#include <stdio.h>
#include <fcntl.h>
#include <vector>
#include "BPatch.h"
#include "BPatch_point.h"
#include "BPatch_process.h"
#include "BPatch_function.h"
#include "BPatch_thread.h"
#include "BPatch_flowGraph.h"
#include "BPatch_basicBlock.h"
# include"BPatch_module.h"
void usage()
{
    fprintf(stderr, "Usage: retee <process pid> <filename>\n");
    fprintf(stderr, "   note: <filename> is relative to the application process.\n");
}

BPatch_variableExpr *fdVar = NULL;

int openFileForWrite(BPatch_process *app, BPatch_image *appImage, char *fileName)
{
    // The code to be generated is:
    // fd = open(argv[2], O_WRONLY|O_CREAT, 0666);
    // (1) Find the open function
    std::vector<BPatch_function *> openFuncs;
    appImage->findFunction("open", openFuncs);
    if (openFuncs.size() == 0)
    {
        fprintf(stderr, "ERROR: Unable to find function for open()\n");
        return -1;
    }
    std::vector<BPatch_snippet *> openArgs;
    BPatch_constExpr fileNameExpr(fileName);
    BPatch_constExpr fileFlagsExpr(O_WRONLY | O_CREAT);
    BPatch_constExpr fileModeExpr(0666);
    openArgs.push_back(&fileNameExpr);
    openArgs.push_back(&fileFlagsExpr);
    openArgs.push_back(&fileModeExpr);
    BPatch_funcCallExpr openCall(*openFuncs[0], openArgs);
    void *openFD = app->oneTimeCode(openCall);
    return (int)(long)openFD;
}

BPatch_variableExpr *writeFileDescIntoMutatee(BPatch_process *app, BPatch_image *appImage, int fileDescriptor)
{ // (1) Allocate a variable in the mutatee of size (and type)
    BPatch_variableExpr *fdVar = app->malloc(*appImage->findType("int"));
    if (fdVar == NULL)
        return NULL;
    bool ret = fdVar->writeValue((void *)&fileDescriptor, sizeof(int), false);
    if (ret == false)
        return NULL;
    return fdVar;
}

bool interceptAndCloneWrite(BPatch_process *app, BPatch_image *appImage, BPatch_variableExpr *fdVar)
{
    std::vector<BPatch_function *> writeFuncs;

    appImage->findFunction("write", writeFuncs);
    if (writeFuncs.size() == 0)
    {
        fprintf(stderr, "ERROR: Unable to find function for write()\n");
        return false;
    }
    std::vector<BPatch_snippet *> writeArgs;
    writeArgs.push_back(fdVar);
    BPatch_paramExpr buffer(1); // Second (0, 1, 2) argument
    BPatch_paramExpr bufferSize(2);
    writeArgs.push_back(&buffer);
    writeArgs.push_back(&bufferSize);
    BPatch_funcCallExpr writeCall(*writeFuncs[0], writeArgs);
    std::vector<BPatch_point *> *points;
    points = writeFuncs[0]->findPoint(BPatch_entry);
    if ((*points).size() == 0)
    {
        return false;
    }
    return app->insertSnippet(writeCall, *points);
}
void closeFile(BPatch_thread *thread, BPatch_exitType)
{
    fprintf(stderr, "Exit callback called for process...\n");

    // (1) Get the BPatch_process and BPatch_images
    BPatch_process *app = thread->getProcess();
    BPatch_image *appImage = app->getImage();

    // The code to be generated is:     // close(fd);          // (2) Find close
    std::vector<BPatch_function *> closeFuncs;
    appImage->findFunction("close", closeFuncs);
    if (closeFuncs.size() == 0)
    {
        fprintf(stderr, "ERROR: Unable to find function for close()\n");
        return;
    }
    // (3) Allocate a vector of snippets for the parameters to open
    std::vector<BPatch_snippet *> closeArgs;
    // (4) Add the fd snippet - fdVar is global since we can't
    // get it via the callback
    closeArgs.push_back(fdVar);
    // (5) create a procedure call using function found at 1 and
    // parameters from step 3.
    BPatch_funcCallExpr closeCall(*closeFuncs[0], closeArgs);
    // (6) Use a oneTimeCode to close the file
    app->oneTimeCode(closeCall);

    // (7) Tell the app to continue to finish it off.
    app->continueExecution();
    return;
}

BPatch bpatch;
int main(int argc, char *argv[])
{
    int pid;
    if (argc != 3)
    {
        usage();
        exit(1);
    }
    pid = atoi(argv[1]);

    // Attach to the program - we can attach with just a pid; the     // program name is no longer necessary
    fprintf(stderr, "Attaching to process %d...\n", pid);
    BPatch_process *app = bpatch.processAttach(NULL, pid);

    if (!app)
        return -1;
    BPatch_image *appImage = app->getImage();
    std::vector<BPatch_function *> writeFuncs;

    fprintf(stderr, "Opening file %s for write...\n", argv[2]);
    int fileDescriptor = openFileForWrite(app, appImage, argv[2]);

    if (fileDescriptor == -1)
    {
        fprintf(stderr, "ERROR: opening file %s for write failed\n", argv[2]);
        exit(1);
    }

    fprintf(stderr, "Writing returned file descriptor %d into"
                    "mutatee...\n",
            fileDescriptor);

    // This was defined globally as the exit callback needs it.
    fdVar = writeFileDescIntoMutatee(app, appImage, fileDescriptor);
    if (fdVar == NULL)
    {
        fprintf(stderr, "ERROR: failed to write mutatee-side variable\n");
        exit(1);
    }

    fprintf(stderr, "Instrumenting write...\n");
    bool ret = interceptAndCloneWrite(app, appImage, fdVar);
    if (!ret)
    {
        fprintf(stderr, "ERROR: failed to instrument mutatee\n");
        exit(1);
    }

    fprintf(stderr, "Adding exit callback...\n");
    bpatch.registerExitCallback(closeFile); // Continue the execution...
    fprintf(stderr, "Continuing execution and waiting for termination\n");
    app->continueExecution();

    while (!app->isTerminated())
        bpatch.waitForStatusChange();
    printf("Done.\n");

    return 0;
}

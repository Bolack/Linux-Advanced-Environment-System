#include "vector"
#include "BPatch.h"
#include"BPatch_Vector.h"
#include"BPatch_process.h"
#include"BPatch_snippet.h"
#include"BPatch_function.h"

int main(int argc,char **argv){

    BPatch *bpatch=new BPatch;

    std::vector <BPatch_function*>  func_old;

    std::vector<BPatch_function*> func_new;

    // Specify the executable file name and process id of the application as arguments
    BPatch_process *appProc = bpatch->processAttach(argv[1], atoi(argv[2]));

    // BPatch_process inherit from BPatch_addressSpace
    BPatch_addressSpace *app = appProc;

    BPatch_image *appImage = app->getImage();
    
    // Find function:old()
    appImage->findFunction("old", func_old);
    
    // find function: new()
    appImage->findFunction("new", func_new);
    
    // Exchange function "old()" to "new()"
    appProc->replaceFunction(*func_old[0], *func_new[0]);
    
    // Detach from the mutatee process, optionally leaving it running
    appProc->detach(1);
}
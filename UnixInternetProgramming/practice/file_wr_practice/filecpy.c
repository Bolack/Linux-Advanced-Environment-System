#include <stdio.h>
#include <sys/stat.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
int file_size(char *filename)
{
    struct stat statbuf;
    stat(filename, &statbuf);
    int size = statbuf.st_size;
    return size;
}
void main()
{
    FILE *infile = fopen("pic.jpg", "rb");
    FILE *outfile = fopen("piccopy.jpg", "wb");
    int filesize = file_size("pic.jpg");
    char* buffer = malloc(filesize);
    fread(buffer, 1, filesize, infile);
    fwrite(buffer, filesize, 1, outfile);
    printf("filesize:%d", filesize);
    fclose(infile);
    fclose(outfile);
}
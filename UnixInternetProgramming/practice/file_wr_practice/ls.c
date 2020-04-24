#include <stdio.h>
#include <dirent.h>
#include <string.h>
#define FilePath "./"

int ls(char *buf);

int main()
{
    char *buf = (char*)malloc(sizeof(char) * 256);
    ls(buf);
    printf("return string:");
    printf("%s", buf);
    return 0;
}

int ls(char *buf)
{
    int i = 0;
    int filesize = 0;
    DIR *dir = NULL;
    struct dirent *entry;

    if ((dir = opendir(FilePath)) == NULL)
    {
        printf("opendir failed!");
        return -1;
    }
    else
    {
        while (entry = readdir(dir))
        {
            i++;
            if (entry->d_type != 4)
            {
                printf("%s    ", entry->d_name);
                strcat(buf,entry->d_name);
                strcat(buf,"    ");
            }
            // printf("filename%d = %s",i,entry->d_name);  //输出文件或者目录的名称
            // printf("filetype = %d\n",entry->d_type);  //输出文件类型
        }
        printf("\n");
        strcat(buf,"\n");
        closedir(dir);
    }
    return 0;
}
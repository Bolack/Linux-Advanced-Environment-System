#include<stdlib.h> 
#include <time.h>

void old()
{
    printf("Oh my god! Pid is %d\n", getpid());
}

void new()
{
    printf("Hello world! Pid is %d\n", getpid());
}

int main()
{
    while(1){
        old();
        sleep(5);
    }
    return 0;
}
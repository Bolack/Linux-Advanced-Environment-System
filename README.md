# linux环境编程的第三分支
## 说明
主要用于


## 上传到github的步骤
1.增加远程地址   
> git remote add origin https://github.com/9DemonFox/Linux-Advanced-Environment-System.git

2.和远程分支关联
- 如果远程有该分支，需要当前与其关联
> git branch --set-upstream-to origin/google
- 如果远程没有该分支，需要从本地推送
> $ git push origin GCC-practice:GCC-practice   
Username for 'https://github.com': 9DemonFox  
Password for 'https://9DemonFox@github.com':  

## 练习linux下C和C++

## GCC
1. 使用 ldd ./test查看链接库链接情况
2. 
    ```
    all: libhello.so test

    libhello.so:hello.c 
        gcc -fPIC -shared -o libhello.so hello.c 
    # 生成动态链接库

    test:test.c
        gcc -o test test.c -L. libhello.so \ 
        -Wl,-rpath=./ # 设定链接库路径 优先搜索-rpath的命令
    ```
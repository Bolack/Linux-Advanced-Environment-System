# linux环境编程的第三分支


## 上传到github的步骤
1.增加远程地址   
> git remote add origin https://github.com/9DemonFox/Linux-Advanced-Environment-System.git

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
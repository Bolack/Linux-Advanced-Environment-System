# dyninst 
## 概念
- mutatee 被修改的程序
- mutator
## Tips
- 在编译mutator时用c++
- 需要修改动态库的配置  
  ```
  修改etc/lb.so.conf，添加usr/local/lib(使用whereis找到库的目录)
  再运行程序
  root@ubuntu:/sbin# vi lb.so.conf
  root@ubuntu:/sbin# ./ldconfig
  
  ```
  ![图片]（./image/image/TIM截图20200408172745.png）
  - 一个Makefile中有多个可执行文件，使用all:app1 app2

## Linux
- debug命令 i r 显示寄存器内容
- 对.o程序生成机器码和汇编码
  ```
    objdump -d -M intel hello >hello.txt
    //生成汇编和机器码
  ```
- 查看某个程序中某个函数地址的命令
  ```
    readelf -a ./a.out | grep bingo
  ```
- Linux管道命令
  > linux执行命令时会先执行  ``中的命令，返回值传递给下一个命令
- 获取当前命令的输出
  >`echo test`

- Linux注销root
  > logout

- Linux删除文件
  > rm-rf filename

- vscode使用git没有权限的问题
  > 使用 ll 命令查看当前文件夹权限归属，.git属于root的  
  > 删除.git,在user下重新创建


## Git中的分支合并
-   git branch  
-   git pull 远程没有配置文件 ，需要.git的config下设置  
-   git clone远程的非master分支 
  

  ## 栈溢出获取命令行控制
- 编译时关闭栈溢出保护
  >a.out:hello.c  
	gcc -g -fno-stack-protector hello.c
- buffer首地址到main函数地址返回偏移（中间填充无效字符在main函数返回地址劫持）
  - 获取bingo的地址
    - 方法1
        >    readelf -a ./a.out | grep bingo  
        >   59: 00000000000011a9    23 FUNC    GLOBAL DEFAULT   16 bingo
     - 方法2
        >(gdb) p bingo  
            $4 = {void ()} 0x5555555551a9 <bingo>
- buffer首地址 
    >(gdb) p &buffer  
    $3 = (char (*)[36]) 0x7fffffffdd50 //buffer在栈中的地址
  - main函数返回地址 rip后面的
  > info f  
  Stack level 0, frame at 0x7fffffffdd90:  
  rip = 0x5555555551c0 in main (hello.c:10); saved rip = 0x7ffff7ded1e3  
  source language c.  
  Arglist at 0x7fffffffdd80, args:   
  Locals at 0x7fffffffdd80, Previous frame's sp is 0x7fffffffdd90  
  Saved registers:  
  rip at 0x7fffffffdd88

## 项目说明

- dyninst_4_retee
  > sudo sh run.sh
  > 实现插桩对程序中printf转到log中去
- dyninst_1
  > 实现了插桩改变程序运行时函数
- dyninst_git_codeCover
  >用于实现codeCover的插桩，但是dyninst的module包不完整，原因未知
- dyninst_shalow_stack
  >使用影子栈的思想，检查返回地址是否准确
- dyninstSamples
  >一些dyninst的例子 包含影子栈

  ## vscode调试make生成文件
  - 注释掉pretask
  - 添加args

## 课程报告
- 
5.	我尝试写一个Task可以传递任意参数和返回任意的地址，但是返回地址一直为0x0，出错程序如下：
表10.3 出错程序
	正确的做法是如图中注释部分，声明一个指针，再返回指针。
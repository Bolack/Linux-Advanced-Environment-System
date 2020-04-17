all: buffer buffer.s

# -no-pie 地址随机化关闭
buffer:buffer.c
	gcc -fno-stack-protector  -no-pie -z norelro -z noexecstack   -o buffer buffer.c 

buffer.s:buffer.c
	gcc -fno-stack-protector  -no-pie -z norelro -z noexecstack   -o buffer.s -S buffer.c

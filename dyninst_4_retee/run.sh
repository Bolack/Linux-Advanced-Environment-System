# 编译
make
# 启动test ,获取test pid 作为retee的参数 输出到test.log
# 使用&并发执行命令
./test &  ./retee $(pgrep -f ./test) test.log
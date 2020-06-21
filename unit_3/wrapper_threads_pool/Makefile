compile_option=-pthread -g

main:test.cpp Buffer.cpp Condition.cpp MutexLock.cpp Thread.cpp Threadpool.cpp
	g++ -o $@ $^ $(compile_option)

clean:
	rm -rf main
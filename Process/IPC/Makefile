# IPC:进程间通信方式的Makefile
# IPC : pipe , fifo , shared memory

unamed_pipe_test : unamed_pipe_test.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


fifo_read : fifo_read.c
	-$(CC) -o $@ $^


fifo_write : fifo_write.c
	-$(CC) -o $@ $^


shared_memory : shared_memory.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


shared_memory_block : shared_memory_block.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


message_queue : message_queue.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@
	
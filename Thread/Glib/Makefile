CC := gcc

thread_pool : thread_pool.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@
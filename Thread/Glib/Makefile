CC := gcc

thread_pool : thread_pool.c
	-$(CC) -o $@ $^ `pkg-config --cflags --libs glib-2.0`
	-./$@ "test"
	-rm ./$@
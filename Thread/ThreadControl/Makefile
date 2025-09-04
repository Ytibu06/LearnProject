CC := gcc

pthread_create : pthread_create.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


pthread_exit : pthread_exit.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


pthread_detach : pthread_detach.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


pthread_cancel_defer : pthread_cancel_defer.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


pthread_cancel_sync : pthread_cancel_sync.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


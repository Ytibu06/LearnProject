CC := gcc

pthread_mutex : pthread_mutex.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


pthread_rwlock : pthread_rwlock.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


pthread_rwlock_hungry : pthread_rwlock_hungry.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


pthread_spinlock : pthread_spinlock.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


unnamed_sem : unnamed_sem.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@
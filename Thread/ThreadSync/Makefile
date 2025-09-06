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


pthread_mutex_condvar : pthread_mutex_condvar.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


unnamed_sem_bin_thread : unnamed_sem_bin_thread.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


unnamed_sem_bin_process : unnamed_sem_bin_process.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


unnamed_sem_count_thread : unnamed_sem_count_thread.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@

unnamed_sem_count_process : unnamed_sem_count_process.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


named_sem_bin_process : named_sem_bin_process.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


named_sem_count_process : named_sem_count_process.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


clean :
	-rm *.o
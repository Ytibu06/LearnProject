CC := gcc

system_test:system_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


fork_test:fork_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


fork_fd_test:fork_fd_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

test : test.c
	-$(CC) -o $@ $^


execve_test:execve_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


fork_execve_test:fork_execve_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


waitpid_test:waitpid_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


pstree_test:pstree_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
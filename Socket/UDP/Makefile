CC := gcc


udp_server : udp_server.c
	-$(CC) -o $@ $^


udp_client : udp_client.c
	-$(CC) -o $@ $^

clean :
	-rm udp_server udp_client
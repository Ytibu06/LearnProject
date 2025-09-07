CC := gcc

num_endianess_convert : num_endianess_convert.c
	-$(CC) -o $@ $^ 
	-./$@ "test"
	-rm ./$@


inet_endian_convert : inet_endian_convert.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


single_conn_server : single_conn_server.c
	-$(CC) -o $@ $^ 


single_conn_client : single_conn_client.c
	-$(CC) -o $@ $^


is_buffer : is_buffer.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


multi_conn_server_thread : multi_conn_server_thread.c
	-$(CC) -o $@ $^


multi_conn_client_thread : multi_conn_client_thread.c
	-$(CC) -o $@ $^


multi_conn_server_process : multi_conn_server_process.c
	-$(CC) -o $@ $^


multi_conn_client_process : multi_conn_client_process.c
	-$(CC) -o $@ $^

clean:
	-rm  multi_conn_client_process
	-rm  multi_conn_server_process
	-rm  multi_conn_client_thread
	-rm  multi_conn_server_thread
	-rm  single_conn_client
	-rm  single_conn_server
	-rm  multi_conn_client
	-rm  multi_conn_server
	-rm  test.txt
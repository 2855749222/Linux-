CC:=gcc
fopen_test: fopen_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fputc_test : fputc_test.c
	-$(CC) $^ -o $@
	-./$@
	-rm ./$@
fputs_test : fputs_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
fprintf_test: fprintf_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
fgetc_test: fgetc_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
fgets_test: fgets_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
fscanf_test: fscanf_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
stdin_out_err_test: stdin_out_err_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
system_call_test: system_call_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
system_text: system_text.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_test: fork_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
erlou: erlou.c
	-$(CC) -o $@ $^
	-./$@
	
execve_text: execve_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_execve_test: fork_execve_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
waitpid-test: waitpid_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
	
tou_erlou: tou_erlou.c
	-$(CC) -o $@ $^

orphan_process: orphan_process.c tou_erlou
	-$(CC) -o $@ $<
	-./$@
	-rm ./$@ ./$(word 2,$^)
 
	

fifo_read: fifo_read.c
	-$(CC) -o $@ $^


fifo_write: fifo_write.c
	-$(CC) -o $@ $^

shared_memory: shared_memory.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

shared_memory_block: shared_memory_block.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
father_son_mq_test: father_son_mq_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

msgget_sand: msgget_sand.c
	-$(CC) -o $@ $^


msgget_rcve: msgget_rcve.c
	-$(CC) -o $@ $^


mq_producer: mq_producer.c
	-$(CC) -o $@ $^


mq_consumer: mq_consumer.c
	-$(CC) -o $@ $^
	
signal_test: signal_test.c
	-$(CC) -o $@ $^
	
	

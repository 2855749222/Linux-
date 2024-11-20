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
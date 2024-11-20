CC:=gcc

create_test: create_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

pthread_join: pthread_join.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

pthread_detach: pthread_detach.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
	
pthread_cancel_deferred_test: pthread_cancel_deferred_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

pthread_cancel_async_test: pthread_cancel_async_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

pthread_cancel_disabled_test: pthread_cancel_disabled_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
race_condition_test: race_condition_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock_test_writer_unlock: rwlock_test_writer_unlock.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock_test: rwlock_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock_rw_alternate: rwlock_rw_alternate.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock_hungry_solved: rwlock_hungry_solved.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

condition_var: condition_var.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

c1119_tjbl: c1119_tjbl.c
	-$(CC) -o $@ $^ 
	-./$@
	-rm ./$@

dog_food: dog_food.c
	-$(CC) -o $@ $^ 
	-./$@
	-rm ./$@

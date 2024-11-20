objects := hello.o main.o
main: $(objects)
	gcc $(objects) -o main
# yilai
main.o: main.c hello.h
	gcc -c main.c
hello.o: hello.c hello.h
	gcc -c hello.c
clean:
	rm $(objects)
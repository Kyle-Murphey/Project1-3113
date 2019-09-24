all: project1

project1.o: project1.c
	gcc -c project1.c

storage.o: storage.c
	gcc -c storage.c

project1: project1.o storage.o
	gcc project1.o storage.o -o project1

zip:
	zip project1.zip *.c *.h Makefile README.txt

clean:
	rm -f project1 *.o

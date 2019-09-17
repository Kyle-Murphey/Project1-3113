all: project1.c
	gcc project1.c -o project1
zip:
	zip project1.zip *.c Makefile README.txt
clean:
	rm -f project1 *.o

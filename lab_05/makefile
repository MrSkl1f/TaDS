CFLAGS = -Wall -std=c99 -Werror -pedantic

all: app.exe cls

app.exe: arrqueue.o main.o listqueue.o
	gcc -o app.exe main.o arrqueue.o listqueue.o  -lm

arrqueue.o: arrqueue.c
	gcc -c arrqueue.c

listqueue.o: listqueue.c
	gcc -c listqueue.c

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *.exe

cls:
	rm -rf *.o

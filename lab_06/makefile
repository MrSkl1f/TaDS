CFLAGS = -Wall -std=c99 -Werror -pedantic

all: app.exe cls

app.exe: mainfile.o operationstree.o input.o operationshash.o operationsddptree.o find.o
	gcc -o app.exe *.o -lm

mainfile.o: ./sourceFiles/mainfile.c
	gcc $(CFLAGS) -c ./sourceFiles/mainfile.c

operationstree.o: ./sourceFiles/operationstree.c
	gcc $(CFLAGS) -c ./sourceFiles/operationstree.c

input.o: ./sourceFiles/input.c
	gcc $(CFLAGS) -c ./sourceFiles/input.c

operationshash.o: ./sourceFiles/operationshash.c
	gcc $(CFLAGS) -c ./sourceFiles/operationshash.c

operationsddptree.o: ./sourceFiles/operationsddptree.c
	gcc $(CFLAGS) -c ./sourceFiles/operationsddptree.c

find.o: ./sourceFiles/find.c
	gcc $(CFLAGS) -c ./sourceFiles/find.c

cls:
	rm -rf *.o *.out

clean:
	rm -rf *.o *.exe
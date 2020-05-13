all: app.exe cls

app.exe: main.o
	gcc -o app.exe main.o

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *.exe

cls:
	rm -rf *.o
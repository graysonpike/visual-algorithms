main: main.o random.o
	gcc -Wall main.o random.o -std=c99 -o main.out -lSDL2

main.o: main.c
	gcc -Wall -c main.c -std=c99 -lSDL2

random.o: random.c
	gcc -Wall -c random.c -std=c99

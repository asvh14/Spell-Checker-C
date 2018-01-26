CC=gcc
CFLAGS=-Wall -pedantic -std=c99

SRC=./src/

all:main

main:
	$(CC) $(CFLAGS) $(SRC)main.c $(SRC)HashTableAPI.c -Iincludes -o ./bin/main
	
testMain:
	$(CC) $(CFLAGS) $(SRC)testMain.c $(SRC)HashTableAPI.c -Iincludes -o ./bin/testMain
	
clean:
	rm main main.o HashTableAPI.o testMain.o

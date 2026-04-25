CC = gcc 

all: cache.o
	$(CC) -o cache cache.o

cache.o: cache.c
	$(CC) -c cache.c

clean:
	rm cache.o
	rm cache

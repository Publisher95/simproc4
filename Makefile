CC = gcc 

all:
	$(CC) -o cache cache.o

cache.o: cache.c
	$(CC) -c cache.c

clean:
	rm cache.o
	rm cache

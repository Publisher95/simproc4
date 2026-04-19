CC = gcc 

TARGET = cache

all: $(TARGET)

$(TARGET): cache.o
	$(CC) -o $(TARGET) cache.o

cache.o: cache.c
	$(CC) -c cache.c


clean:
	rm -f *.o $(TARGET)

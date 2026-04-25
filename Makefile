CC = gcc 

TARGET = cache

$(TARGET): $(TARGET)

$(TARGET): cache.o
	$(CC) -o3 $(TARGET) cache.o

cache.o: cache.c
	$(CC) -c cache.c


clean:
	rm cache

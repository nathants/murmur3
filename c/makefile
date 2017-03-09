.PHONY: all clean

all: murmur3
murmur3:
	$(CC) -fPIC -O3 -Wall main.c murmur3.c -o murmur3

clean:
	rm -rf murmur3 *.o *.so

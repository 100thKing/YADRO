CC = g++

CFLAGS = -std=c++20

all:
	mkdir -p build
	$(CC) $(CFLAGS) -c src/noise.cpp -o build/noise.o
	$(CC) $(CFLAGS) -c src/qam.cpp -o build/qam.o
	$(CC) $(CFLAGS) -c src/main.cpp -o build/main.o
	g++ build/noise.o build/qam.o build/main.o -o runfile


clean:
	rm -f runfile
	rm -rf build
	rm -f result.txt

.PHONY: all clean

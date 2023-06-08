CC = ccache g++
CFLAGS = -g -Wall -std=c++17 -O0 -fsanitize=undefined,address -DLOCAL

ALL: main.o TempState.o TempStateTest.o
	$(CC) $(CFLAGS) -o main \
	main.o \
	TempState.o \
	TempStateTest.o \
	-lgtest_main -lgtest -lpthread
	
clean:
	rm main *.o

test: ALL
	./main

main.o: main.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

TempState.o: ../TempState.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<

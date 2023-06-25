CC = ccache g++
#CFLAGS = -g -Wall -std=c++17 -O0 -fsanitize=undefined,address -DLOCAL

# core dump出力用
#CFLAGS = -g -Wall --std=c++17 -O0 -DLOCAL

CFLAGS = -Wall --std=c++17 -O2 -DLOCAL
#CFLAGS = -pg -g -Wall --std=c++17 -O0 -DLOCAL

ALL: Utility.o XorShift.o Parameter.o SearchInfo.o State.o main.o
	$(CC) $(CFLAGS) -o main \
	Utility.o \
	XorShift.o \
	Parameter.o \
	SearchInfo.o \
	State.o \
	main.o \

clean:
	rm main *.o

run:
	./main

Utility.o: ../Utility.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

XorShift.o: ../XorShift.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

Parameter.o: ../Parameter.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

SearchInfo.o: ../SearchInfo.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

State.o: ../State.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

main.o: ../main.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<


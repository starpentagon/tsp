CC = ccache g++
#CFLAGS = -g -Wall -std=c++17 -O0 -fsanitize=undefined,address -DLOCAL $(CFLAGS_EXTRA)

# core dump出力用
#CFLAGS = -g -Wall --std=c++17 -O0 -DLOCAL $(CFLAGS_EXTRA)

CFLAGS = -Wall --std=c++17 -O3 -DLOCAL $(CFLAGS_EXTRA)
#CFLAGS = -Wall --std=c++17 -O3 -funroll-loops -DLOCAL $(CFLAGS_EXTRA)
#CFLAGS = -pg -g -Wall --std=c++17 -O0 -DLOCAL $(CFLAGS_EXTRA)

ALL: XorShift.o Utility.o Parameter.o SearchInfo.o State.o main.o
	$(CC) $(CFLAGS) -o main$(POSIX) \
	XorShift.o \
	Utility.o \
	Parameter.o \
	SearchInfo.o \
	State.o \
	main.o \

clean:
	rm main *.o

run:
	./main

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<


rm *.o > /dev/null
make -j > /dev/null

rm *.o > /dev/null
make -j CFLAGS_EXTRA:=-DLOCAL_TEST POSIX=_test > /dev/null

CC=g++ -std=c++11
LDFLAGS= -ggdb
CFLAGS = -c -Wall

EXECUTABLE=test

$(EXECUTABLE): Option.h test.cpp
	$(CC) $(LDFLAGS) test.cpp -o $@

clean:
	rm -f test

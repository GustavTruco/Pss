CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g
LDLIBS= -lpthread -lm

all:

test-p1.o p1.o: p1.h
test-p1: test-p1.o p1.o

test-p1-valgrind: test-p1
	make clean
	make test-p1
	valgrind --vgdb=yes --vgdb-error=0 ./test-p1

test-p2.o p2.o: p2.h
test-p2: test-p2.o p2.o

test-p2-valgrind:
	make clean
	make test-p2
	valgrind --vgdb=yes --vgdb-error=0 ./test-p2

test-p3.o p3.o: p3.h
test-p3: test-p3.o p3.o

test-p3-sanitize:
	make clean
	make "CFLAGS=-g -fsanitize=thread -DSANITIZE -Wall -pedantic -std=c99" "LDFLAGS=-fsanitize=thread" test-p3
	./test-p3

test-p4.o p4.o: p4.h
test-p4: test-p4.o p4.o

clean:
	rm -f *.o test-p1 test-p2 test-p3 test-p4

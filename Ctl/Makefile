CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g
LDLIBS= -lpthread -lm

all: test-p5

test-p1.o p1.o: p1.h
test-p1: test-p1.o p1.o

test-p2.o p2.o: p2.h
test-p2: test-p2.o p2.o
test-p2-valgrind-ddd:
	make clean
	make test-p2
	valgrind --leak-check=full --vgdb=yes --vgdb-error=0 ./test-p2

test-p3.o p3.o: p3.h
test-p3: test-p3.o p3.o
test-p3-valgrind-ddd:
	make clean
	make test-p3
	valgrind --leak-check=full --vgdb=yes --vgdb-error=0 ./test-p3

muestrear: muestrear.c
muestrear-valgrind-ddd:
	make clean
	make muestrear
	valgrind --leak-check=full --vgdb=yes --vgdb-error=0 ./muestrear noms.txt 3

test-p5.o p5.o: p5.h
test-p5: test-p5.o p5.o
test-p5-valgrind-ddd:
	make clean
	make "CFLAGS=-g -Wall -pedantic -std=c99 -DVALGRIND" test-p5
	valgrind --leak-check=full --vgdb=yes --vgdb-error=0 ./test-p5

clean:
	rm -f *.o test-p1 test-p2 test-p3 muestrear test-p5

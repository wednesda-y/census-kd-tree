CFLAGS = -Wall -g 
LIBS = -lm
all: map1 map2

map1: map1.c list read business kd_tree
	gcc $(CFLAGS) list.o read.o business.o kd_tree.o map1.c -o map1 $(LIBS)

map2: map2.c list read business kd_tree
	gcc $(CFLAGS) list.o read.o business.o kd_tree.o map2.c -o map2 $(LIBS)

list: list.c list.h
	gcc $(CFLAGS) -c list.c

read: read.c read.h
	gcc $(CFLAGS) -c read.c

business: business.c business.h
	gcc $(CFLAGS) -c business.c

kd_tree: kd_tree.c kd_tree.h
	gcc $(CFLAGS) -c kd_tree.c

clean:
	rm *.o

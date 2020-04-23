CC=gcc
CFLAGS=-c -Wall
OBJS=Main.o Numbers.o

all: prog

prog: $(OBJS)
	$(CC) $(OBJS) -o prog

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o
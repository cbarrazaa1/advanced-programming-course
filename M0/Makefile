CC=gcc
CFLAGS=-c -Wall
OBJS=Main.o StringNode.o AgentNode.o

all: prog

prog: $(OBJS)
	$(CC) $(OBJS) -o prog

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o
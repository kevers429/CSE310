OBJS = main.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p2

main.o : main.cpp
	$(CC) $(CFLAGS) main.cpp

clean :
	rm p2

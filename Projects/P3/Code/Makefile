OBJS = AdjList.o main.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = $(DEBUG)

p3 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) $^

clean :
	rm *.o p3

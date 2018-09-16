OBJS = value.o compare.o printStat.o isort.o find.o main.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

main.o : main.cpp value.h compare.h printStat.h sorts.h find.h
	$(CC) $(CFLAGS) compare.cpp value.cpp find.cpp printStat.cpp isort.cpp main.cpp

value.o : value.cpp value.h
	$(CC) $(CFLAGS) value.cpp

compare.o : compare.cpp compare.h value.h
	$(CC) $(CFLAGS) compare.cpp

printStat.o : printStat.cpp value.h
	$(CC) $(CFLAGS) printStat.cpp

isort.o : isort.cpp sorts.h compare.h
	$(CC) $(CFLAGS) isort.cpp

find.o : find.cpp sorts.h printStat.h
	$(CC) $(CFLAGS) find.cpp

clean :
	rm *.o p1

CC = gcc
CFLAGS = -Wall -Werror -g


all:
	make pagerank inverted searchPagerank

Graph.o: Graph.c
	$(CC) $(CFLAGS) -c  Graph.c

read_file.o: read_file.c Graph.c
	$(CC) $(CFLAGS) -c  read_file.c Graph.c

DLListStr.o: DLListStr.c
	$(CC) $(CFLAGS) -c  DLListStr.c

helper.o: helper.c
	$(CC) $(CFLAGS) -c  helper.c

pagerank.o: pagerank.c 
	$(CC) $(CFLAGS) -c  pagerank.c

pagerank: pagerank.o Graph.o read_file.o DLListStr.o InvertedIdx.o helper.o
	$(CC) -o pagerank pagerank.o Graph.o read_file.o DLListStr.o InvertedIdx.o helper.o

InvertedIdx.o: InvertedIdx.c InvertedIdx.h
	$(CC) $(CFLAGS) -c  InvertedIdx.c InvertedIdx.h

inverted.o: inverted.c read_file.c

inverted: inverted.o read_file.o DLListStr.o InvertedIdx.o helper.o read_file.o Graph.o
	$(CC) -o inverted inverted.o DLListStr.o InvertedIdx.o helper.o read_file.o Graph.o

searchPagerank.o : searchPagerank.c

searchPagerank: searchPagerank.o DLListStr.o helper.o Triple.o read_file.o
	$(CC) -o searchPagerank searchPagerank.o DLListStr.o helper.o Triple.o

Triple.o: Triple.c

clear: 
	rm ./*.o pagerank inverted searchPagerank
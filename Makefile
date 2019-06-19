CC = gcc
CFLAGS = -Wall -Werror -g


all:
	make pagerank inverted searchPagerank

Graph.o: Graph.c
	$(CC) $(CFLAGS) -c  Graph.c

DLListStr.o: DLListStr.c
	$(CC) $(CFLAGS) -c  DLListStr.c

Triple.o: Triple.c
	$(CC) $(CFLAGS) -c  Triple.c

read_file.o: read_file.c Graph.c
	$(CC) $(CFLAGS) -c  read_file.c Graph.c

helper.o: helper.c
	$(CC) $(CFLAGS) -c  helper.c

pagerank.o: pagerank.c 
	$(CC) $(CFLAGS) -c  pagerank.c

InvertedIdx.o: InvertedIdx.c InvertedIdx.h
	$(CC) $(CFLAGS) -c  InvertedIdx.c

pagerank: pagerank.o Graph.o read_file.o DLListStr.o InvertedIdx.o helper.o
	$(CC) -o pagerank pagerank.o Graph.o read_file.o DLListStr.o InvertedIdx.o helper.o


inverted.o: inverted.c read_file.c

inverted: inverted.o read_file.o DLListStr.o InvertedIdx.o helper.o read_file.o Graph.o
	$(CC) -o inverted inverted.o DLListStr.o InvertedIdx.o helper.o read_file.o Graph.o

searchPagerank.o : searchPagerank.c

searchPagerank: searchPagerank.o DLListStr.o helper.o Triple.o read_file.o
	$(CC) -o searchPagerank searchPagerank.o DLListStr.o helper.o Triple.o

clear: 
	rm invertedIndex.txt pagerankList.txt ./*.o pagerank inverted searchPagerank

test:
	./pagerank 0.85  0.00001  1000
	./inverted
	./searchPagerank winds;
all:
	gcc -Wall -c common.c
	gcc -Wall clientprof.c common.o -o client
	gcc -Wall serverprof.c common.o -o server
	gcc -Wall -lpthread server-mt.c common.o -o server-mt

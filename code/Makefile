CC=gcc
LD=gcc

CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -O3
LDFLAGS=

MODULES=main.c graphes.c prufer.c tableau.c utilitaires.c

HEADER=graphes.h prufer.h utilitaires.h tableau.h

OBJETS=graphes.o prufer.o utilitaires.o tableau.o main.o

EXEC: prufer

prufer: $(OBJETS)
	$(LD) -o $@ $(OBJETS) $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

prufer_benchmarking.o : prufer_benchmarking.c prufer.h graphes.h utilitaires.h tableau.h
	$(CC) $(CFLAGS) -c prufer_benchmarking.c -o prufer_benchmarking.o

prufer_benchmarking: prufer_benchmarking.o graphes.o prufer.o utilitaires.o tableau.o
	$(LD) -o prufer_benchmarking prufer_benchmarking.o graphes.o prufer.o utilitaires.o tableau.o $(LDFLAGS)

clean:
	rm -f $(OBJETS) prufer_benchmarking.o prufer prufer_benchmarking
	clear

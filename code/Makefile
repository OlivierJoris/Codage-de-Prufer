CC=gcc
LD=gcc

CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -g
LDFLAGS=

MODULES=main.c graphes.c prufer.c tableau.c utilitaires.c

HEADER=graphes.h prufer.h utilitaires.h tableau.h

OBJETS=graphes.o prufer.o utilitaires.o tableau.o main.o

EXEC: prufer

prufer: $(OBJETS)
	$(LD) -o $@ $(OBJETS) $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJETS) prufer
	clear

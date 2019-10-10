CC=gcc
LD=gcc

CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -g
LDFLAGS=

MODULES=main.c graphes.c tableau.c tilitaires.c

HEADER=graphes.h utilitaires.h tableau.h

OBJETS=main.o graphes.o utilitaires.o tableau.o

EXEC: prufer

prufer: $(OBJETS)
	$(LD) -o $@ $(OBJETS) $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJETS) prufer
	clear
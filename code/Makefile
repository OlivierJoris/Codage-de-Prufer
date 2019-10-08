CC=gcc
LD=gcc

CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -g
LDFLAGS=

MODULES=main.c graphes.c

HEADER=graphes.h

OBJETS=main.o graphes.o

EXEC: prufer

prufer: $(OBJETS)
	$(LD) -o $@ $(OBJETS) $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJETS) prufer
	clear

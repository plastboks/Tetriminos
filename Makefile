CC=gcc
CFLAGS=-Wall -Iinc -std=c99
LFLAGS=-lncurses

ODIR=obj

_OBJ = tetriminos.o config.o screens.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

tetriminos: $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o tetriminos

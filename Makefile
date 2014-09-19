CC=gcc
CFLAGS=-Wall -Iinc -std=c99
LFLAGS=-lncurses

ODIR=obj

# tetriminos app
_OBJ = tetriminos.o config.o screens.o game.o bricks.o
_OBJ += stack.o colors.o movements.o drawers.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

tetriminos: $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


# brick test
_TESTS = brick_test.o bricks.o
TESTS = $(patsubst %,$(ODIR)/%,$(_TESTS))

brick_test: $(TESTS)
	$(CC) -o $@ $^ $(LFLAGS)

$(ODIR)/%.o: tests/%.c src/bricks.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


# clean routine
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o tetriminos brick_test

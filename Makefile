# Makefile generated on Wed Feb  6 17:09:43 2013

CC=g++
CFLAGS= -Wall -Wextra -Wwrite-strings -ansi -pedantic -Isrc
LDFLAGS= 

EXEC=bin/sudoku-solver

# debug/release mode
DEBUG=no
ifeq ($(DEBUG), yes)
	CFLAGS += -g -DDEBUG
else
	CFLAGS += -O3 -march=native -fomit-frame-pointer
endif

$(EXEC): src/Sudoku.o src/Main.o
	@echo linking $(EXEC)...
	@$(CC) $^ -o $(EXEC) $(LDFLAGS)

src/Sudoku.o:src/Sudoku.cpp
	@echo '*' $<
	@$(CC) -o $@ $< -c $(CFLAGS)

src/Main.o:src/Main.cpp
	@echo '*' $<
	@$(CC) -o $@ $< -c $(CFLAGS)

clean:
	@rm src/Sudoku.o
	@rm src/Main.o

mrproper: clean
	@rm $(EXEC)

all: mrproper $(EXEC)

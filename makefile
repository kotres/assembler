CC = gcc

CFLAGS = -W -Wall -Wextra -ansi -pedantic-errors

SOURCES = $(wildcard src/*.c)

OBJS = $(SOURCES:src/%.c=obj/%.o)

all : assembler

assembler : $(OBJS)
	$(CC) -o bin/assembler $(OBJS)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -f bin/assembler obj/*.o *~

# make:
# 	gcc -I src -I src/ADT  main.c src/misc.c src/ADT/mesinkarakter.c src/ADT/mesinkata.c src/ADT/queue.c src/ADT/list.c src/wordl32.c src/rng.c src/qwordl3.c -o main

CC = gcc
CFLAGS = -I include -Wall -Wextra -Werror
SOURCES = src/features/main.c src/features/misc.c src/ADT/mesinkarakter.c src/ADT/mesinkata.c src/ADT/queue.c src/ADT/list.c src/features/wordl32.c src/features/rng.c src/features/qwordl3.c src/features/DNA.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
    $(CC) $(CFLAGS) -o $@ $^

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJECTS) $(TARGET)

.DEFAULT_GOAL := run

run: $(TARGET)
    ./$(TARGET)
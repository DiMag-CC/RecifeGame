CC := gcc

CFLAGS := -Wall -Wextra -I./src $(shell pkg-config --cflags raylib)

LDFLAGS := $(shell pkg-config --libs raylib) -lm

SRC := $(wildcard src/*.c) \
       $(wildcard src/entities/*.c) \
       $(wildcard src/steps/*.c) \
       $(wildcard src/structure/*.c) \
       $(wildcard src/utils/*.c) \
       $(wildcard src/gfx/*.c)

OBJ := $(SRC:.c=.o)

TARGET := deixaeu

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
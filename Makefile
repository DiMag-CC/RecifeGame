CC := gcc
CFLAGS := -Wall -Wextra -I./src
LDFLAGS := -lraylib -lopengl32 -lgdi32 -lwinmm

SRC := $(wildcard src/**/*.c) $(wildcard src/*.c)
OBJ := $(SRC:.c=.o)
TARGET := jogo.exe

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	del /Q /F $(OBJ) $(TARGET) 2>nul || exit 0

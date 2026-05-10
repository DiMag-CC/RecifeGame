CC = gcc

CFLAGS = -Wall -Wextra $(shell pkg-config --cflags raylib)

LDFLAGS = $(shell pkg-config --libs raylib) -lm

SRC = $(wildcard src/*.c) \
      $(wildcard src/entities/*.c) \
      $(wildcard src/steps/*.c) \
      $(wildcard src/structure/*.c) \
      $(wildcard src/utils/*.c) \
      $(wildcard src/gfx/*.c)

OBJ = $(SRC:.c=.o)

BUILD_DIR = build

TARGET = $(BUILD_DIR)/deixaeu

.PHONY: all clean run

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJ)
	rm -rf $(BUILD_DIR)
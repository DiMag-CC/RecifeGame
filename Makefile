CC := gcc
CFLAGS := -Wall -Wextra -I./src
RAYLIB_PATH ?=
ifneq ($(RAYLIB_PATH),)
	CFLAGS += -I$(RAYLIB_PATH)/include
	LDFLAGS := -L$(RAYLIB_PATH)/lib -lraylib -lopengl32 -lgdi32 -lwinmm
else
	LDFLAGS := -lraylib -lopengl32 -lgdi32 -lwinmm
endif

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

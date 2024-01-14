CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = $(shell pkg-config --cflags --libs gtk+-3.0) -lm
SRC_FILES = calc.c calc.h
OUTPUT = calc

__start__: $(OUTPUT)
	./$(OUTPUT)

$(OUTPUT): $(SRC_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(OUTPUT) $(LDFLAGS)
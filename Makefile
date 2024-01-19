# Makefile, tabs must be in tabulation, not spaces

# Compiler and compiler flags
CC = gcc
CFLAGS = -fsanitize=address -Wall -g

# Source files 
SRC = memtest.c editmalloc.c

# Name of the executable
TARGET = memtest


# Build target
all: $(TARGET)

$(TARGET): 
	$(CC) -o $@ $(SRC) $(CFLAGS)

# No testing neccesary, I assume that will be done by the grader

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

# Source files and Object files
# This grabs all .c files in src/ and turns them into .o files
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

# The name of your final program
TARGET = myshell

# 1. The Default Rule: Type 'make' to build this
all: $(TARGET)

# 2. Linking: How to join .o files into the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# 3. Compiling: How to turn .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 4. Clean: Type 'make clean' to remove garbage files
clean:
	rm -f $(OBJS) $(TARGET)


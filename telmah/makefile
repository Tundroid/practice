# Makefile

# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -std=c99 -pedantic
LFLAGS =

# Source files
SRCS = main.c utils.c

# Header files
HDRS = nana.h

# Object files
OBJS = $(SRCS:.c=.o)

# Executable
EXEC = nana

# Default target
all: $(OBJS) $(EXEC)

# Compile object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files
$(EXEC):
	$(CC) $(LFLAGS) $(OBJS) -o $@

# Clean
clean:
	rm -f *.o $(EXEC)

# Run
run: $(EXEC)
	./$(EXEC)

# Dependencies
main.o: nana.h
utils.o: nana.h
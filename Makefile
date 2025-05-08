# Compiler
CC = gcc 

# Compiler flags
CFLAGS = -Wall  -std=c11 
#-fsanitize=address

# Source files
SRC = parser.c 

# Object files
OBJ = $(SRC:.c=.o)

# Executable name
EXEC = parser

# Include directories
INCLUDES = -I.

# Libraries
LIBS =

# Main target
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXEC) $(OBJ) $(LIBS)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(EXEC)

#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./parser 

CC=gcc

CFLAGS = -Wall -g -std=gnu99
LDFLAGS = -lpthread -g
SRC = counter.c

TARGET = counter


all: $(TARGET)

# Define all object files.
OBJ = $(SRC:.c=.o)

# rule to link the program
$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile: create object files from C source files.
%.o : %.c
	$(CC) $(CFLAGS) -c  $< -o $@ 

# rule for cleaning re-compilable files.
clean:
	rm -f $(TARGET) $(OBJ)

rebuild:	clean all

build_spawner: all
	$(CC) spawner.c -o spawner $(LDFLAGS)

clean_spawner:
	rm -f spawner

.PHONY: all rebuild clean counter spawner


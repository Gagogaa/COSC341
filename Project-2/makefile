CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = compiler

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)

run: all
	./$(TARGET)

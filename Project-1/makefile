CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = program

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)

run: all
	./$(TARGET)

format: all
	uncrustify -c uncrustify.cfg $(TARGET).c

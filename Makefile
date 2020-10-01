CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11
TARGET = milli-stress

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm $(TARGET)

CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = q1 q2

all: $(TARGET)

$(TARGET): %: %.c
	$(CC) $(CFLAG) -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

CC = gcc
CFLAG = -std=c11 -O2 -Wall -fsanitize=undefined
TARGET = assignment5
SRCS = assignment5.c
OBJS = assignment5.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS) 

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

CC = gcc
CFLAG = -std=c11 -O2 -Wall -pthread
TARGET = assignment9
SRCS = assignment9.c
OBJS = assignment9.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS) 

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

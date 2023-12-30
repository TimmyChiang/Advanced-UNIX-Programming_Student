CC = gcc
CFLAG = -std=c11 -pthread -O2 -Wall
TARGET1 = q1
SRCS1 = q1.c
OBJS1 = q1.o

TARGET2 = q2
SRCS2 = q2.c
OBJS2 = q2.o

TARGET3 = q3
SRCS3 = q3.c
OBJS3 = q3.o

all: $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1): $(OBJS1)
	$(CC) $(CFLAG) -o $(TARGET1) $(OBJS1)

$(TARGET2): $(OBJS2)
	$(CC) $(CFLAG) -o $(TARGET2) $(OBJS2) 

$(TARGET3): $(OBJS3)
	$(CC) $(CFLAG) -o $(TARGET3) $(OBJS3) 

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJS1) $(TARGET1)


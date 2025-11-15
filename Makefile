CC = gcc
CFLAGS = -Wall -g -std=c11 
TARGET = music_app

SRCS = main.c album.c library.c playlist.c
HDRS = album.h library.h playlist.h struct.h

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
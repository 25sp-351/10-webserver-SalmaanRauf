# basic makefile for our http server
CC       = gcc
CFLAGS   = -Wall -g -Iinclude
LDFLAGS  = -pthread

# all the source files we need
SRCS = src/main.c \
       src/request_parser.c \
       src/router.c \
       src/response_builder.c \
       src/util.c \
       src/handlers/static_handler.c \
       src/handlers/calc_handler.c

# convert .c to .o automatically
OBJS = $(SRCS:.c=.o)
TARGET = http_server

# default target
all: $(TARGET)

# link everything together
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# compile rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# remove all the generated files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean 
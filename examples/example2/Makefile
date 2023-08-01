CC = gcc
CFLAGS = -w -Wall -Wextra -std=c99
LDFLAGS = -lm

TARGET = example2
SRCS = example2.c
LIBS = ../../textMath.c
OBJS = $(SRCS:.c)

ifeq ($(shell uname),Darwin)
	LDFLAGS += -Wl,-no_compact_unwind
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) $(LIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

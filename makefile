CC := gcc
CFLAGS := -Wall -Wextra -Iinclude
DIRS := src gui cli
SRCS := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))
OBJS := $(SRCS:.c=.o)
TARGET := myprog

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

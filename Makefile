TARGET = math
PREFIX = /usr/local/bin
SRCS = rn.c stor.c setting.c menu.c input.c operation.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall

.PHONY: all clean install uninstall

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

.c.o:
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)
install:
	install $(TARGET) $(PREFIX)
uninstall:
	rm -rf $(PREFIX)/$(TARGET)

all: main

CC = clang
override CFLAGS += -g -pthread -lm -Wno-int-conversion

SRCS = $(shell find src -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
HEADERS = $(shell find src -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

main: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o "$@"

main-debug: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@"

clean:
	rm -f main main-debug
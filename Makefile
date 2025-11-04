CC = gcc

TARGET = tidehit

CFLAGS = -Wall -Wextra -std=c99 -I. -Icli-lib/include
SRCS = tidehit.c game.c

LIB_SRCS = cli-lib/src/screen.c cli-lib/src/keyboard.c cli-lib/src/timer.c


OBJS = $(SRCS:.c=.o)
LIB_OBJS = $(LIB_SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS) $(LIB_OBJS)
	@echo "Linkando o jogo: $@"
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIB_OBJS)
	@echo "Pronto! Execute com: ./$(TARGET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Limpando..."
	rm -f $(TARGET) *.o cli-lib/src/*.o

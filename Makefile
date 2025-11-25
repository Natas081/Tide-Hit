TARGET = tidehit
CC = gcc
SRCS = tidehit.c game.c
OBJS = $(SRCS:.c=.o)


CFLAGS = -Wall -I. -g


LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)
	@echo "Pronto! Execute com: ./$(TARGET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

TARGET = tidehit
CC = gcc
SRCS = tidehit.c game.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Iraylib/src -I. -g

LIBS = raylib/src/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11
LDFLAGS =

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LIBS)
	@echo "Pronto! Execute com: ./$(TARGET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe

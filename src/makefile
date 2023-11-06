TARGET = main
CC = g++
CFLAGS = -O2

.PHONY: default all clean

default: $(TARGET)
all: clean default

main : main.o nim_game.o screen.o
	$(CC) $(CFLAGS) -o main main.o nim_game.o screen.o -lncurses

main.o : main.cpp nim_game.cpp nim_game.h screen.cpp screen.h libs.h
	$(CC) $(CFLAGS) -c  main.cpp

screen.o : screen.cpp screen.h libs.h
	$(CC) $(CFLAGS) -c screen.cpp

nim_game.o : nim_game.cpp nim_game.h libs.h
	$(CC) $(CFLAGS) -c nim_game.cpp

clean:
	-rm -f *.o
	-rm -f $(TARGET)


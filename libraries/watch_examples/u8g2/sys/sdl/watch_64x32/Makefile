CFLAGS = -std=c++11 -lstdc++ -g -Wall -I../../../csrc/.  `sdl-config --cflags`

SRC = $(shell ls ../../../csrc/*.c) $(shell ls ../common/*.c ) main.cpp 

OBJ = $(SRC:.c=.o)

main: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) `sdl-config --libs` -o watch_64x32

clean:	
	-rm $(OBJ) watch_64x32


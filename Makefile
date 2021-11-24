all: board.cpp board.h
	g++ board.cpp -o board

clean:
	rm board
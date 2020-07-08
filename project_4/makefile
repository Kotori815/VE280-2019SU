quarto.o: quarto.cpp
	g++ -c quarto.cpp

exceptions.o: exceptions.cpp
	g++ -c exceptions.cpp

piece.o: piece.cpp
	g++ -c piece.cpp

pool.o: pool.cpp
	g++ -c pool.cpp

square.o: square.cpp
	g++ -c square.cpp

board.o: board.cpp
	g++ -c board.cpp

player.o: player.cpp
	g++ -c player.cpp
	
game.o: game.cpp
	g++ -c game.cpp

test.o: test.cpp
	g++ -c test.cpp
	
gameall: game.o board.o exceptions.o piece.o player.o pool.o quarto.o square.o
	g++ -Wall -std=c++11 -o game game.o board.o exceptions.o piece.o player.o pool.o quarto.o square.o

testall: test.o board.o test.cpp exceptions.o piece.o player.o pool.o quarto.o square.o
	g++ -Wall -std=c++11 -o test test.o board.o exceptions.o piece.o player.o pool.o quarto.o square.o
	
test: test.cpp board.cpp exceptions.cpp piece.cpp player.cpp pool.cpp quarto.cpp square.cpp
	g++ -Wall -std=c++11 -o test test.cpp board.cpp exceptions.cpp piece.cpp player.cpp pool.cpp quarto.cpp square.cpp
	
game: game.cpp board.cpp exceptions.cpp piece.cpp player.cpp pool.cpp quarto.cpp square.cpp
	g++ -Wall -std=c++11 -o game game.cpp board.cpp exceptions.cpp piece.cpp player.cpp pool.cpp quarto.cpp square.cpp
	
clean: 
	rm -f game *.o game test



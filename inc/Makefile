CPPFLAGS= -c -g -Iinc -Wall -pedantic -std=c++17 

__start__: clear Checkers
	./Checkers

Checkers: 
	g++ -o Checkers src/main.cpp inc/Board.h -lpthread -lsfml-graphics -lsfml-window -lsfml-system
	
Driver: 
	g++ -o Driver src/driver.cpp inc/Board.h -lpthread

clear:
	rm -f obj/*.o Checkers

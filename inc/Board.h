#ifndef BOARD_H
#define BOARD_H

#include <math.h>
#include "MyMath.h"
#include <iostream>

enum field
{
	blackKing = -2,
	black = -1,
	empty = 0,
	white = 1,
	whiteKing = 2,
	outOfBounds = 101,
	outOfPlay = 102
};

/*

7| X X X X|
6|X X X X |
5| X X X X|
4|        |
3|        |
2|O O O O |
1| O O O O|
0|O O O O |
  01234567
  
*/

class Board {
private:
	field board[4][8];
	int draw;
public:
	bool whiteTurn; 
	
	//Konstruktor poczatkowej planszy
	Board():draw(0),whiteTurn(true){
		//whiteTurn = true;
		//draw = 0;
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				if (j < 3)
				set(i, j, white);
				else if (j >= 5)
				set(i, j, black);
				else
				set(i, j, empty);
			}
		}
	}
		
	//konstruktor kopiujacy
	Board(const Board & board2){
		whiteTurn = board2.whiteTurn;
		draw = board2.draw;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				set(i, j, board2.getSafe(i, j));
	}	
	
	//Wyswietlenie planszy w konsoli
	void print(bool all = false) const{
		for (int j = 7; j >= 0; j--)
		{
			for (int i = 0; i < 8; i++)
			{
				if (i == 0) std::cout << j << "|";
				switch(getSafe(i,j))
				{
					case white: 	std::cout << "O"; break;
					case whiteKing: std::cout << "@"; break;
					case black: 	std::cout << "X"; break;
					case blackKing: std::cout << "Y"; break;
					case empty: 	std::cout << "_"; break;
					case outOfPlay: std::cout << " "; break;
					default: std::cout << "E"; break;
				}
			}
			std::cout << std::endl;
		}
		std::cout << "  "; for (int i = 0; i < 8; i++) std::cout << "-"; 	std::cout << std::endl;
		std::cout << "  "; for (int i = 0; i < 8; i++) std::cout << i;		std::cout << std::endl;
		
		if (all)
		{
			if (whiteTurn) std::cout << "White's turn" << std::endl;
			else std::cout << "Black's turn" << std::endl;
			
			std::cout << "Count of legal moves: " << countOfLegalMoves() << std::endl;
			if (canCapture()) std::cout << "You have to capture!"  << std::endl;
		}
	}
	
	//Zwrocenie wartosci na danym poly w bezpieczny sposob, aby nie wyjsc poza tablice przypadkiem
	field getSafe(int x, int y) const{
		if (x < 0 || x > 7) return outOfBounds;
		if (y < 0 || y > 7) return outOfBounds;
		if ((x+y) % 2 == 1) return outOfPlay;
		return board[x/2][y];
	}
	
	//zwracanie wartosci ilosci ruchow, ktorymi sie wyznacza remis
	int getDraw() const{
		return draw;
	}
	
	//ustalenie wartosci pola
	bool set(int x, int y, const field & a){
		if (!active(x, y)) return false;
		
		board[x/2][y] = a;
		return true;
	}
	
	//sprawdzanie czy plansze sa takie same
	bool sameBoard(const Board & board2) const{
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				if(getSafe(i,j) != board2.getSafe(i,j)){
					return false;
				}
			}	
		}
		return true;
	}
	
	bool operator == (const Board & board2) const {return sameBoard(board2);}
	
	//sprawdzenie czy pole jest w grze
	bool active(int x, int y) const{
		return !(getSafe(x,y) == outOfBounds || getSafe(x,y) == outOfPlay);
	}
	
	//sprawdzanie czy pole jest zajete przez przeciwnika
	bool isEnemy(int x, int y) const{
		if (whiteTurn) return getSafe(x,y) == black || getSafe(x,y) == blackKing;
		return getSafe(x,y) == white || getSafe(x,y) == whiteKing;
	}
	
	//sprawdzanie czy pole jest zajete przez przyjaznego pionka
	bool isFriendly(int x, int y) const{
		if (whiteTurn) return getSafe(x,y) == white || getSafe(x,y) == whiteKing;
		return getSafe(x,y) == black || getSafe(x,y) == blackKing;
	}
	
	//otrzymanie informacji, w ktora strone ida pionki w danej turze
	int direction() const{
		return whiteTurn?1:-1;
	}
	
	//sprawdzanie czy mozliwe jest bicie w danej turze
	bool canCapture() const{
		for (int j = 0; j < 8; j++){
			for (int i = 0; i < 8; i++){
				if (isFriendly(i,j) && canCapture(i, j)) return true;
			}
		}
		return false;
	}
	
	//sprawdzanie czy dana bierka moze bic
	bool canCapture(int x, int y) const{
		if (!isFriendly(x,y)) return false;
		//Damka
		if (getSafe(x,y) == whiteKing || getSafe(x,y) == blackKing){
			for (int i = -1; i <= 1; i+=2){
				for (int j = -1; j <= 1; j+=2){
					if (legalCapture(x, y, x+i*2, y+j*2)) return true;
				}
			}
		}
		//Pion
		else if (getSafe(x,y) == white || getSafe(x,y) == black){
			for (int i = -1; i <= 1; i+=2){
				if (legalCapture(x, y, x+i*2, y+direction()*2)) return true;
			}
		}
		return false;
	}
	
	//sprawdzanie czy dane bicie jest legalne
	bool legalCapture(int x1, int y1, int x2, int y2) const{
		if (getSafe(x1,y1) == white || getSafe(x1,y1) == black)
			if (getSafe(x2,y2) == empty && abs(x2-x1) == 2 && y2-y1 == 2*direction() && isEnemy(x1+sign(x2-x1),y1+sign(y2-y1))) return true;
			else return false;
		//Damka
		else if (getSafe(x1,y1) == whiteKing || getSafe(x1,y1) == blackKing)
			if (getSafe(x2,y2) == empty && abs(x2-x1) == 2 && abs(y2-y1) == 2 && isEnemy(x1+sign(x2-x1),y1+sign(y2-y1))) return true;
			else return false;
		return false;
	}
	
	//zliczenie mozliwych bic prze bierke
	int countCaptures(int x, int y) const{
		int counter = 0;
		//Damka
		if (getSafe(x,y) == whiteKing || getSafe(x,y) == blackKing){
			for (int i = -1; i <= 1; i+=2){
				for (int j = -1; j <= 1; j+=2){
					if (isEnemy(x+i, y+j) && getSafe(x+i*2,y+j*2) == empty) counter++;
				}
			}
		}
		//Pion
		else if (getSafe(x,y) == white || getSafe(x,y) == black){
			for (int i = -1; i <= 1; i+=2){
				if (isEnemy(x+i, y+direction()) && getSafe(x+i*2,y+direction()*2) == empty) counter++;
			}
		}
		
		return counter;
	}
	
	//sprawdzanie czy mozliwe jest przesuniecie bierki wraz ze sprawdzeniem czy jest bicie
	bool canStepSafe() const{
		if (canCapture()) return false;
		return canStep();
	}
	//sprawdzanie czy mozliwe jest przesuniecie bierki bez sprawdzenia czy jest bicie
	bool canStep() const{
		for (int j = 0; j < 8; j++){
			for (int i = 0; i < 8; i++){
				if (isFriendly(i,j) && canStep(i, j)) return true;
			}
		}
		return false;
	}
	
	//sprawdzanie czy bierka moze wykonac ruch wraz ze sprawdzeniem czy jest bicie
	bool canStepSafe(int x, int y) const{
		if (canCapture()) return false;
		return canStep(x,y);
	}
	
	//sprawdzanie czy bierka moze wykonac ruch bez sprawdzenia czy jest bicie
	bool canStep(int x, int y) const{
		if (!isFriendly(x,y)) return false;
		//Trzeba najpierw bic
		//if (canCapture()) return false;
		//Pion
		if (getSafe(x,y) == white || getSafe(x,y) == black)
			for (int i = -1; i <= 1; i+=2){
				if (legalStep(x,y,x+i,y+direction())) return true;
			}
		//Damka
		if (getSafe(x,y) == whiteKing || getSafe(x,y) == blackKing)
			for (int i = -1; i <= 1; i+=2)
				for (int j = -1; j <= 1; j+=2){
					if (legalStep(x,y,x+i,y+j)) return true;
				}

		return false;
	}
	//sprawdzanie czy dane przsuniecie pionka jest legalne
	bool legalStep(int x1, int y1, int x2, int y2) const
	{
		if (getSafe(x1,y1) == white || getSafe(x1,y1) == black)
			if (getSafe(x2,y2) == empty && abs(x2-x1) == 1 && y2-y1 == direction()) return true;
			else return false;
		//Damka
		else if (getSafe(x1,y1) == whiteKing || getSafe(x1,y1) == blackKing)
			if (getSafe(x2,y2) == empty && abs(x2-x1) == 1 && abs(y2-y1) == 1) return true;
			else return false;
		return false;
	}
	//policzenie mozliwych ruchow
	int countSteps(int x, int y) const{
		int counter = 0;
		//Trzeba najpierw bic
		if (canCapture()) return counter;
		//Pion
		if (getSafe(x,y) == white || getSafe(x,y) == black)
			for (int i = -1; i <= 1; i+=2){
				if (legalStep(x,y,x+i,y+direction())) counter++;
			}
		//Damka
		else if (getSafe(x,y) == whiteKing || getSafe(x,y) == blackKing)
			for (int i = -1; i <= 1; i+=2)
				for (int j = -1; j <= 1; j+=2){
					if (legalStep(x,y,x+i,y+j) == empty) counter++;
				}
		return counter;
	}
	//wykonanie ruchu
	bool move(int x1, int y1, int x2, int y2)
	{
		if (getSafe(x2,y2) != empty) return false;
	
		if (getSafe(x1,y1) == white || getSafe(x1,y1) == black){
			//normalny ruch
			if (abs(x2-x1) == 1 && y2-y1 == direction() && canStepSafe(x1,y1)){
				set(x1,y1,empty);
				set(x2,y2,whiteTurn?white:black);
				draw = 0;
			}
			//bicie
			else if (abs(x2-x1) == 2 && y2-y1 == 2*direction() && isEnemy(x1+sign(x2-x1), y1+sign(y2-y1)))
			{
				set(x1,y1,empty);
				set(x1+sign(x2-x1),y1+sign(y2-y1),empty);
				set(x2,y2,whiteTurn?white:black);
				draw = 0;
			} else return false;
		} else if (getSafe(x1,y1) == whiteKing || getSafe(x1,y1) == blackKing){
			//normalny ruch
			if (abs(x2-x1) == 1 && abs(y2-y1) == 1 && canStepSafe(x1,y1)){
				set(x1,y1,empty);
				set(x2,y2,whiteTurn?whiteKing:blackKing);
				draw++;
			}
			//bicie
			else if (abs(x2-x1) == 2 && abs(y2-y1) == 2 && isEnemy(x1+sign(x2-x1), y1+sign(y2-y1))){
				set(x1,y1,empty);
				set(x1+sign(x2-x1),y1+sign(y2-y1),empty);
				set(x2,y2,whiteTurn?whiteKing:blackKing);
				draw = 0;
			} else return false;
		} else false;
		return true;
	}
	//ilosc legalnych ruchow
	int countOfLegalMoves() const{
		int counter = 0;
		if (canCapture()){
			for (int j = 0; j < 8; j++)
				for (int i = 0; i < 8; i++)
					if (isFriendly(i,j)){
						int temp = countCaptures(i,j);
						counter += temp;
					}
		}
		else{
			for (int j = 0; j < 8; j++)
				for (int i = 0; i < 8; i++)
					if (isFriendly(i,j)){
						int temp = countSteps(i,j);
						counter += temp;
						//if (countMoves(i,j) > 0) std::cout << "Moves: " << countMoves(i,j) << " i: " << i << " j: " << j << std::endl;
					}
		}
		return counter;
	}
	//sprawdzenie czy nie ma promocji
	void checkPromotion(){
		for (int i = 1; i < 8; i += 2) 
		if (getSafe(i,7) == white) set(i,7,whiteKing); 
		
		for (int i = 0; i < 8; i += 2) 
		if (getSafe(i,0) == black) set(i,0,blackKing); 
	}
	//sprawdzenie czy nie ma remisu
	bool isDraw() const{
		return draw >= 40;
	}
	//sprawdzenie czy nie ma konca gry
	bool end() const{
		if (isDraw()) return true;
		if (canStep() || canCapture()) return false;
		return true;
	}
};



#endif


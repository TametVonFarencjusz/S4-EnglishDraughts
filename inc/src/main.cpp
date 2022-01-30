#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string>

#include "../inc/Board.h"
#include "../inc/AI.h"
#include "../inc/Graphics.h"

#include <SFML/Graphics.hpp>

enum State{
	start, play, end
};

Graphics gfx;																		//Tworzenie obiektu grafik
int mouseTileX1 = -1, mouseTileY1 = -1, mouseTileX2 = -1, mouseTileY2 = -1;

int main()
{
    Board board;
    int depthAI = -1;
    State state = start;
    StarTech * ptrAI;
	
	bool players[2] = { true, false };
	
	//if (!gfx.LoadAll(1)) return -1;
	
	bool flagCanChangePiece = true;
	bool flagCapture = false;
	while (gfx.IsWindowOpen()){ //pętla trwająca dopóki jest otwarte okno
		//***Sprawdzanie czy została otrzymana proźba o zamknięcie okna (np. wciśnięcie X na pasku okna)***//
	    sf::Event event;
		gfx.PollEvent(event);
		
		if (state == start){ //Wybor poziomu trudnosci
			gfx.drawStart(board); //funkcja rysujaca plansze
			
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					int mouseTileX = event.mouseButton.x;
					int mouseTileY = event.mouseButton.y;
					//std::cout << "work";
					if(mouseTileX >= 300 && mouseTileX <= 500){
						if (mouseTileY >= 100 && mouseTileY <= 250) depthAI = 2;
						if (mouseTileY >= 300 && mouseTileY <= 450) depthAI = 5;
						if (mouseTileY >= 500 && mouseTileY <= 650) depthAI = 8;
					}
				}
			}
						
			if (depthAI != -1){ 
				state = play;
				ptrAI = new StarTech(depthAI, false);
			}
 		}
		else if(state == play){ //Gra
			//****************************GRACZ********************************************//
			if ((board.whiteTurn && players[0]) || (!board.whiteTurn && players[1])){
				//Mysz
				if (event.type == sf::Event::MouseButtonPressed){
					if (event.mouseButton.button == sf::Mouse::Left){
						int mouseTileX = event.mouseButton.x/100;
						int mouseTileY = 7-event.mouseButton.y/100;
						if (board.isFriendly(mouseTileX, mouseTileY) && flagCanChangePiece)
						{
							mouseTileX1 = event.mouseButton.x/100;
							mouseTileY1 = 7-event.mouseButton.y/100;
						}
						else if(board.getSafe(mouseTileX, mouseTileY) == empty && mouseTileX1 != -1 && mouseTileY1 != -1)
						{
							mouseTileX2 = event.mouseButton.x/100;
							mouseTileY2 = 7-event.mouseButton.y/100;
						}
					}
				}
				
				bool flagMoveEnd = false;
				bool legalMove = false;
				if (mouseTileX1 != -1 && mouseTileY1 != -1 && mouseTileX2 != -1 && mouseTileY2 != -1 && !flagCapture){
					legalMove = board.move(mouseTileX1, mouseTileY1, mouseTileX2, mouseTileY2);
					if (legalMove){
						flagCapture = abs(mouseTileX2-mouseTileX1) == 2 && abs(mouseTileY2-mouseTileY1) == 2;
						
						mouseTileX1 = mouseTileX2;
						mouseTileY1 = mouseTileY2;
						
						flagCanChangePiece = false;
						flagMoveEnd = !board.canCapture(mouseTileX1, mouseTileY1) || !flagCapture;;
					}
					mouseTileX2 = -1;
					mouseTileY2 = -1;
					
				}
				if (flagCapture && mouseTileX2 != -1 && mouseTileY2 != -1 && !flagMoveEnd){
		  			legalMove = board.move(mouseTileX1, mouseTileY1, mouseTileX2, mouseTileY2);
		  			if (legalMove){
						flagCapture = abs(mouseTileX2-mouseTileX1) == 2 && abs(mouseTileY2-mouseTileY1) == 2;
						
						mouseTileX1 = mouseTileX2;
						mouseTileY1 = mouseTileY2;
						
						flagCanChangePiece = false;
						
						flagMoveEnd = !board.canCapture(mouseTileX1, mouseTileY1) || !flagCapture;
					}
					mouseTileX2 = -1;
					mouseTileY2 = -1;
		  		}
				
				if (flagMoveEnd){
					board.whiteTurn = !board.whiteTurn;
					board.checkPromotion();
					
					flagCanChangePiece = true;
					flagCapture = false;
					flagMoveEnd = false;
					mouseTileX1 = -1;
					mouseTileY1 = -1;
				}
			} 
			else{
			//****************************SI********************************************//
				if (!board.end()){
					gfx.WindowDisplay();
					board = ptrAI->play(board);
				}
			}
			
			//************************************************************************//
			gfx.drawBoard(board,mouseTileX1, mouseTileY1); //funkcja rysujaca plansze
			//************************************************************************//
			
			if (board.end()) //Koniec gry
			{
				sf::sleep(sf::milliseconds(2000));
				state = end;
			}
		}
		else{
			gfx.drawEnd(board);
		}
	}
	delete ptrAI;
}


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string>

#include "../inc/Board.h"
#include "../inc/AI.h"

#include <SFML/Graphics.hpp>

enum State{
	start, play, end
};

sf::Image icon;
sf::Texture textureBoard, textureBoard2, textureWhite, textureWhiteKing, textureBlack, textureBlackKing, textureMark, textureMove, textureButton1, textureButton2, textureButton3;
sf::Font font; 																		//Tworzenie obiektu czcionki
sf::RenderWindow window(sf::VideoMode(800, 800), "Checkers by Szymon Startek"); 	//Utworzenie obiektu okna o wymiarach 800x800
int mouseTileX1 = -1, mouseTileY1 = -1, mouseTileX2 = -1, mouseTileY2 = -1;

bool loadTextures(){
	bool flagLoad = false;
	flagLoad = textureBoard.loadFromFile("sprites/Board.png", sf::IntRect(0, 0, 800, 800));		if (!flagLoad) return false;
	flagLoad = textureBoard2.loadFromFile("sprites/Board2.png", sf::IntRect(0, 0, 800, 800));	if (!flagLoad) return false;
	flagLoad = textureWhite.loadFromFile("sprites/White.png");									if (!flagLoad) return false;
	flagLoad = textureWhiteKing.loadFromFile("sprites/WhiteKing.png");							if (!flagLoad) return false;
	flagLoad = textureBlack.loadFromFile("sprites/Black.png");									if (!flagLoad) return false;
	flagLoad = textureBlackKing.loadFromFile("sprites/BlackKing.png");							if (!flagLoad) return false;
	flagLoad = textureMark.loadFromFile("sprites/Mark.png"); 									if (!flagLoad) return false;
	flagLoad = textureMove.loadFromFile("sprites/Move.png");									if (!flagLoad) return false;
	flagLoad = textureButton1.loadFromFile("sprites/Button1.png");								if (!flagLoad) return false;
	flagLoad = textureButton2.loadFromFile("sprites/Button2.png");								if (!flagLoad) return false;
	flagLoad = textureButton3.loadFromFile("sprites/Button3.png");								if (!flagLoad) return false;
	flagLoad = icon.loadFromFile("sprites/Icon.png");											if (!flagLoad) return false;
	return true;
}

int drawStart(const Board & board){
	//************************//
	window.clear();	//Wyczyszczenie okna "window" ze wszystkich obiektów, aby móc narysowane nowe metodą "draw"	
	//************************//
	sf::Sprite sprite;
	sprite.setTexture(textureBoard2); 	
	sprite.setPosition(sf::Vector2f(0,0)); 
	window.draw(sprite);
	
	sf::Sprite sprite2;
	sprite2.setTexture(textureButton1); 
	sprite2.setPosition(sf::Vector2f(300,100)); 
	window.draw(sprite2);
	
	sprite2.setTexture(textureButton2); 
	sprite2.setPosition(sf::Vector2f(300,300)); 
	window.draw(sprite2);

	sprite2.setTexture(textureButton3); 
	sprite2.setPosition(sf::Vector2f(300,500)); 
	window.draw(sprite2);
	
	//************************//
	window.display();		//Wyświetlenie w oknie "window" wszystkich obiektów, które zostały narysowane metodą "draw"
	//************************//
	
	return -1;
}

void drawEnd(const Board & board){
	//************************//
	window.clear();	//Wyczyszczenie okna "window" ze wszystkich obiektów, aby móc narysowane nowe metodą "draw"	
	//************************//
	
	if (board.isDraw()){
		sf::Text message("Draw: 40 move rule", font);		//Tworzenie obiektu wiadomości
		message.move(300.f, 400.f);									//Pozycja wiadomości w oknie
		window.draw(message);	
	} 
	else if(board.whiteTurn){
		sf::Text message("Black wins", font);		//Tworzenie obiektu wiadomości
		message.move(300.f, 400.f);					//Pozycja wiadomości w oknie
		window.draw(message);	
	} 
	else{
		sf::Text message("White wins", font);		//Tworzenie obiektu wiadomości
		message.move(300.f, 400.f);					//Pozycja wiadomości w oknie
		window.draw(message);	
	}
	
	//************************//
	window.display();		//Wyświetlenie w oknie "window" wszystkich obiektów, które zostały narysowane metodą "draw"
	//************************//
}

void drawBoard(const Board & board){
	//************************//
	window.clear();	//Wyczyszczenie okna "window" ze wszystkich obiektów, aby móc narysowane nowe metodą "draw"	
	//************************//
	sf::Sprite sprite;
	sprite.setTexture(textureBoard); 	
	sprite.setPosition(sf::Vector2f(0,0)); 
	window.draw(sprite);
	
	sf::Sprite sprite2;
	for (int j = 7; j >= 0; j--){
		for (int i = 0; i < 8; i++){
			switch(board.getSafe(i,j)){
				case white: 	sprite2.setTexture(textureWhite); 		sprite2.setPosition(sf::Vector2f(i*100,700-j*100)); window.draw(sprite2); break;
				case whiteKing: sprite2.setTexture(textureWhiteKing); 	sprite2.setPosition(sf::Vector2f(i*100,700-j*100)); window.draw(sprite2); break;
				case black: 	sprite2.setTexture(textureBlack); 		sprite2.setPosition(sf::Vector2f(i*100,700-j*100)); window.draw(sprite2); break;
				case blackKing: sprite2.setTexture(textureBlackKing); 	sprite2.setPosition(sf::Vector2f(i*100,700-j*100)); window.draw(sprite2); break;
			}
		}
	}
	
	sf::Sprite sprite3;
	if (mouseTileX1 != -1 && mouseTileY1 != -1){
		sprite3.setTexture(textureMark); 		
		sprite3.setPosition(sf::Vector2f(mouseTileX1*100,700-mouseTileY1*100)); 
		window.draw(sprite3);
	}
	
	//************************//
	window.display();		//Wyświetlenie w oknie "window" wszystkich obiektów, które zostały narysowane metodą "draw"
	//************************//
}

int main()
{
    Board board;
    int depthAI = -1;
    State state = start;
    StarTech * ptrAI;
    //StarTech ai2(5, true);
	
	if (!loadTextures()){
		std::cout << "ERROR: Texture not loaded\n";
		return -1;
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());	//Ustawianie wczytanego obrazu jako ikona okna
	
	if (!font.loadFromFile("font/arial.ttf")){ 	//Wczytywanie czcionki "arial.tff" z pliku
		std::cerr << "ERROR: Font not found" << std::endl; 	//Błąd przy wczytywaniu pliku: Brak pliku z czcionką
	    return -1;						//Zakończenie programu z powodu nie znalezienia czcionki
	}
	
	bool flagCanChangePiece = true;
	bool flagCapture = false;
	while (window.isOpen()){ //pętla trwająca dopóki jest otwarte okno
		//***Sprawdzanie czy została otrzymana proźba o zamknięcie okna (np. wciśnięcie X na pasku okna)***//
	    sf::Event event;
	    while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) window.close();
		}
		
		if (state == start){ //Wybor poziomu trudnosci
			drawStart(board); //funkcja rysujaca plansze
			
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
				ptrAI = new StarTech(depthAI);
			}
 		}
		else if(state == play){ //Gra
			//****************************GRACZ********************************************//
			if (board.whiteTurn){
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
				/*if (!board.end()){
					window.display();
					board = ai2.play(board);
				}*/
			} 
			else{
			//****************************SI********************************************//
				if (!board.end()){
					window.display();
					board = ptrAI->play(board);
				}
			}
			
			//************************************************************************//
			drawBoard(board); //funkcja rysujaca plansze
			//************************************************************************//
			
			if (board.end()) //Koniec gry
			{
				sf::sleep(sf::milliseconds(2000));
				state = end;
			}
		}
		else{
			drawEnd(board);
		}
	}
	delete ptrAI;
}


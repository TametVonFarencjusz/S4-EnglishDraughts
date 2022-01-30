#include <stdlib.h>
#include <vector>
#include <SFML/Graphics.hpp>

class Graphics {
	private:
		sf::RenderWindow window;
		sf::Texture textureBoard, textureBoard2, textureWhite, textureWhiteKing, textureBlack, textureBlackKing, textureMark, textureMove, textureButton1, textureButton2, textureButton3;
		sf::Image icon;
		sf::Font font; 
	public:
		Graphics(int style = 0) : window(sf::VideoMode(800, 800), "Checkers by Szymon Startek") //Utworzenie obiektu okna o wymiarach 800x800
		{
			LoadAll(style);
		}
		
	bool LoadTextures(int style = 0)
	{
		if (style == 0)
		{
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
		} 
		else if (style == 1)
		{
			bool flagLoad = false;
			flagLoad = textureBoard.loadFromFile("sprites/Texture2/Board.png", sf::IntRect(0, 0, 800, 800));
			flagLoad = textureBoard2.loadFromFile("sprites/Texture2/Board2.png", sf::IntRect(0, 0, 800, 800));
			flagLoad = textureWhite.loadFromFile("sprites/Texture2/White.png");
			flagLoad = textureWhiteKing.loadFromFile("sprites/Texture2/WhiteKing.png");
			flagLoad = textureBlack.loadFromFile("sprites/Texture2/Black.png");
			flagLoad = textureBlackKing.loadFromFile("sprites/Texture2/BlackKing.png");
			flagLoad = textureMark.loadFromFile("sprites/Texture2/Mark.png");
			flagLoad = textureMove.loadFromFile("sprites/Texture2/Move.png");
			flagLoad = textureButton1.loadFromFile("sprites/Texture2/Button1.png");
			flagLoad = textureButton2.loadFromFile("sprites/Texture2/Button2.png");
			flagLoad = textureButton3.loadFromFile("sprites/Texture2/Button3.png");
			flagLoad = icon.loadFromFile("sprites/Texture2/Icon.png");
		}
		return true;
	}
	
	bool IsWindowOpen() {
		return window.isOpen();
	}
	
	void WindowDisplay()
	{
		window.display();
	}
	
	void PollEvent(sf::Event & event)
	{
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) window.close();
		}
	}
	
		
	bool LoadAll(int style = 0)
	{
		if (!LoadTextures(1)){
			std::cerr << "ERROR: Texture not loaded\n";
			return false;
		}
		if (!font.loadFromFile("font/arial.ttf")){ 	//Wczytywanie czcionki "arial.tff" z pliku
			std::cerr << "ERROR: Font not found" << std::endl; 	//Błąd przy wczytywaniu pliku: Brak pliku z czcionką
			return false;						//Zakończenie programu z powodu nie znalezienia czcionki
		}
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());	//Ustawianie wczytanego obrazu jako ikona okna
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
	
	void drawBoard(const Board & board, int mouseTileX1, int mouseTileY1){
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
};

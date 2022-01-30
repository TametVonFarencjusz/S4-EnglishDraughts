#include <stdlib.h>
#include <vector>
#include <SFML/Graphics.hpp>

class Graphics {
	public:
		sf::Texture textureBoard, textureBoard2, textureWhite, textureWhiteKing, textureBlack, textureBlackKing, textureMark, textureMove, textureButton1, textureButton2, textureButton3;
		sf::Image icon;
		
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
		
};

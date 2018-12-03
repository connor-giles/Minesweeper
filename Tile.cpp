#include "Tile.h"


//Every tile needs a multiple sprites (either revelaed or hidden) etc.
//flags and numbers mine can take up same spot
//2 sprites (mine flags and numbers are one) (hidden or reveled is another)

//sprites are part of tile class


Tile::Tile() 
{
	isMine = false;
	tileState = TileState::Hidden;
	//adjMine;
}

Tile::Tile(sf::Texture &hiddenText, sf::Texture &revealedText, sf::Texture &flagText, sf::Texture &mineText, sf::Texture &num1, sf::Texture &num2, sf::Texture &num3, sf::Texture &num4, sf::Texture &num5, sf::Texture &num6, sf::Texture &num7, sf::Texture &num8) 
{
	hiddenTile.setTexture(hiddenText);
	revealedTile.setTexture(revealedText);
	flagTile.setTexture(flagText);
	mine.setTexture(mineText);
	number1.setTexture(num1);
	number2.setTexture(num2);
	number3.setTexture(num3);
	number4.setTexture(num4);
	number5.setTexture(num5);
	number6.setTexture(num6);
	number7.setTexture(num7);
	number8.setTexture(num8);
}



Tile::~Tile()
{

}

void Tile::TileIsMine() 
{
	isMine = true;
}

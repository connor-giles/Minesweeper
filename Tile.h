#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

struct Tile
{
	enum class TileState 
	{
		Hidden, Flagged, Revealed
	};

	//===== Variables =====//
	float xPos;
	float yPos;
	sf::Sprite hiddenTile; 
	sf::Sprite revealedTile; 
	sf::Sprite flagTile; 
	sf::Sprite mine;
	sf::Sprite number1, number2, number3, number4;
	sf::Sprite number5, number6, number7, number8;


	bool isMine; //determines if the tile is a mine
	bool isClicked; //determines if the tile has been clicked

	void TileIsMine(); //sets is mine to true

	TileState tileState;

	Tile();
	Tile(sf::Texture *, sf::Texture *, sf::Texture *, sf::Texture *, sf::Texture *, sf::Texture *, sf::Texture *, sf::Texture *, sf::Texture *, sf::Texture *, sf::Texture *, sf::Texture *);
	~Tile();




};


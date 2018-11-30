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
	sf::Sprite regularSprite; //can be either a hidden tile or a reveledd tile
	sf::Sprite flag; //can be a flag tile
	sf::Sprite contents; //can be any of the number 1-8 and a bomb
	bool isMine; //determines if the tile is a mine
	bool isClicked; //determines if the tile has been clicked

	TileState tilestate;

	Tile();
	~Tile();




};


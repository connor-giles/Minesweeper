#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
using namespace std;

struct Tile
{

	//===== Variables =====//
	float xPos;
	float yPos;
	int numOfAdjMines;

	sf::Sprite hiddenTile; 
	sf::Sprite revealedTile; 
	sf::Sprite flagTile; 
	sf::Sprite mine;
	sf::Sprite number1, number2, number3, number4;
	sf::Sprite number5, number6, number7, number8;

	bool isMine; //determines if the tile is a mine
	bool isFlag; //determines if the tile is a flag
	bool hasBeenLeftClicked; //determines if the tile has been clicked

	vector<Tile *> adjacentTiles;

	void TileIsMine(); //sets is mine to true

	Tile();

	//constructor that takes in all the textures as parameters
	Tile(sf::Texture &, sf::Texture &, sf::Texture &, sf::Texture &, sf::Texture &, sf::Texture &, sf::Texture &, sf::Texture &, sf::Texture &, sf::Texture &, sf::Texture &, sf::Texture &);
	
	//destructor
	~Tile();




};


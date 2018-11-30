#pragma once
#include "Tile.h"
#include <vector>
//needs data structure to hold tiles


struct Board
{
	enum class Mode 
	{
		Win, Lose, Play, Debug, Test1, Test2
	};
	
	//===Variables===//
	const int height = 16;
	const int width = 25;
	int numMines;
	int totalTiles = height * width;
	int numberFlagged;


	Mode mode; //makes a mode class object
	vector<vector<Tile>> gameBoardVector; // creates a 2d vector that starts in the upper left
	vector<Tile *> tileVec; //used in LoadTextures
	map<string, sf::Texture> imagesMap;


	Board();
	~Board();
	void MakeBoard(sf::RenderWindow&);
	void LoadTextures();

	
	

};


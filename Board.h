#pragma once
#include "Tile.h"
#include <random>
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
	int totalTiles;
	int numberFlagged;
	int tileWidth = 32; //this is the pixel width of one tile
	int tileClickedCounter = 0;

	int numberRevealed = 0;

	bool gameIsPlayable;


	sf::Sprite place1;
	sf::Sprite place2;
	sf::Sprite place3;
	sf::Sprite debugButton;
	sf::Sprite happyButton;
	sf::Sprite winButton;
	sf::Sprite loseButton;
	sf::Sprite test1;
	sf::Sprite test2;



	Mode currentGameMode; //makes a mode class object
	vector<vector<Tile>> gameBoardVector; // creates a 2d vector that starts in the upper left
	vector<Tile *> tileVec; //used in LoadTextures
	map<string, sf::Texture> imagesMap;


	Board();
	~Board();
	void MakeBoard(sf::RenderWindow&);
	void LoadTextures();
	void SetMines();
	void PlayDebugMode(sf::RenderWindow&);
	void PlayRegularMode(sf::RenderWindow&);
	void PlayWinMode(sf::RenderWindow&);
	void PlayLoseMode(sf::RenderWindow&);
	void ResetBoard();
	void CalculateAdjacentTiles();
	void CalculateAdjacentMines();
	void SetMiddleAdjTiles(int, int);
	void LoadTest1();
	void LoadTest2();
	void UpdateMineCount();
	bool GameWon();
		
};


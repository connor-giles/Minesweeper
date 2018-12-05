#include "Board.h"
#include "Tile.h"

mt19937 random_mt(time(0)); //potential loss of data?
int Random(int min, int max)
{
    uniform_int_distribution<int> dist(min, max);
    return dist(random_mt);
}

//int loseCounter = 0;

Board::Board() //populates the 2d vector used to make minesweeper board
{
	numMines = 0;
	numberFlagged = 0;
	totalTiles = height * width;
	gameIsPlayable = true;
	LoadTextures();

	//all this code below sets the textures for the sprites that on at the bottom of the game board, as well as their location
	//place1.setTexture(imagesMap["digits0"]);
	place1.setPosition(0.f, 16.f * tileWidth);

	//place2.setTexture(imagesMap["digits5"]);
	place2.setPosition(21.f, 16.f * tileWidth);

	//place3.setTexture(imagesMap["digits0"]);
	place3.setPosition(42.f, 16.f * tileWidth);

	debugButton.setTexture(imagesMap["debug"]);
	debugButton.setPosition(16.5f * tileWidth, 16.f * tileWidth);

	happyButton.setTexture(imagesMap["face_happy"]);
	happyButton.setPosition(11.5f * tileWidth, 16.f * tileWidth);

	loseButton.setTexture(imagesMap["face_lose"]);
	loseButton.setPosition(11.5f * tileWidth, 16.f * tileWidth);

	winButton.setTexture(imagesMap["face_win"]);
	winButton.setPosition(11.5f * tileWidth, 16.f * tileWidth);

	test1.setTexture(imagesMap["test_1"]);
	test1.setPosition(18.5f * tileWidth, 16.f * tileWidth);

	test2.setTexture(imagesMap["test_2"]);
	test2.setPosition(20.5f * tileWidth, 16.f * tileWidth);



	for (int i = 0; i < width; i++) 
	{
		vector<Tile> temptT;
		for (int j = 0; j < height; j++)
		{
			//this long constructor sets all of the textures of the tiles to their appropriate texture
			Tile tempTile(imagesMap["tile_hidden"], imagesMap["tile_revealed"], imagesMap["flag"], imagesMap["mine"], imagesMap["number_1"], imagesMap["number_2"], imagesMap["number_3"], imagesMap["number_4"], imagesMap["number_5"], imagesMap["number_6"], imagesMap["number_7"], imagesMap["number_8"]);
			tempTile.xPos = i;
			tempTile.yPos = j;
			tempTile.hiddenTile.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.revealedTile.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.flagTile.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.mine.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number1.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number2.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number3.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number4.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number5.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number6.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number7.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number8.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile

			temptT.push_back(tempTile);
		}

		gameBoardVector.push_back(temptT);

	}

	SetMines();
	totalTiles = totalTiles - numMines;
	CalculateAdjacentTiles(); //should calculate the tiles 
	CalculateAdjacentMines(); //should calculate the number of mines in the surrounding tiles
	UpdateMineCount();
	
	currentGameMode = Mode::Play;
}

Board::~Board()
{

}

void Board::MakeBoard(sf::RenderWindow& mainWindow)
{
	if (currentGameMode == Mode::Debug) 
	{
		PlayDebugMode(mainWindow);
	}
	 
	else if (currentGameMode == Mode::Test1) 
	{
		LoadTest1();
	}

	else if (currentGameMode == Mode::Test2)
	{
		LoadTest2();
	}

	else if (currentGameMode == Mode::Win) //might not need to be here
	{
		//do the stuff for Win
	}

	else if (currentGameMode == Mode::Lose) //might not need to be here
	{
		//do the stuff for Lose
		PlayLoseMode(mainWindow);
	}


	else //implies that the game is in Play mode
	{
		PlayRegularMode(mainWindow);
	}

}

void Board::LoadTextures()
{
	//this loads all the textures into a vector in preperation for them to be loaded 
	vector<sf::Texture> textureVec(28);
	textureVec[0].loadFromFile("images\\mine.png");
	textureVec[1].loadFromFile("images\\flag.png");
	textureVec[2].loadFromFile("images\\number_1.png");
	textureVec[3].loadFromFile("images\\number_2.png");
	textureVec[4].loadFromFile("images\\number_3.png");
	textureVec[5].loadFromFile("images\\number_4.png");
	textureVec[6].loadFromFile("images\\number_5.png");
	textureVec[7].loadFromFile("images\\number_6.png");
	textureVec[8].loadFromFile("images\\number_7.png");
	textureVec[9].loadFromFile("images\\number_8.png");
	textureVec[10].loadFromFile("images\\test_1.png");
	textureVec[11].loadFromFile("images\\test_2.png");
	textureVec[12].loadFromFile("images\\tile_hidden.png");
	textureVec[13].loadFromFile("images\\tile_revealed.png");
	textureVec[14].loadFromFile("images\\debug.png");
	textureVec[15].loadFromFile("images\\face_win.png");
	textureVec[16].loadFromFile("images\\face_happy.png");
	textureVec[17].loadFromFile("images\\face_lose.png");
	textureVec[18].loadFromFile("images\\digits.png", sf::IntRect(0, 0, 21, 32));   //digit 0
	textureVec[19].loadFromFile("images\\digits.png", sf::IntRect(21, 0, 21, 32));  //digit 1
	textureVec[20].loadFromFile("images\\digits.png", sf::IntRect(42, 0, 21, 32));  //digit 2
	textureVec[21].loadFromFile("images\\digits.png", sf::IntRect(63, 0, 21, 32));  //digit 3
	textureVec[22].loadFromFile("images\\digits.png", sf::IntRect(84, 0, 21, 32));  //digit 4
	textureVec[23].loadFromFile("images\\digits.png", sf::IntRect(105, 0, 21, 32)); //digit 5
	textureVec[24].loadFromFile("images\\digits.png", sf::IntRect(126, 0, 21, 32)); //digit 6
	textureVec[25].loadFromFile("images\\digits.png", sf::IntRect(147, 0, 21, 32)); //digit 7
	textureVec[26].loadFromFile("images\\digits.png", sf::IntRect(168, 0, 21, 32)); //digit 8
	textureVec[27].loadFromFile("images\\digits.png", sf::IntRect(189, 0, 21, 32)); //digit 9

	imagesMap.emplace("mine", textureVec[0]);
	imagesMap.emplace("flag", textureVec[1]);
	imagesMap.emplace("number_1", textureVec[2]);
	imagesMap.emplace("number_2", textureVec[3]);
	imagesMap.emplace("number_3", textureVec[4]);
	imagesMap.emplace("number_4", textureVec[5]);
	imagesMap.emplace("number_5", textureVec[6]);
	imagesMap.emplace("number_6", textureVec[7]);
	imagesMap.emplace("number_7", textureVec[8]);
	imagesMap.emplace("number_8", textureVec[9]);
	imagesMap.emplace("test_1", textureVec[10]);
	imagesMap.emplace("test_2", textureVec[11]);
	imagesMap.emplace("tile_hidden", textureVec[12]);
	imagesMap.emplace("tile_revealed", textureVec[13]);
	imagesMap.emplace("debug", textureVec[14]);
	imagesMap.emplace("face_win", textureVec[15]);
	imagesMap.emplace("face_happy", textureVec[16]);
	imagesMap.emplace("face_lose", textureVec[17]);
	imagesMap.emplace("digits0", textureVec[18]);
	imagesMap.emplace("digits1", textureVec[19]);
	imagesMap.emplace("digits2", textureVec[20]); 
	imagesMap.emplace("digits3", textureVec[21]);
	imagesMap.emplace("digits4", textureVec[22]);
	imagesMap.emplace("digits5", textureVec[23]);
	imagesMap.emplace("digits6", textureVec[24]);
	imagesMap.emplace("digits7", textureVec[25]);
	imagesMap.emplace("digits8", textureVec[26]);
	imagesMap.emplace("digits9", textureVec[27]);
	 
}
 
void Board::SetMines() //this function loops through the total number of mines and randomly assigns a mine to a certain location
{
	int tempMines = 50;

	while (tempMines != 0)
	{
		int x = Random(0, 24);
		int y = Random(0, 15);

		if (!gameBoardVector[x][y].isMine) //prevents 2 mines from being placed on top of each other
		{
			gameBoardVector[x][y].TileIsMine();
			tempMines--;
			numMines++;
		}

		

	}

}

void Board::RevealMines(sf::RenderWindow& mWindow)
{
	//needs to loop through whole board and reveal all the mines
	for (int k = 0; k < width; k++)
	{
		for (int l = 0; l < height; l++)
		{
			if (gameBoardVector[k][l].isMine)
			{
				mWindow.draw(gameBoardVector[k][l].revealedTile);
				mWindow.draw(gameBoardVector[k][l].mine);
			}
		}
	}



}

void Board::PlayDebugMode(sf::RenderWindow& dWindow)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{

			if (gameBoardVector[i][j].hasBeenLeftClicked && gameBoardVector[i][j].isMine) //checks if it was left clicked and a mine
			{
				currentGameMode = Mode::Lose;
				gameIsPlayable = false;
			}

			else if (gameBoardVector[i][j].isFlag && gameBoardVector[i][j].isMine)
			{
				dWindow.draw(gameBoardVector[i][j].hiddenTile); //draws a hidden tile at that location
				dWindow.draw(gameBoardVector[i][j].flagTile); //draws a flag tile at that location
				dWindow.draw(gameBoardVector[i][j].mine); //draws a mine tile at that 
			}

			else if (gameBoardVector[i][j].isMine)
			{
				dWindow.draw(gameBoardVector[i][j].hiddenTile); //draws a revealed tile at that location
				dWindow.draw(gameBoardVector[i][j].mine); //draws a mine tile at that location
			}
			
			else if (gameBoardVector[i][j].isFlag)
			{
				dWindow.draw(gameBoardVector[i][j].hiddenTile); //draws a hidden tile at that location
				dWindow.draw(gameBoardVector[i][j].flagTile); //draws a flag tile at that 
			}


			else if (gameBoardVector[i][j].hasBeenLeftClicked && !gameBoardVector[i][j].isMine) //checks if it was left clicked and not a mine
			{
				dWindow.draw(gameBoardVector[i][j].revealedTile); //draws a revealed tile at that location
				
				if (gameBoardVector[i][j].numOfAdjMines == 0) //this case should handle the cascade
				{
					for (int k = 0; k < gameBoardVector[i][j].adjacentTiles.size(); k++)
					{
						gameBoardVector[i][j].adjacentTiles[k]->hasBeenLeftClicked = true;
					}
				}
			
				else if (gameBoardVector[i][j].numOfAdjMines == 1)
				{
					dWindow.draw(gameBoardVector[i][j].number1); //draws a number1 tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 2)
				{
					dWindow.draw(gameBoardVector[i][j].number2); //draws a number2 tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 3)
				{
					dWindow.draw(gameBoardVector[i][j].number3); //draws a number3 tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 4)
				{
					dWindow.draw(gameBoardVector[i][j].number4); //draws a number4 tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 5)
				{
					dWindow.draw(gameBoardVector[i][j].number5); //draws a number5 tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 6)
				{
					dWindow.draw(gameBoardVector[i][j].number6); //draws a number6 tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 7)
				{
					dWindow.draw(gameBoardVector[i][j].number7); //draws a number7 tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 8)
				{
					dWindow.draw(gameBoardVector[i][j].number8); //draws a number8 tile at that location
				}
			}

			else
				dWindow.draw(gameBoardVector[i][j].hiddenTile); //draws a hidden tile at that location
		}
	}

	UpdateMineCount();

	//these draw the bottom buttons
	dWindow.draw(debugButton);
	dWindow.draw(test1);
	dWindow.draw(test2);
	dWindow.draw(place1);
	dWindow.draw(place2);
	dWindow.draw(place3);
	dWindow.draw(happyButton);
}

void Board::PlayLoseMode(sf::RenderWindow& lWindow)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (gameBoardVector[i][j].isMine)
			{
				lWindow.draw(gameBoardVector[i][j].revealedTile); //draws a revealed tile at that location
				lWindow.draw(gameBoardVector[i][j].mine); //draws a revealed tile at that location
			}

			else if (gameBoardVector[i][j].isFlag)
			{
				lWindow.draw(gameBoardVector[i][j].hiddenTile); //draws a hidden tile at that location
				lWindow.draw(gameBoardVector[i][j].flagTile); //draws a flag tile at that location
			}

			else if (gameBoardVector[i][j].hasBeenLeftClicked && !gameBoardVector[i][j].isMine) //checks if it was left clicked and not a mine
			{
				lWindow.draw(gameBoardVector[i][j].revealedTile); //draws a revealed tile at that location
				if (gameBoardVector[i][j].numOfAdjMines == 1)
				{
					lWindow.draw(gameBoardVector[i][j].number1); //draws a revealed tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 2)
				{
					lWindow.draw(gameBoardVector[i][j].number2); //draws a revealed tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 3)
				{
					lWindow.draw(gameBoardVector[i][j].number3); //draws a revealed tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 4)
				{
					lWindow.draw(gameBoardVector[i][j].number4); //draws a revealed tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 5)
				{
					lWindow.draw(gameBoardVector[i][j].number5); //draws a revealed tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 6)
				{
					lWindow.draw(gameBoardVector[i][j].number6); //draws a revealed tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 7)
				{
					lWindow.draw(gameBoardVector[i][j].number7); //draws a revealed tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 8)
				{
					lWindow.draw(gameBoardVector[i][j].number8); //draws a revealed tile at that location
				}
			}

			else
				lWindow.draw(gameBoardVector[i][j].hiddenTile); //draws a hidden tile at that location
		}
	}

	UpdateMineCount();

	//these draw the bottom buttons
	lWindow.draw(debugButton);
	lWindow.draw(test1);
	lWindow.draw(test2);
	lWindow.draw(place1);
	lWindow.draw(place2);
	lWindow.draw(place3);
	lWindow.draw(loseButton);
}

void Board::PlayRegularMode(sf::RenderWindow& rWindow)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (gameBoardVector[i][j].isMine && !gameBoardVector[i][j].hasBeenLeftClicked && !gameBoardVector[i][j].isFlag)
			{
				rWindow.draw(gameBoardVector[i][j].mine); //draws a revealed tile at that location
				rWindow.draw(gameBoardVector[i][j].hiddenTile); //draws a revealed tile at that location
			}

			if (gameBoardVector[i][j].isMine && !gameBoardVector[i][j].hasBeenLeftClicked && gameBoardVector[i][j].isFlag)
			{
				rWindow.draw(gameBoardVector[i][j].mine); //draws a revealed tile at that location
				rWindow.draw(gameBoardVector[i][j].hiddenTile); //draws a revealed tile at that location
				rWindow.draw(gameBoardVector[i][j].flagTile); //draws a revealed tile at that location
			}

			else if (gameBoardVector[i][j].isFlag)
			{
				rWindow.draw(gameBoardVector[i][j].hiddenTile); //draws a hidden tile at that location
				rWindow.draw(gameBoardVector[i][j].flagTile); //draws a flag tile at that location
			}

			else if (gameBoardVector[i][j].hasBeenLeftClicked && gameBoardVector[i][j].isMine) //checks if it was left clicked and a mine
			{
				currentGameMode = Mode::Lose;
				gameIsPlayable = false;
			}

			else if (gameBoardVector[i][j].hasBeenLeftClicked && !gameBoardVector[i][j].isMine) //checks if it was left clicked and not a mine
			{
				rWindow.draw(gameBoardVector[i][j].revealedTile); //draws a revealed tile at that location

			
				if (gameBoardVector[i][j].numOfAdjMines == 0) //this case should handle the cascade
				{
					for (int k = 0; k < gameBoardVector[i][j].adjacentTiles.size(); k++)
					{
						gameBoardVector[i][j].adjacentTiles[k]->hasBeenLeftClicked = true;
					}
				}


				if (gameBoardVector[i][j].numOfAdjMines == 1)
				{
					rWindow.draw(gameBoardVector[i][j].number1); //draws a revealed tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 2)
				{
					rWindow.draw(gameBoardVector[i][j].number2); //draws a revealed tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 3)
				{
					rWindow.draw(gameBoardVector[i][j].number3); //draws a revealed tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 4)
				{
					rWindow.draw(gameBoardVector[i][j].number4); //draws a revealed tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 5)
				{
					rWindow.draw(gameBoardVector[i][j].number5); //draws a revealed tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 6)
				{
					rWindow.draw(gameBoardVector[i][j].number6); //draws a revealed tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 7)
				{
					rWindow.draw(gameBoardVector[i][j].number7); //draws a revealed tile at that location
				}
				else if (gameBoardVector[i][j].numOfAdjMines == 8)
				{
					rWindow.draw(gameBoardVector[i][j].number8); //draws a revealed tile at that location
				}
			}

			else
				rWindow.draw(gameBoardVector[i][j].hiddenTile); //draws a hidden tile at that location
		}
	}

	UpdateMineCount();
 

	//these draw the bottom buttons
	rWindow.draw(debugButton);
	rWindow.draw(test1);
	rWindow.draw(test2);
	rWindow.draw(place1);
	rWindow.draw(place2);
	rWindow.draw(place3);
	rWindow.draw(happyButton);
}

void Board::ResetBoard() 
{
	
	gameBoardVector.clear(); //completely removes old game

	numberFlagged = 0;
	numMines = 0;
	gameIsPlayable = true;
	totalTiles = height * width;

	
	for (int i = 0; i < width; i++)
	{

		vector<Tile> temptT;
		for (int j = 0; j < height; j++)
		{
			//this long constructor sets all of the textures of the tiles to their appropriate texture
			Tile tempTile(imagesMap["tile_hidden"], imagesMap["tile_revealed"], imagesMap["flag"], imagesMap["mine"], imagesMap["number_1"], imagesMap["number_2"], imagesMap["number_3"], imagesMap["number_4"], imagesMap["number_5"], imagesMap["number_6"], imagesMap["number_7"], imagesMap["number_8"]);
			tempTile.xPos = i;
			tempTile.yPos = j;
			tempTile.hiddenTile.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.revealedTile.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.flagTile.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.mine.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number1.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number2.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number3.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number4.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number5.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number6.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number7.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number8.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile

			temptT.push_back(tempTile);
		}

		gameBoardVector.push_back(temptT);

	}

	SetMines();
	CalculateAdjacentTiles(); //should calculate the tiles surrounding
	CalculateAdjacentMines(); //should calculate the number of mines in the surrounding tiles
	totalTiles = totalTiles - numMines;

	currentGameMode = Mode::Play; //might not need to be here


}


void Board::CalculateAdjacentTiles()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (!gameBoardVector[i][j].isMine && (i != 0) && (j != 0) && (i != width - 1) && (j != height - 1))
			{
				SetMiddleAdjTiles(i, j);
				//gameBoardVector[i][j].numOfAdjMines = 8;
			}

			//UPPER LEFT CORNER
			if (i == 0 && j == 0) 
			{
				Tile* temp1;
				Tile* temp2;
				Tile* temp3;

				temp1 = &gameBoardVector[i +1][j];		 //E
				temp2 = &gameBoardVector[i + 1][j + 1];	 //SE
				temp3 = &gameBoardVector[i][j + 1];		 //S

				gameBoardVector[i][j].adjacentTiles.push_back(temp1);
				gameBoardVector[i][j].adjacentTiles.push_back(temp2);
				gameBoardVector[i][j].adjacentTiles.push_back(temp3);

				//gameBoardVector[i][j].numOfAdjMines = 3;
			}

			//UPPER RIGHT CORNER
			if (i == (width - 1) && j == 0) 
			{
				Tile* temp1;
				Tile* temp2;
				Tile* temp3;

				temp1 = &gameBoardVector[i - 1][j];		 //W
				temp2 = &gameBoardVector[i - 1][j + 1];	 //SW
				temp3 = &gameBoardVector[i][j + 1];		 //S

				gameBoardVector[i][j].adjacentTiles.push_back(temp1);
				gameBoardVector[i][j].adjacentTiles.push_back(temp2);
				gameBoardVector[i][j].adjacentTiles.push_back(temp3);

				//gameBoardVector[i][j].numOfAdjMines = 3;

			}

			//LOWER LEFT CORNER
			if (i == 0 && j == (height - 1)) 
			{
				Tile* temp1;
				Tile* temp2;
				Tile* temp3;

				temp1 = &gameBoardVector[i][j - 1];		 //N
				temp2 = &gameBoardVector[i + 1][j - 1];	 //NE
				temp3 = &gameBoardVector[i + 1][j];		 //E

				gameBoardVector[i][j].adjacentTiles.push_back(temp1);
				gameBoardVector[i][j].adjacentTiles.push_back(temp2);
				gameBoardVector[i][j].adjacentTiles.push_back(temp3);

				//gameBoardVector[i][j].numOfAdjMines = 3;

			}

			//LOWER RIGHT CORNER
			if (i == (width - 1) && j == (height - 1)) 
			{
				Tile* temp1;
				Tile* temp2;
				Tile* temp3;

				temp1 = &gameBoardVector[i - 1][j];		 //W
				temp2 = &gameBoardVector[i - 1][j - 1];	 //NW
				temp3 = &gameBoardVector[i][j - 1];		 //N

				gameBoardVector[i][j].adjacentTiles.push_back(temp1);
				gameBoardVector[i][j].adjacentTiles.push_back(temp2);
				gameBoardVector[i][j].adjacentTiles.push_back(temp3);

				//gameBoardVector[i][j].numOfAdjMines = 3;

			}

			//LEFT EDGE TILE
			if (i == 0 && j > 0 && j != (height - 1)) 
			{
				Tile* temp1;
				Tile* temp2;
				Tile* temp3;
				Tile* temp4;
				Tile* temp5;

				temp1 = &gameBoardVector[i][j - 1];		 //N
				temp2 = &gameBoardVector[i + 1][j - 1];  //NE
				temp3 = &gameBoardVector[i + 1][j];      //E
				temp4 = &gameBoardVector[i + 1][j + 1];  //SE
				temp5 = &gameBoardVector[i][j + 1];      //S

				gameBoardVector[i][j].adjacentTiles.push_back(temp1);
				gameBoardVector[i][j].adjacentTiles.push_back(temp2);
				gameBoardVector[i][j].adjacentTiles.push_back(temp3);
				gameBoardVector[i][j].adjacentTiles.push_back(temp4);
				gameBoardVector[i][j].adjacentTiles.push_back(temp5);

				//gameBoardVector[i][j].numOfAdjMines = 5;

			}

			//TOP EDGE TILE
			if (i > 0 && i != (width - 1) && j == 0)
			{
				Tile* temp1;
				Tile* temp2;
				Tile* temp3;
				Tile* temp4;
				Tile* temp5;

				temp1 = &gameBoardVector[i - 1][j];      //W
				temp2 = &gameBoardVector[i - 1][j + 1];  //SW
				temp3 = &gameBoardVector[i][j + 1];      //S
				temp4 = &gameBoardVector[i + 1][j + 1];  //SE
				temp5 = &gameBoardVector[i + 1][j];      //E

				gameBoardVector[i][j].adjacentTiles.push_back(temp1);
				gameBoardVector[i][j].adjacentTiles.push_back(temp2);
				gameBoardVector[i][j].adjacentTiles.push_back(temp3);
				gameBoardVector[i][j].adjacentTiles.push_back(temp4);
				gameBoardVector[i][j].adjacentTiles.push_back(temp5);

				//gameBoardVector[i][j].numOfAdjMines = 5;

			}

			//RIGHT EDGE TILE
			if (i == (width - 1) && j > 0 && j != (height - 1))
			{
				Tile* temp1;
				Tile* temp2;
				Tile* temp3;
				Tile* temp4;
				Tile* temp5;

				temp1 = &gameBoardVector[i][j - 1];		 //N
				temp2 = &gameBoardVector[i - 1][j - 1];  //NW
				temp3 = &gameBoardVector[i - 1][j];      //W
				temp4 = &gameBoardVector[i - 1][j + 1];  //SW
				temp5 = &gameBoardVector[i][j + 1];      //S

				gameBoardVector[i][j].adjacentTiles.push_back(temp1);
				gameBoardVector[i][j].adjacentTiles.push_back(temp2);
				gameBoardVector[i][j].adjacentTiles.push_back(temp3);
				gameBoardVector[i][j].adjacentTiles.push_back(temp4);
				gameBoardVector[i][j].adjacentTiles.push_back(temp5);

				//gameBoardVector[i][j].numOfAdjMines = 5;

			}

			//BOTTOM EDGE TILE
			if (i > 0 && i != (width - 1) && j == (height - 1))
			{
				Tile* temp1;
				Tile* temp2;
				Tile* temp3;
				Tile* temp4;
				Tile* temp5;

				temp1 = &gameBoardVector[i - 1][j];      //W
				temp2 = &gameBoardVector[i - 1][j - 1];  //NW
				temp3 = &gameBoardVector[i][j - 1];		 //N
				temp4 = &gameBoardVector[i + 1][j - 1];  //NE
				temp5 = &gameBoardVector[i + 1][j];      //E

				gameBoardVector[i][j].adjacentTiles.push_back(temp1);
				gameBoardVector[i][j].adjacentTiles.push_back(temp2);
				gameBoardVector[i][j].adjacentTiles.push_back(temp3);
				gameBoardVector[i][j].adjacentTiles.push_back(temp4);
				gameBoardVector[i][j].adjacentTiles.push_back(temp5);

				//gameBoardVector[i][j].numOfAdjMines = 5;

			}

		}//end inner for loop
	}//end outer for loop
}//end function
//STILL NEED THE STUFF FOR SET ADJACENT NUMBER OF MINES
//CURRENTLY HAVE AN ISSUE WHERE ALL ADJACENT TILES WERE SAID TO BE MINES WHEN THEY WERE NOT
void Board::SetMiddleAdjTiles(int i, int j) //this sets the adjacent tile if its in the middle 
{
	Tile* temp1;
	Tile* temp2;
	Tile* temp3;
	Tile* temp4;
	Tile* temp5;
	Tile* temp6;
	Tile* temp7;
	Tile* temp8;

	temp1 = &gameBoardVector[i - 1][j - 1];  //NW
	temp2 = &gameBoardVector[i][j - 1];		 //N
	temp3 = &gameBoardVector[i + 1][j - 1];  //NE
	temp4 = &gameBoardVector[i - 1][j];      //W
	temp5 = &gameBoardVector[i + 1][j];      //E
	temp6 = &gameBoardVector[i - 1][j + 1];  //SW
	temp7 = &gameBoardVector[i][j + 1];      //S
	temp8 = &gameBoardVector[i + 1][j + 1];  //SE

	//need to push back into vector
	gameBoardVector[i][j].adjacentTiles.push_back(temp1);
	gameBoardVector[i][j].adjacentTiles.push_back(temp2);
	gameBoardVector[i][j].adjacentTiles.push_back(temp3);
	gameBoardVector[i][j].adjacentTiles.push_back(temp4);
	gameBoardVector[i][j].adjacentTiles.push_back(temp5);
	gameBoardVector[i][j].adjacentTiles.push_back(temp6);
	gameBoardVector[i][j].adjacentTiles.push_back(temp7);
	gameBoardVector[i][j].adjacentTiles.push_back(temp8);


}

void Board::LoadTest1() 
{
	//do the stuff for Test1

	numberFlagged = 0;
	numMines = 0;
	gameIsPlayable = true;
	totalTiles = height * width;
	gameBoardVector.clear();

	for (int i = 0; i < width; i++)
	{
		vector<Tile> temptT;
		for (int j = 0; j < height; j++)
		{
			//this long constructor sets all of the textures of the tiles to their appropriate texture
			Tile tempTile(imagesMap["tile_hidden"], imagesMap["tile_revealed"], imagesMap["flag"], imagesMap["mine"], imagesMap["number_1"], imagesMap["number_2"], imagesMap["number_3"], imagesMap["number_4"], imagesMap["number_5"], imagesMap["number_6"], imagesMap["number_7"], imagesMap["number_8"]);
			tempTile.xPos = i;
			tempTile.yPos = j;
			tempTile.hiddenTile.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.revealedTile.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.flagTile.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.mine.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number1.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number2.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number3.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number4.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number5.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number6.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number7.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number8.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile

			temptT.push_back(tempTile);
		}

		gameBoardVector.push_back(temptT);

	}


	ifstream iFile("boards\\testboard.brd");
	string lineFromFile;

	if (iFile.is_open())
	{
		int j = 0;
		while (getline(iFile, lineFromFile))
		{
			for (int i = 0; i < lineFromFile.length(); i++)
			{
				if (lineFromFile[i] == '1')
				{
					gameBoardVector[i][j].TileIsMine();
					numMines++;
				}
				else
				{
					gameBoardVector[i][j].isMine = false;
				}
			}
			j++;
		}
	}

	iFile.close();

	CalculateAdjacentTiles(); //should calculate the tiles surrounding
	CalculateAdjacentMines(); //should calculate the number of mines in the surrounding tiles
	totalTiles = totalTiles - numMines;

	currentGameMode = Mode::Play;

	//set adj tiles and bombs
}
void Board::LoadTest2()
{
	//do the stuff for Test2
	numberFlagged = 0;
	numMines = 0;
	gameIsPlayable = true;
	totalTiles = height * width;
	gameBoardVector.clear();

	for (int i = 0; i < width; i++)
	{
		vector<Tile> temptT;
		for (int j = 0; j < height; j++)
		{
			//this long constructor sets all of the textures of the tiles to their appropriate texture
			Tile tempTile(imagesMap["tile_hidden"], imagesMap["tile_revealed"], imagesMap["flag"], imagesMap["mine"], imagesMap["number_1"], imagesMap["number_2"], imagesMap["number_3"], imagesMap["number_4"], imagesMap["number_5"], imagesMap["number_6"], imagesMap["number_7"], imagesMap["number_8"]);
			tempTile.xPos = i;
			tempTile.yPos = j;
			tempTile.hiddenTile.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.revealedTile.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.flagTile.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.mine.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number1.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number2.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number3.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number4.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number5.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number6.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number7.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile
			tempTile.number8.setPosition(tempTile.xPos * 32.f, tempTile.yPos * 32.f); //sets the location of that tile

			temptT.push_back(tempTile);
		}

		gameBoardVector.push_back(temptT);

	}


	ifstream iFile("boards\\testboard2.brd");
	string lineFromFile;

	if (iFile.is_open())
	{
		int j = 0;
		while (getline(iFile, lineFromFile))
		{
			for (int i = 0; i < lineFromFile.length(); i++)
			{
				if (lineFromFile[i] == '1')
				{
					gameBoardVector[i][j].TileIsMine();
					numMines++;
				}
				else
				{
					gameBoardVector[i][j].isMine == false;
				}
			}
			j++;
		}
	}

	iFile.close();

	CalculateAdjacentTiles(); //should calculate the tiles surrounding
	CalculateAdjacentMines(); //should calculate the number of mines in the surrounding tiles
	totalTiles = totalTiles - numMines;


	currentGameMode = Mode::Play;

	//set adj tiles and bombs
}

void Board::CalculateAdjacentMines() 
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int mineCount = 0;
			for (int k = 0; k < gameBoardVector[i][j].adjacentTiles.size(); k++)
			{
				if (gameBoardVector[i][j].adjacentTiles.at(k)->isMine)
				{
					mineCount++;
				}
			}
			
			gameBoardVector[i][j].numOfAdjMines = mineCount;

		}
	}
}

void Board::UpdateMineCount() 
{
	int numberOfFlagsOnBoard = 0;
	int newNumMines = numMines;
	int iPlace1 = 0, iPlace2 = 0, iPlace3 = 0;
	string sPlace1, sPlace2, sPlace3;
	

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (gameBoardVector[i][j].isFlag) 
			{
				numberOfFlagsOnBoard++;
			}

		}
	}

	
	newNumMines = newNumMines - numberOfFlagsOnBoard;

	
	if (newNumMines < 0)
	{
		iPlace3 = 0;
		iPlace2 = 0;
		iPlace1 = 0;
	}
	else 
	{
		iPlace3 = newNumMines % 10;
		newNumMines /= 10;
		iPlace2 = newNumMines % 10;
		newNumMines /= 10;
		iPlace1 = newNumMines % 10;
	}
	

	sPlace1 = "digits" + to_string(iPlace1);
	sPlace2 = "digits" + to_string(iPlace2);
	sPlace3 = "digits" + to_string(iPlace3);

	place1.setTexture(imagesMap[sPlace1]);
	place2.setTexture(imagesMap[sPlace2]);
	place3.setTexture(imagesMap[sPlace3]);

}

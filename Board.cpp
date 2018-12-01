#include "Board.h"
#include "Tile.h"

mt19937 random_mt(time(0)); //potential loss of data?
int Random(int min, int max)
{
    uniform_int_distribution<int> dist(min, max);
    return dist(random_mt);
}

Board::Board() //populates the 2d vector used to make minesweeper board
{
	numMines = 50;
	numberFlagged = 0;
	totalTiles = totalTiles - numMines;
	LoadTextures();

	place1.setTexture(imagesMap["digits0"]);
	place1.setPosition(0.f, 16.f * tileWidth);

	place2.setTexture(imagesMap["digits5"]);
	place2.setPosition(21.f, 16.f * tileWidth);

	place3.setTexture(imagesMap["digits0"]);
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
			Tile tempTile;
			tempTile.xPos = (float)i;
			tempTile.yPos = (float)j;
			tempTile.hiddenTile.setPosition(i * 32.f, j * 32.f);
			temptT.push_back(tempTile);
		}

		gameBoardVector.push_back(temptT);

	}

}


Board::~Board()
{

}

void Board::MakeBoard(sf::RenderWindow& mainWindow)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			gameBoardVector[i][j].hiddenTile.setTexture(imagesMap["tile_hidden"]);
			mainWindow.draw(gameBoardVector[i][j].hiddenTile); //draws a hidden tile at that location
		}
	}

	//starts at 400 for x
	//starts at 500 for y
	mainWindow.draw(debugButton);
	mainWindow.draw(test1);
	mainWindow.draw(test2);
	mainWindow.draw(place1);
	mainWindow.draw(place2);
	mainWindow.draw(place3);

	mainWindow.draw(happyButton);

	//need to add the set mines function somewhere


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
 
void Board::SetMines() 
{
	for (int i = 0; i < 50; i++) //loops for total number of mines
	{
		int x = Random(0, 15);
		int y = Random(0, 24);
		
		if (gameBoardVector[x][y].isMine) //prevents 2 mines from being placed on top of each other
		{
			i--;
		}
		else 
		{
			gameBoardVector[x][y].TileIsMine();
		}
	}
	


}





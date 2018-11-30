#include "Board.h"
#include "Tile.h"

Board::Board() //populates the 2d vector used to make minesweeper board
{
	numMines = 50;
	numberFlagged = 0;
	totalTiles = totalTiles - numMines;
	LoadTextures();

	//place1.setTexture
	place1.setPosition(0, 16 * tileWidth);

	//place2.setTexture
	place2.setPosition(21, 16 * tileWidth);

	//place3.setTexture
	place3.setPosition(42, 16 * tileWidth);

	debugButton.setTexture(imagesMap["debug"]);
	debugButton.setPosition(16.5 * tileWidth, 16 * tileWidth);

	happyButton.setTexture(imagesMap["face_happy"]);
	happyButton.setPosition(11.5 * tileWidth, 16 * tileWidth);

	winButton.setTexture(imagesMap["face_lose"]);
	winButton.setPosition(11.5 * tileWidth, 16 * tileWidth);

	test1.setTexture(imagesMap["test_1"]);
	test1.setPosition(18.5 * tileWidth, 16 * tileWidth);

	test2.setTexture(imagesMap["test_2"]);
	test2.setPosition(20.5 * tileWidth, 16 * tileWidth);



	for (int i = 0; i < width; i++)
	{
		vector<Tile> temptT;
		for (int j = 0; j < height; j++)
		{
			Tile tempTile;
			tempTile.xPos = i;
			tempTile.yPos = j;
			tempTile.regularSprite.setPosition(i * 32.f, j * 32.f);
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
			gameBoardVector[i][j].regularSprite.setTexture(imagesMap["tile_hidden"]);
			mainWindow.draw(gameBoardVector[i][j].regularSprite); //draws a hidden tile at that location
		}
	}

	//Print the bottoom buttons now


}

void Board::LoadTextures()
{
	//this loads all the textures into a vector in preperation for them to be loaded 
	vector<sf::Texture> textureVec(19);
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
	textureVec[15].loadFromFile("images\\digits.png");
	textureVec[16].loadFromFile("images\\face_happy.png");
	textureVec[17].loadFromFile("images\\face_lose.png");
	textureVec[18].loadFromFile("images\\face_win.png");

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
	imagesMap.emplace("digits", textureVec[15]);
	imagesMap.emplace("face_happy", textureVec[16]);
	imagesMap.emplace("face_lose", textureVec[17]);
	imagesMap.emplace("face_win", textureVec[18]);
}







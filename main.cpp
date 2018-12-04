#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
using namespace std;

//FUNCTION PROTOTYPES
bool ResetButtonClicked(sf::Event, Board);
bool DebugButtonClicked(sf::Event, Board);
bool Test1Clicked(sf::Event, Board);
bool Test2Clicked(sf::Event, Board);
Tile SelectedTile(sf::Event, Board);


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper"); //this sets the window to the appropriate size
	Board boardObj;
	Tile tileObj;

	// runs the program as long as the window is open
	while (window.isOpen())
	{

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) //checks if the mouse button was pressed
			{
				if (event.mouseButton.button == sf::Mouse::Left) //only if its the left mouse click
				{

					cout << "Left Mouse Clicked" << endl;

					cout << event.mouseButton.x << endl;
					cout << event.mouseButton.y << endl;

					
					if (ResetButtonClicked(event, boardObj) && boardObj.currentGameMode != Board::Mode::Debug) //checks if its within the reset face button area and not in debug mode
					{
						cout << "Reset button clicked in regular mode" << endl;
						boardObj.ResetBoard();
					}

					else if (ResetButtonClicked(event, boardObj) && boardObj.currentGameMode == Board::Mode::Debug) //checks if its within the reset face button area and in debug mode
					{
						cout << "Reset button clicked in debug mode" << endl;
						boardObj.ResetBoard();
						boardObj.currentGameMode = Board::Mode::Debug; //keeps the game in debug mode
					}

					else if (DebugButtonClicked(event, boardObj) && boardObj.currentGameMode != Board::Mode::Debug) //checks if its within the debug button area and not already in debug mode
					{
						cout << "Debug mode turned on" << endl;
						boardObj.currentGameMode = Board::Mode::Debug;
					}

					else if (DebugButtonClicked(event, boardObj) && boardObj.currentGameMode == Board::Mode::Debug) 
					{
						cout << "Debug mode turned off" << endl;
						boardObj.currentGameMode = Board::Mode::Play;
					}

					else if (Test1Clicked(event, boardObj) && boardObj.currentGameMode != Board::Mode::Debug)
					{
						cout << "Test 1 mode turned on in regular mode" << endl;
					}

					else if (Test1Clicked(event, boardObj) && boardObj.currentGameMode == Board::Mode::Debug)
					{
						cout << "Test 1 mode turned on in debug mode" << endl;
					}

					else if (Test2Clicked(event, boardObj) && boardObj.currentGameMode != Board::Mode::Debug)
					{
						cout << "Test 2 mode turned on in regular mode" << endl;
					}

					else if (Test2Clicked(event, boardObj) && boardObj.currentGameMode == Board::Mode::Debug)
					{
						cout << "Test 2 mode turned on in debug mode" << endl;
					}

					else if (!SelectedTile(event, boardObj).hasBeenLeftClicked && !SelectedTile(event, boardObj).isFlag) //implies the tile hasnt been left clicked yet
					{
						boardObj.gameBoardVector[event.mouseButton.x / 32][event.mouseButton.y / 32].hasBeenLeftClicked = true;
					}
					else //assumes the tile has already been clicked
					{
						
					}

				}

				if (event.mouseButton.button == sf::Mouse::Right) //only if its the right mouse 
				{

					cout << "Right Mouse Clicked" << endl;
					//need to add a fix for clicking outside of the board with a right click
					//need to be able to right click a mine and have a flag appear


					if (SelectedTile(event, boardObj).isFlag) //this checks if the tile is already a flag and removes the sprite
					{
						boardObj.gameBoardVector[event.mouseButton.x / 32][event.mouseButton.y / 32].isFlag = false;
					}
					else if (!boardObj.gameBoardVector[event.mouseButton.x / 32][event.mouseButton.y / 32].hasBeenLeftClicked) //assumes the tile is not a flag and hasnt already been left clicked
					{
						boardObj.gameBoardVector[event.mouseButton.x / 32][event.mouseButton.y / 32].isFlag = true;
					} 

				}
			}


		}

		window.clear();

		boardObj.MakeBoard(window);

		window.display();



	}

	return 0;
}

bool ResetButtonClicked(sf::Event e, Board bObj) 
{
	if ((e.mouseButton.x >= (11.5f * bObj.tileWidth) && (e.mouseButton.x <= (11.5f * bObj.tileWidth) + 64)) && (e.mouseButton.y >= 16.f * bObj.tileWidth && (e.mouseButton.y <= (16.f * bObj.tileWidth) + 64)) == true)
	{
		return true;
	}
	else
		return false;
}

bool DebugButtonClicked(sf::Event e, Board bObj)
{
	
	if ((e.mouseButton.x >= (16.5f * bObj.tileWidth) && (e.mouseButton.x <= (16.5f * bObj.tileWidth) + 64)) && (e.mouseButton.y >= 16.f * bObj.tileWidth && (e.mouseButton.y <= (16.f * bObj.tileWidth) + 64)) == true)
	{
		return true;
	}
	else
		return false;

}

bool Test1Clicked(sf::Event e, Board bObj) 
{
	if ((e.mouseButton.x >= (18.5f * bObj.tileWidth) && (e.mouseButton.x <= (18.5f * bObj.tileWidth) + 64)) && (e.mouseButton.y >= 16.f * bObj.tileWidth && (e.mouseButton.y <= (16.f * bObj.tileWidth) + 64)) == true)
	{
		return true;
	}
	else
		return false;

}

bool Test2Clicked(sf::Event e, Board bObj)
{
	if ((e.mouseButton.x >= (20.5f * bObj.tileWidth) && (e.mouseButton.x <= (20.5f * bObj.tileWidth) + 64)) && (e.mouseButton.y >= 16.f * bObj.tileWidth && (e.mouseButton.y <= (16.f * bObj.tileWidth) + 64)) == true)
	{
		return true;
	}
	else
		return false;

}


Tile SelectedTile(sf::Event e, Board bObj) 
{
	return bObj.gameBoardVector[e.mouseButton.x / 32][e.mouseButton.y / 32];
}
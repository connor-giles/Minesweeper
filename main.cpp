#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
using namespace std;

//FUNCTION PROTOTYPES



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


					if ((event.mouseButton.x >= (16.5f * boardObj.tileWidth) && (event.mouseButton.x <= (16.5f * boardObj.tileWidth) + 64)) && (event.mouseButton.y >= 16.f * boardObj.tileWidth && (event.mouseButton.y <= (16.f * boardObj.tileWidth) + 64)) && boardObj.currentGameMode != Board::Mode::Debug) //checks if its within the debug button area and not already in debug mode
					{
						cout << "Debug button clicked" << endl;
						boardObj.currentGameMode = Board::Mode::Debug;
					}

					else if ((event.mouseButton.x >= (16.5f * boardObj.tileWidth) && (event.mouseButton.x <= (16.5f * boardObj.tileWidth) + 64)) && (event.mouseButton.y >= 16.f * boardObj.tileWidth && (event.mouseButton.y <= (16.f * boardObj.tileWidth) + 64)) && boardObj.currentGameMode == Board::Mode::Debug) 
					{
						//need to turn debug mode off
						boardObj.currentGameMode = Board::Mode::Play;
					}

					else if (!boardObj.gameBoardVector[event.mouseButton.x / 32][event.mouseButton.y / 32].hasBeenLeftClicked && !boardObj.gameBoardVector[event.mouseButton.x / 32][event.mouseButton.y / 32].isFlag) //implies the tile hasnt been left clicked yet
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


					if (boardObj.gameBoardVector[event.mouseButton.x / 32][event.mouseButton.y / 32].isFlag) //this checks if the tile is already a flag and removes the sprite
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

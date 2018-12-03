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


					if (!boardObj.gameBoardVector[event.mouseButton.x / 32][event.mouseButton.y / 32].hasBeenLeftClicked) //implies the tile hasnt been left clicked yet
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

					if (boardObj.gameBoardVector[event.mouseButton.x / 32][event.mouseButton.y / 32].isFlag) //this checks if the tile is already a flag and removes the sprite
					{
						boardObj.gameBoardVector[event.mouseButton.x / 32][event.mouseButton.y / 32].isFlag = false;
					}
					else //assumes the tile is not a flag
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

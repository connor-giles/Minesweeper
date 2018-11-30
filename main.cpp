#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
using namespace std;

//FUNCTION PROTOTYPES
void MakeBoard();




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
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
				}
			}


		}

		window.clear();

		boardObj.MakeBoard(window);

		window.display();



	}

	return 0;
}

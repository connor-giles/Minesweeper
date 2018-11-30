#include "Tile.h"


//Every tile needs a multiple sprites (either revelaed or hidden) etc.
//flags and numbers mine can take up same spot
//2 sprites (mine flags and numbers are one) (hidden or reveled is another)

//sprites are part of tile class


Tile::Tile() 
{
	isMine = false;
	tilestate = TileState::Hidden;
	//adjMine;
}


Tile::~Tile()
{

}


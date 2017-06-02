#include "ComputerBoard.h"
#include <assert.h>
#include <random>

ComputerBoard::ComputerBoard(const Vei2 & pos, Graphics & gfx)
	:
	Board(pos, gfx)
{
	for (int y = 0; y < GetHeight(); y++)
	{
		for (int x = 0; x < GetWidth(); x++)
		{
			tiles[x][y].Hide();
		}
	}
}

void ComputerBoard::PlaceShips()
{	
	PlaceShip(4);

	PlaceShip(3);
	PlaceShip(3);

	PlaceShip(2);
	PlaceShip(2);
	PlaceShip(2);

	PlaceShip(1);
	PlaceShip(1);
	PlaceShip(1);
	PlaceShip(1);
}

void ComputerBoard::PlaceShip(short nShipTiles)
{
	assert(nShipTiles <= 4 && nShipTiles >= 1); // TODO: Remove this assert.

	bool shipPlaced = false;

	unsigned short direction;

	unsigned short x;
	unsigned short y;

	std::random_device rd;
	std::mt19937 rng( rd() );
	std::uniform_int_distribution<unsigned short> dirDist(1, 2); //1: horizontal, 2: vertical.
	
	std::uniform_int_distribution<unsigned short> xDist1(0, GetWidth() - nShipTiles);
	std::uniform_int_distribution<unsigned short> yDist1(0, GetHeight() - 1);

	std::uniform_int_distribution<unsigned short> xDist2(0, GetWidth() - 1);
	std::uniform_int_distribution<unsigned short> yDist2(0, GetHeight() - nShipTiles);
	
	do
	{
		unsigned short startX;
		unsigned short startY;

		unsigned short endX;
		unsigned short endY;

		direction = dirDist( rng );

		switch(direction)
		{
		case 1:
			x = xDist1(rng);
			y = yDist1(rng);

			if (x == GetWidth() - nShipTiles)
			{
				endX = GetWidth() - 1;
			}
			else
			{
				endX = x + nShipTiles;
			}

			if (y == GetHeight() - 1)
			{
				endY = y;
			}
			else
			{
				endY = y + 1;
			}

			break;

		case 2:
			x = xDist2(rng);
			y = yDist2(rng);

			if (x == GetWidth() - 1)
			{
				endX = x;
			}
			else
			{
				endX = x + 1;
			}

			if (y == GetHeight() - nShipTiles)
			{
				endY = GetHeight() - 1;
			}
			else
			{
				endY = y + nShipTiles;
			}

			break;
		}

		if (x == 0)
		{
			startX = x;
		}
		else
		{
			startX = x - 1;
		}

		if (y == 0)
		{
			startY = y;
		}
		else
		{
			startY = y - 1;
		}

		bool isAreaAvailable = true;

		for(unsigned short j = startY; j <= endY; j++)
		{
			for(unsigned short i = startX; i <= endX; i++)
			{
				if (tiles[i][j].IsShipTile())
				{
					isAreaAvailable = false;
					break;
				}
			}
			if (!isAreaAvailable)
			{
				break;
			}
		}

		if (!isAreaAvailable)
		{
			continue;
		}
		else if (direction == 1)
		{
			for (unsigned short i = x; i < x + nShipTiles; i++)
			{
				tiles[i][y].SetShip();
			}
		}
		else
		{
			for (unsigned short i = y; i < y + nShipTiles; i++)
			{
				tiles[x][i].SetShip();
			}
		}
		shipPlaced = true;
	} 
	while (!shipPlaced);
}

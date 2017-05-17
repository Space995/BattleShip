#pragma once
#include "Board.h"

class ComputerBoard : public Board
{
public:
	ComputerBoard() = delete;
	ComputerBoard(const Vei2& pos, Graphics& gfx);

	void PlaceShips();
private:
	void PlaceShip(short nShipTiles);
};

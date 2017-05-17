#include "Board.h"
#include <assert.h>

Board::Tile::Tile(const Vei2 & pos)
	:
	pos(pos),
	tileArea(pos, Dimension, Dimension)
{
}

void Board::Tile::Draw(Graphics & gfx) const
{
	gfx.DrawRect(tileArea, color);
	gfx.DrawRectBorder(tileArea, BorderColor);
}

bool Board::Tile::Contains(const Vei2 in_pos) const
{
	if (in_pos.x > pos.x && in_pos.y > pos.y)
	{
		Vei2 tileDwnRightCorner = { pos.x + Tile::Dimension - 1 , pos.y + Tile::Dimension - 1 };

		if (in_pos.x < tileDwnRightCorner.x && in_pos.y < tileDwnRightCorner.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Board::Tile::IsHidden() const
{
	return state == State::Hidden;
}

bool Board::Tile::IsRevealed() const
{
	return state == State::Revealed;
}

bool Board::Tile::IsWater() const
{
	return isWater;
}

bool Board::Tile::IsShipTile() const
{
	return !isWater;
}



void Board::Tile::Hide()
{
	assert(state == State::Revealed); // TODO: Remove this assert.
	state = State::Hidden;
	color = Colors::Gray;
}

void Board::Tile::Reveal()
{
	assert(state == State::Hidden); // TODO: Remove this assert.
	state = State::Revealed;

	if (isWater)
	{
		color = Colors::Blue;
	}
	else
	{
		color = Colors::Red;
	}
}

void Board::Tile::SetShip()
{
	assert(state == State::Revealed && isWater); // TODO: Remove this assert.
	isWater = false;
	color = Colors::Gray;
}

Board::Board(const Vei2 & in_pos, Graphics & gfx)
	:
	gfx(gfx),
	pos(in_pos)		// TODO: Remove this assertions
{
	assert( (pos.x >= 0) && (pos.x <= (Graphics::ScreenWidth - (Width * Tile::Dimension))));
	assert( (pos.y >= 0) && (pos.y <= (Graphics::ScreenHeight - (Height * Tile::Dimension))));

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			Vei2 tilePos = { ( pos.x + (x * Tile::Dimension) ) , ( (pos.y + (y * Tile::Dimension) ) ) };
			tiles[x][y] = Tile{tilePos};
		}
	}
}

void Board::Draw()
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			tiles[x][y].Draw(gfx);
		}
	}
}

void Board::Reveal()
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			tiles[x][y].Reveal();
		}
	}
}

bool Board::Contains(const Vei2 & in_pos) const
{
	if (in_pos.x > pos.x && in_pos.y > pos.y)
	{
		Vei2 brdDwnRightCorner = { pos.x + (Width * Tile::Dimension) , pos.y + (Height * Tile::Dimension) };

		if (in_pos.x < brdDwnRightCorner.x && in_pos.y < brdDwnRightCorner.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Board::isOnTilesBorder(const Vei2 & in_pos) const
{
	if ((in_pos.x - pos.x) % Tile::Dimension == 0.0)
	{
		return true;
	}
	else if ((in_pos.y - pos.y) % Tile::Dimension == 0.0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Board::Tile& Board::getTile(const Vei2 & in_pos)
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			if (tiles[x][y].Contains(in_pos))
			{
				return tiles[x][y];
			}
		}
	}
}

int Board::GetWidth() const
{
	return Width;
}

int Board::GetHeight() const
{
	return Height;
}



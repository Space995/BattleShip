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

void Board::Tile::Reveal()
{
	assert(state == State::Hidden); // TODO: Remove this assert.
	state = State::Revealed;
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

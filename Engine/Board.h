#pragma once
#include "Colors.h"
#include "Graphics.h"

class Board
{
	class Tile
	{
	public:
		Tile() = default;
		Tile(const Vei2& pos);

		void Draw(Graphics& gfx) const;
		bool Contains(const Vei2 in_pos) const; //This function doesn't evaluate the border of the tile!
		bool isHidden() const;
		bool isRevealed() const;
		void Hide();
		void Reveal();
		void SetShip(); //If you call this function, you're tile will be a ship tile.
	private:
		enum class State
		{
			Hidden,
			Revealed
		};

	public:
		static constexpr int Dimension = 40;
	private:
		Vei2 pos; //This is the up-left corner of the tileArea.
		RectI tileArea;
		State state = State::Revealed; //Player will place his ship tiles, so the board have to start revealed.
		bool isWater = true; //Player will place his ship tiles, so initially, the tiles have to be water.
		Color color = Colors::Blue; 
		static constexpr Color BorderColor = Colors::White;
	};


public:
	Board() = delete;
	Board(const Vei2& pos, Graphics& gfx);

	void Draw();
	bool Contains(const Vei2& in_pos) const; //This function doesn't evaluate the border of the board!
	bool isOnTilesBorder(const Vei2& in_pos) const; //Contains(in_pos) MUST be true to use this function!
	Tile& getTile(const Vei2& in_pos); //isOnTilesBorder(in_pos) MUST be FALSE to use this function!

private:
	static constexpr int Width = 10;
	static constexpr int Height = 10;

	Graphics& gfx;
	Vei2 pos; //This is the up-left corner of the board.
	Tile tiles[Width][Height];
};

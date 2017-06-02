#pragma once
#include "Colors.h"
#include "Graphics.h"
#include "Text.h"

class Board
{
protected:
	class Tile
	{
	public:
		Tile() = default;
		Tile(const Vei2& pos);

		void Draw(Graphics& gfx) const;
		bool Contains(const Vei2 in_pos) const; //This function doesn't evaluate the border of the tile!
		bool IsHidden() const;
		bool IsRevealed() const;
		bool IsWater() const;
		bool IsShipTile() const;
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
	void Reveal();
	bool Contains(const Vei2& in_pos) const; //This function doesn't evaluate the border of the board!
	bool IsOnTilesBorder(const Vei2& in_pos) const; //Contains(in_pos) MUST be true to use this function!
	Tile& GetTile(const Vei2& in_pos); //IsOnTilesBorder(in_pos) MUST be FALSE to use this function!

private:
	static constexpr int Width = 10;
	static constexpr int Height = 10;

	static constexpr Color lettersColor = Colors::Yellow;
	static constexpr Color numbersColor = Colors::Green;

	Graphics& gfx;
	Vei2 pos; //This is the up-left corner of the board.
	Text letters;
	Text numbers;
	Text number10;
protected:
	Tile tiles[Width][Height];

protected:
	int GetWidth() const;
	int GetHeight() const;
};

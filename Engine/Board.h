#pragma once
#include "Colors.h"
#include "Graphics.h"

class Board
{
public:
	Board() = delete;
	Board(const Vei2& pos, Graphics& gfx);

	void Draw();

private:
	class Tile
	{
	public:
		Tile() = default;
		Tile(const Vei2& pos);

		void Draw(Graphics& gfx) const;
		void Reveal();
	private:
		enum class State
		{
			Hidden,
			Revealed
		};



	public:
		static constexpr int Dimension = 40;
	private:
		Vei2 pos; //Board relative position, This is the up-left corner of the tileArea.
		RectI tileArea;
		State state = State::Hidden;
		bool isWater = true;
		Color color = Colors::Gray;
		static constexpr Color BorderColor = Colors::White;
	};

	static constexpr int Width = 10;
	static constexpr int Height = 10;

	Graphics& gfx;
	Vei2 pos; //Absolute position. This is the up-left corner of the board.
	Tile tiles[Width][Height];
};

/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "ComputerBoard.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Types and Functions    */
	enum class Stage
	{
		WAITING,
		STARTING,
		PLAYING,
		ENDING,
		OVER
	};

	class Turn
	{
	public:
		enum class PlayingEntity
		{
			Player,
			Computer
		};

		Turn();

		void Next();
		void MoveCompleted();
		const PlayingEntity& GetPlayingEntity() const;
		bool IsMoveDone() const;
	private:
		
	private:
		PlayingEntity entity;
		bool isMoveDone = false;
	};
	/*enum class Turn
	{
		Player,
		Computer
	};*/

	enum class Winner
	{
		Player,
		Computer
	};


	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Board playerBoard;
	ComputerBoard computerBoard;

	Text testText;

	Stage stage = Stage::WAITING;
	Turn turn;
	Winner winner;
	/********************************/
};
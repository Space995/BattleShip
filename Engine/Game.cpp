/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include <random>
#include <assert.h>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	playerBoard(Vei2{ 100,100 }, gfx),
	computerBoard(Vei2{ Graphics::ScreenWidth - 500, 100 }, gfx),
	testText(gfx)
{
	computerBoard.PlaceShips();

	testText.SetPostion(220, Graphics::ScreenHeight - 120);
	testText.SetColor(Colors::White);

	if (turn.GetPlayingEntity() == Turn::PlayingEntity::Player)
	{
		testText.SetText("Inizia a giocare il Giocatore!");
	}
	else
	{
		testText.SetText("Inizia a giocare il Computer!");
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		turn.MoveCompleted();
		turn.Next();

		if (turn.GetPlayingEntity() == Turn::PlayingEntity::Player)
		{
			testText.SetText("Turno del Giocatore!");
		}
		else
		{
			testText.SetText("Turno del Computer!");
		}
	}

	if (turn.GetPlayingEntity() == Turn::PlayingEntity::Player && wnd.mouse.IsInWindow() && wnd.mouse.LeftIsPressed())
	{
		Vei2 mousePos {wnd.mouse.GetPosX(), wnd.mouse.GetPosY()};
		if (computerBoard.Contains(mousePos) && !computerBoard.IsOnTilesBorder(mousePos))
		{
			if (computerBoard.GetTile(mousePos).IsHidden())
			{
				computerBoard.GetTile(mousePos).Reveal();
				if (computerBoard.GetTile(mousePos).IsWater())
				{
					turn.MoveCompleted();
					turn.Next();
					testText.SetText("Turno del Computer!");
				}
			}
		}
	}
}

void Game::ComposeFrame()
{
	playerBoard.Draw();
	computerBoard.Draw();

	testText.Draw();
}

Game::Turn::Turn()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> startEntDistr(0, 1);

	entity = (PlayingEntity) startEntDistr(rng);
}

void Game::Turn::Next()
{
	assert(isMoveDone); // TODO: Remove this assertion!

	if (entity == PlayingEntity::Computer)
	{
		entity = PlayingEntity::Player;
	}
	else
	{
		entity = PlayingEntity::Computer;
	}

	isMoveDone = false;
}

void Game::Turn::MoveCompleted()
{
	assert(!isMoveDone); // TODO: Remove this assertion!
	isMoveDone = true;
}

const Game::Turn::PlayingEntity& Game::Turn::GetPlayingEntity() const
{
	return entity;
}

bool Game::Turn::IsMoveDone() const
{
	return isMoveDone;
}

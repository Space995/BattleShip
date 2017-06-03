#include "Turn.h"
#include <random>
#include <assert.h>

Turn::Turn()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> startEntDistr(0, 1);

	entity = (PlayingEntity)startEntDistr(rng);
}

void Turn::Next()
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

void Turn::MoveCompleted()
{
	assert(!isMoveDone); // TODO: Remove this assertion!
	isMoveDone = true;
}

const Turn::PlayingEntity& Turn::GetPlayingEntity() const
{
	return entity;
}

bool Turn::IsMoveDone() const
{
	return isMoveDone;
}

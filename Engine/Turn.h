#pragma once

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
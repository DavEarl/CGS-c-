#pragma once
#include "PlaceableActor.h"
class Enemy : public PlaceableActor
{
public:
	Enemy(int x, int y, int deltaX = 0, int deltaY = 0);

	virtual ActorType GetType() override { return ActorType::Enemy; }
	virtual void Draw() override;
	virtual void Update() override;

private:
	int m_movmentInX;
	int m_movmentInY;

	int m_currentlyMovementX;
	int m_currentlyMovementY;

	int m_directionX;
	int m_directionY;

	void UpdateDirection(int& current, int& direction, int& movement);
};
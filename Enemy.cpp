#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int x, int y, int deltaX, int deltaY)
	:PlaceableActor(x, y)
	, m_currentlyMovementX(0)
	, m_currentlyMovementY(0)
	, m_directionX(0)
	, m_directionY(0)
	, m_movmentInX(deltaX)
	, m_movmentInY(deltaY)
{
	if (m_movmentInX != 0)
	{
		m_directionX = 1;
	}
	if (m_movmentInY != 0)
	{
		m_directionY = 1;
	}
}

void Enemy::Draw()
{
	std::cout << (char)153;
}

void Enemy::Update()
{
	if (m_movmentInX != 0)
	{
		UpdateDirection(m_currentlyMovementX, m_directionX, m_movmentInX);
	}
	if (m_movmentInY != 0)
	{
		UpdateDirection(m_currentlyMovementY, m_directionY, m_movmentInY);
	}

	this->SetPosition(m_pPosition->x + m_directionX, m_pPosition->y + m_directionY);
}

void Enemy::UpdateDirection(int& current, int& direction, int& movement)
{
	current += direction;
	if (std::abs(current) > movement)
	{
		current = movement * direction;
		direction *= -1;
	}
}
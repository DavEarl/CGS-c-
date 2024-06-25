#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Game.h"
#include <assert.h>
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Goal.h"
#include "AudioManager.h"

using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;

Game::Game()
	: m_isGameOver(false)
{

}

Game::~Game()
{

}

bool Game::Load()
{
	return m_Level.Load("level3", m_player.GetXPositionPointer(), m_player.GetYPositionPointer());
}

void Game::Run()
{
	Draw();

	m_isGameOver = Update();

	if (m_isGameOver)
	{
		Draw();
	}
}

bool Game::IsGameOver()
{
	return m_isGameOver;
}

bool Game::Update()
{
	char input = (char)_getch();
	int arrowInput = 0;
	int newPlayerX = m_player.GetXPosition();
	int newPlayerY = m_player.GetYPosition();

	// one of the arrow keys were pressed
	if (input == kArrowInput)
	{
		arrowInput = _getch();
	}

	if ((input == kArrowInput && arrowInput == kLeftArrow) ||
		(char)input == 'A' || (char)input == 'a')
	{
		newPlayerX--;
	}

	else if ((input == kArrowInput && arrowInput == kRightArrow) ||
		(char)input == 'D' || (char)input == 'd')
	{
		newPlayerX++;
	}

	else if ((input == kArrowInput && arrowInput == kUpArrow) ||
		(char)input == 'W' || (char)input == 'w')
	{
		newPlayerY--;
	}

	else if ((input == kArrowInput && arrowInput == kDownArrow) ||
		(char)input == 'S' || (char)input == 's')
	{
		newPlayerY++;
	}

	else if (input == kEscapeKey)
	{
		m_UserQuit = true;
		return true;
	}

	else if ((char)input == 'Z' || (char)input == 'z')
	{
		m_player.DropKey();
	}

	//if position never changed
	if (newPlayerX == m_player.GetXPosition() && newPlayerY == m_player.GetYPosition())
	{
		return false;
	}
	else
	{
		return HandleCollision(newPlayerX, newPlayerY);
	}

}

//Returns true if player beats game or loses all lives
bool Game::HandleCollision(int newPlayerX, int newPlayerY)
{
	bool isGameDone = false;
	PlaceableActor* collidedActor = m_Level.UpdateActors(newPlayerX, newPlayerY);
	if (collidedActor != nullptr && collidedActor->IsActive())
	{
		switch (collidedActor->GetType())
		{
		case ActorType::Enemy:
		{
			Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
			assert(collidedEnemy);
			AudioManager::GetInstance()->PlayLoseLivesSound();
			collidedEnemy->Remove();
			m_player.SetPosition(newPlayerX, newPlayerY);

			m_player.Decrementlives();
			if (m_player.GetLives() < 0)
			{
				isGameDone = true;
			}
			break;
		}
		case ActorType::Money:
		{
			Money* collidedMoney = dynamic_cast<Money*>(collidedActor);
			assert(collidedMoney);
				collidedMoney->Remove();
				m_player.AddMoney(collidedMoney->GetWorth());
				m_player.SetPosition(newPlayerX, newPlayerY);
				AudioManager::GetInstance()->PlayMoneySound();
				break;
		}
		case ActorType::Key:
		{
			Key* collidedKey = dynamic_cast<Key*>(collidedActor);
			assert(collidedKey);
			AudioManager::GetInstance()->PlayKeyPickupSound();
				if (!m_player.HasKey())
				{
					m_player.PickupKey(collidedKey);
					collidedKey->Remove();
					m_player.SetPosition(newPlayerX, newPlayerY);
				}
			break;
		}
		case ActorType::Door:
		{
			Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
			assert(collidedDoor);
				if (!collidedDoor->IsOpen())
				{
					if (m_player.HasKey(collidedDoor->GetColor()))
					{
						collidedDoor->Open();
						collidedDoor->Remove();
						m_player.UseKey();
						m_player.SetPosition(newPlayerX, newPlayerY);
						AudioManager::GetInstance()->PlayDoorOpenSound();
					}
				}
				else
				{
					AudioManager::GetInstance()->PlayDoorOpenSound();
				}
			break;
		}
		case ActorType::Goal:
		{
			Goal* collidedGoal = dynamic_cast<Goal*>(collidedActor);
			assert(collidedGoal);
				collidedGoal->Remove();
				m_player.SetPosition(newPlayerX, newPlayerY);
				isGameDone = true;
			break;
		}
		default:
			break;
		}
	}
	else if (m_Level.IsSpace(newPlayerX, newPlayerY))//no colision
	{
		m_player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_Level.IsWall(newPlayerX, newPlayerY))
	{
		// is wall, do nothing
	}

	return isGameDone;
}

void Game::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	m_Level.Draw();

	//set cursor position for player
	COORD actorCusorPosition;
	actorCusorPosition.X = m_player.GetXPosition();
	actorCusorPosition.Y = m_player.GetYPosition();
	SetConsoleCursorPosition(console, actorCusorPosition);
	m_player.Draw();

	//set cursor to the end of the level
	COORD currentCursorPosition;
	currentCursorPosition.X = 0;
	currentCursorPosition.Y = m_Level.GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);
}
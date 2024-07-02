#include "GameplayState.h"
#include <iostream>
#include <conio.h>
#include <assert.h>
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Goal.h"
#include "AudioManager.h"
#include "Utility.h"
#include "StateMachineExampleGame.h"

using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;

GameplayState::GameplayState(StateMachineExampleGame* pOwner)
	:m_pOwner(pOwner)
	,m_beatGame(false)
	,m_skipFramesCount(0)
	,m_currentLevel(0)
	,m_pLevel(nullptr)
{
	m_LevelNames.push_back("level1");
	m_LevelNames.push_back("level2");
	m_LevelNames.push_back("level3");
}

GameplayState::~GameplayState()
{
	delete m_pLevel;
	m_pLevel = nullptr;
}

bool GameplayState::Load()
{
	if (m_pLevel)
	{
		delete m_pLevel;
		m_pLevel = nullptr;
	}

	m_pLevel = new Level();

	return m_pLevel->Load(m_LevelNames.at(m_currentLevel), m_player.GetXPositionPointer(), m_player.GetYPositionPointer());
}

void GameplayState::Enter()
{
	Load();
}

bool GameplayState::Update(bool processInput)
{
	if (processInput && !m_beatGame)
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
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
		}

		else if ((char)input == 'Z' || (char)input == 'z')
		{
			m_player.DropKey();
		}

		//if position never changed
		if (newPlayerX == m_player.GetXPosition() && newPlayerY == m_player.GetYPosition())
		{
			
		}
		else
		{
			HandleCollision(newPlayerX, newPlayerY);
		}


	}
	if (m_beatGame)
	{
		++m_skipFramesCount;
		if (m_skipFramesCount > kFramesToSkip)
		{
			m_skipFramesCount = 0;
			Utility::WriteHighScore(m_player.GetMoney());
			AudioManager::GetInstance()->PlayWinSound();
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Win);
		}
	}
	return false;
}

void GameplayState::HandleCollision(int newPlayerX, int newPlayerY)
{
	bool isGameDone = false;
	PlaceableActor* collidedActor = m_pLevel->UpdateActors(newPlayerX, newPlayerY);
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
				AudioManager::GetInstance()->PlayLoseSound();
				m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
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
			m_beatGame = true;
			break;
		}
		default:
			break;
		}
	}
	else if (m_pLevel->IsSpace(newPlayerX, newPlayerY))//no colision
	{
		m_player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_pLevel->IsWall(newPlayerX, newPlayerY))
	{
		// is wall, do nothing
	}

}

void GameplayState::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	m_pLevel->Draw();

	//set cursor position for player
	COORD actorCusorPosition;
	actorCusorPosition.X = m_player.GetXPosition();
	actorCusorPosition.Y = m_player.GetYPosition();
	SetConsoleCursorPosition(console, actorCusorPosition);
	m_player.Draw();

	//set cursor to the end of the level
	COORD currentCursorPosition;
	currentCursorPosition.X = 0;
	currentCursorPosition.Y = m_pLevel->GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);

	DrawHUD(console);
}

void GameplayState::DrawHUD(const HANDLE& console)
{
	cout << endl;

	//draw top border
	for (int i = 0; i < m_pLevel->GetWidth();  i++)
	{
		cout << Level::WAL;

	}
	cout << endl;

	//left border
	cout << Level::WAL;

	cout << "wasd-move " << Level::WAL << "z-drop key" << Level::WAL;
	cout << "$:" << m_player.GetMoney() << " " << Level::WAL;
	cout << "lives:" << m_player.GetLives() << " " << Level::WAL;
	cout << "Key:";
	if (m_player.HasKey())
	{
		m_player.GetKey()->Draw();
	}
	else
	{
		cout << " ";
	}

	//right border
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);

	COORD pos;
	pos.X = m_pLevel->GetWidth() - 1;
	pos.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(console, pos);

	cout << Level::WAL;
	cout << endl;

	//bottom border

	for (int i = 0; i < m_pLevel->GetWidth(); ++i)
	{
		cout << Level::WAL;
	}
	cout << endl;

}
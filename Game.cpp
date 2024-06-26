#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Game.h"

using namespace std;

constexpr int kOpenDoorColor = 10;
constexpr int kClosedDoorColor = 12;
constexpr int kRegularColor = 7;

Game::Game()
	: m_isGameOver(false)
{

}

Game::~Game()
{

}

bool Game::Load()
{
	return m_Level.Load("level1", m_player.GetXPositionPointer(), m_player.GetYPositionPointer());
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

	int newPlayerX = m_player.GetXPosition();
	int newPlayerY = m_player.GetYPosition();

	switch (input)
	{
	case 'w':
	case 'W':
	{
		newPlayerY--;
		break;
	}
	case 's':
	case 'S':
	{
		newPlayerY++;
		break;
	}
	case 'a':
	case 'A':
	{
		newPlayerX--;
		break;
	}
	case 'd':
	case 'D':
	{
		newPlayerX++;
		break;
	}
	default:
		break;
	}

	if (m_Level.IsSpace(newPlayerX, newPlayerY))
	{
		m_player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_Level.IsKey(newPlayerX, newPlayerY))
	{
		m_Level.PickUpKey(newPlayerX, newPlayerY);
		m_player.PickupKey();
		m_player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_Level.IsDoor(newPlayerX, newPlayerY) && m_player.HasKey())
	{
		m_Level.OpenDoor(newPlayerX, newPlayerY);
		m_player.UseKey();
		m_player.SetPosition(newPlayerX, newPlayerY);
		//PlayDoorOpenSound();
	}
	else if (m_Level.IsDoor(newPlayerX, newPlayerY) && !m_player.HasKey())
	{
		//PlayDoorClosedSound();
	}
	else if (m_Level.IsGoal(newPlayerX, newPlayerY))
	{
		m_player.SetPosition(newPlayerX, newPlayerY);
		return true;
	}
	return false;
}

void Game::Draw()
{
	system("cls");
	for (int y = 0; y < m_Level.GetHeight(); y++)
	{
		for (int x = 0; x < m_Level.GetWidth(); x++)
		{
			if (m_player.GetXPosition() == x && m_player.GetYPosition() == y)
			{
				m_player.Draw();
			}
			else
			{
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				if (m_Level.IsDoor(x, y))
				{
					if (m_player.HasKey())
					{
						SetConsoleTextAttribute(console, kOpenDoorColor);
					}
					else
					{
						SetConsoleTextAttribute(console, kClosedDoorColor);
					}
				}
				else
				{
					SetConsoleTextAttribute(console, kRegularColor);
				}

				m_Level.Draw(x, y);
			}
		}
		cout << endl;
	}
}
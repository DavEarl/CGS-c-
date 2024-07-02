#include "HighScoreState.h"
#include "MainMenuState.h"
#include <iostream>
#include <conio.h>
#include "StateMachineExampleGame.h"
#include "Utility.h"

using namespace std;

HighScoreState::HighScoreState(StateMachineExampleGame* pOwner)
	:m_pOwner(pOwner)
{
	m_HighScores = Utility::WriteHighScore(0);
}

bool HighScoreState::Update(bool processInput)
{
	bool shouldQuit = false;
	if (processInput)
	{
		int input = _getch();
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}
	return shouldQuit;
}

void HighScoreState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          ------High Scores------" << endl << endl;

	for (auto i = m_HighScores.rbegin(); i != m_HighScores.rend(); i++)
	{
		cout << "              " << *i << endl;
	}

	cout << endl << endl;
	cout << "   Press any key to go back to Main Menu" << endl;
}
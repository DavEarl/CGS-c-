#include "LoseState.h"
#include <iostream>
#include <conio.h>
#include "StateMachineExampleGame.h"

using namespace std;

LoseState::LoseState(StateMachineExampleGame* pOwner)
	:m_pOwner(pOwner)
{

}

bool LoseState::Update(bool processInput)
{
	if (processInput)
	{
		int input = _getch();
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}
	return false;
}

void LoseState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          ------Game Over------" << endl << endl;
	cout << "          Better Luck Next Time!!!" << endl << endl;
	cout << "      Press Any Key to Go Back to Main Menu" << endl << endl;
}
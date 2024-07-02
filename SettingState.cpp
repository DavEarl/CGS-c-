#include "SettingState.h"
#include "MainMenuState.h"
#include <iostream>
#include <conio.h>
#include "StateMachineExampleGame.h"
#include "AudioManager.h"

using namespace std;

constexpr int kEscapeKey = 27;
constexpr char kSound = '1';
constexpr char kMainMenu = '2';

SettingState::SettingState(StateMachineExampleGame* pOwner)
	:m_pOwner(pOwner)
{

}

bool SettingState::Update(bool processInput)
{
	bool shouldQuit = false;
	if (processInput)
	{
		int input = _getch();
		if (input == kEscapeKey || (char)input == kMainMenu)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
		}
		else if ((char)input == kSound)
		{
			AudioManager::GetInstance()->ToggleSound();
			AudioManager::GetInstance()->PlayMoneySound();
		}
	}
	return shouldQuit;
}

void SettingState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          ------Settings------" << endl << endl;
	cout << "            " << kSound << ". Toggle Sound: ";
	if (AudioManager::GetInstance()->IsSoundOn())
	{
		cout << "ON" << endl;
		Beep(500, 50);
	}
	else
	{
		cout << "OFF" << endl;
	}
	cout << "            " << kMainMenu << ". Main Menu" << endl;
}
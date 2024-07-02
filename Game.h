#pragma once
#include "GameStateMachine.H"

class Game
{
	GameStateMachine* m_pStateMachine;


public:
	Game();
	void Initialize(GameStateMachine* pStateMachine);
	void RunGameLoop();
	void Deinitialize();

private:
	bool Update(bool processInput = true);
	void Draw();

};
#pragma once
#include "GameState.H"

class StateMachineExampleGame;


class WinState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	WinState(StateMachineExampleGame* pOwner);
	~WinState() = default;

	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;
};


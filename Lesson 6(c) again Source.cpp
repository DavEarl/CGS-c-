#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
	Game myGame;

	if (myGame.Load())
	{
		while (!myGame.IsGameOver())
		{
			myGame.Run();
		}

		cout << "YOU WIN!!!" << endl;

	}
	else
	{
		cout << "game did not load, terminating" << endl;
	}
}


//void PlayDoorClosedSound()
//{
//	Beep(500, 75);
//	Beep(500, 75);
//}
//
//void PlayDoorOpenSound()
//{
//	Beep(1397, 200);
//}
//
//void PlayKeyPickupSound()
//{
//	Beep(1568, 200);
//}
//
//void PlayWinSound()
//{
//	Beep(100, 100);
//}

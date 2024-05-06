#include <iostream>
using namespace std;

int main()
{
	int num1;
	int varri1 = 1;

	cout << "please enter a number: ";
	cin >> num1;
	
	do {
		if (num1 < 0)
		{
			num1 * -1;
		}
		if (num1 % varri1 == 0)
		{
			cout << varri1 << endl;
		}
		varri1++;


	} while (varri1 <= num1);
	
	
	/*
	for (int varri1 = 1; varri1 <= num1; varri1++)
	{
		if (num1 < 0)
		{
			num1 * -1;
		}
		if (num1 % varri1 == 0)
		{
			cout << varri1 << endl;
		}
	}
	*/
}
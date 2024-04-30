#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
using namespace std;

int cubing(int cube);

int main()
{
	int cube = 1;
	int exponent = 1;
	
	cout << "please enter a number to be cubed: " << endl;
	cin >> cube;

	cout << cubing(cube);
}

int cubing(int cube)
{
	return pow(cube, 3);
}
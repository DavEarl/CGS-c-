#include <iostream>
using namespace std;

int Swap(int* ptrA, int* ptrB);

int main()
{
	cout << "please enter 2 numbers to be swaped: " << endl;
	int a;
	cin >> a;
	int b;
	cin >> b;

	Swap(&a, &b);
	cout << endl << "here are your swapped numbers: " << a << " " << b << endl;

	cout << "Please enter a number to be put stored in a pointer: " << endl;
	int varri1 = 0;
	cin >> varri1;

	int* pointer = &varri1;

	cout << "here is your number: " << *pointer << endl;
	cout << "here is your number as a pointer: " << pointer << endl;

}

int Swap(int* ptrA, int* ptrB)
{
	int temp = *ptrA;
	*ptrA = *ptrB;
	*ptrB = temp;

	return *ptrA, * ptrB;
}
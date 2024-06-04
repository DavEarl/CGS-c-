#include <iostream>
using namespace std;

void DisplayArray(int theArray[], int size);
void DisplayArray2(int* theArray, int size);

int main()
{
	int myArray[3]{ 10, 20, 30 };
	int* pArrayPointer = myArray;

	cout << myArray[0] << endl;
	cout << myArray[1] << endl;
	cout << myArray[2] << endl;

	cout << pArrayPointer[0] << endl;
	cout << pArrayPointer[1] << endl;
	cout << pArrayPointer[2] << endl;

	cout << *(pArrayPointer + 0) << endl;
	cout << *(pArrayPointer + 1) << endl;
	cout << *(pArrayPointer + 2) << endl;

	cout << *(myArray + 0) << endl;
	cout << *(myArray + 1) << endl;
	cout << *(myArray + 2) << endl;

	//these all are different ways of saying the same thing

}

void DisplayArray(int theArray[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << theArray[i] << " ";
	}
}

void DisplayArray2(int* theArray, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << theArray[i] << " ";
	}
}
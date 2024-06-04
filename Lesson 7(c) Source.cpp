#include <iostream>
using namespace std;


int main()
{
	//new dataType{ initialValue };


	//this is how you allocate dynamic memory
	//YOU NEED TO DEACTIVATE THE POINTERS WHEN YOU ARE FINISHED WITH THEM
	int* pInt = new int{ 10 };
	float* pFloat = new float{ 20.5 };
	bool* pBool = new bool{ true };


	//this is how you deactivate it
	delete pInt;
	pInt = nullptr;

	delete pFloat;
	pFloat = nullptr;

	delete pBool;
	pBool = nullptr;


	//to activate and delete pointer arrays is verry similar
	int* pIntArray = new int[5];
	float* pFloatArray = new float[5];
	bool* pBoolArray = new bool[5];

	//this is how you delete them
	delete[] pIntArray;
	pIntArray = nullptr;

	delete[] pFloatArray;
	pFloatArray = nullptr;

	delete[] pBoolArray;
	pBoolArray = nullptr;
}



/* This is static allocation
* int other words, static allocation is when an array's limits are known before compiling

constexpr int kSize = 3;
int myArray[kSize]{10 ,20 ,30};
int* pArrayPointer = myArray;

*/
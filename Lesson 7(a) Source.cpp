#include <iostream>
using namespace std;

void Swap(int* pNum1, int* pNum2);
void Swap(int& Num1, int& Num2);

/*
int main()
{
	int varri1 = 10;
	int* pointer = &varri1;

	int varri2 = *pointer; // 10
	*pointer = 20;//varri1 == 20


	cout << "varriable: " << varri1 << endl;//20
	cout << "variable address: " << &varri1 << endl;//
	cout << "pointer: " << pointer << endl;//
	cout << "pointer address: " << &pointer << endl;

	cout << "value in pointer: " << *pointer << endl;//20

}*/


int main()
{
	int a = 10;
	int b = 20;

	Swap(a, b);
	cout << "a" << a << endl << "b" << b << endl;
}

void Swap(int* pNum1, int* pNum2)
{
	int temp = *pNum1;
	*pNum1 = *pNum2;
	*pNum2 = temp;
}

void Swap(int& Num1, int& Num2)
{
	int temp = Num1;
	Num1 = Num2;
	Num2 = temp;
}
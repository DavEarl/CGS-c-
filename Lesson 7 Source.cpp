#include <iostream>
using namespace std;


int main()
{
	int a = 5;
	int b = 1;
	int& c = a;

	c = b;

	cout << a;// 1
	cout << b;//1
	cout << c;//1
	//the reason this happens is that when the computer needs to get 'a' it works backwards
	//since it sees that c is = to b or 1, it asumes that a must also equal 1
}
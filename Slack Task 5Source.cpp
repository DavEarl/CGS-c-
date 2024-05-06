#include <iostream>
using namespace std;

int main()
{
	char pyramid = 65;
	int input = 1;
	int BASE = 65;

	cout << "please input a number: ";
	cin >> input;

	for (int loop = 0; loop < input; loop++)
	{
		for (int spaceLoop = 1; input - spaceLoop - loop; spaceLoop++)
		{
			cout << " ";
		}
		for (int loop2; pyramid <= BASE + loop -1; pyramid++)
		{
			cout << pyramid;

		}
		//pyramid = 65;
		for (int loop3; pyramid >= BASE ; pyramid--)
		{
			cout << pyramid;
		}
		pyramid = 65;
		//cout << pyramid << endl;
		cout << endl;
	}

}
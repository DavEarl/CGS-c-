#include <iostream>

using namespace std;


class Car
{
public:
	//default constructor:
	Car()
	{
		cout << "default constructor" << endl;
	}

	//decpmstructor
	~Car()
	{
		cout << "deconstructor" << endl;
	}
};

int main()
{
	Car* pMyCar = new Car;
	if (pMyCar != nullptr)
	{
		Car myCar;
	}
	delete pMyCar;
}
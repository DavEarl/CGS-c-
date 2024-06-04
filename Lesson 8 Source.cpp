#include <iostream>

using namespace std;

//typically you want to make all member variables private

class Car
{
public:
	//default constructor:

	//member variables
	int m_year;
	int m_miles;
	string m_brand;

	//member functions
	void Display()
	{
		cout << "brand: " << m_brand << endl;
		cout << "year: " << m_year << endl;
		cout << "miles: " << m_miles << endl;
	}
	void Drive(int miles)
	{
		m_miles = m_miles + miles;
	}
	//destructor
	~Car();
};

int main()
{

//variable called myVariable of int type
int myVariable;

//objects called myCar of Car type
Car myCar;
Car myDadsCar;
Car fastCar;
Car slowCar;


Car * pCurrentCar = &myCar;
pCurrentCar = &myDadsCar;
pCurrentCar = nullptr;

Car& currentCar = myCar;


//dynamic allocation
Car* pCar = new Car;

//vroom vroom
delete pCar;

Car myCar;
myCar.m_brand = "bmw";
myCar.m_year = 2019;
myCar.m_miles = 20;
myCar.Drive(10);
myCar.Display();

Car* pCar = new Car;
(*pCar).m_brand = "Ford";
(*pCar).m_year = 2018;
(*pCar).m_miles = 300;
(*pCar).Drive(100);
(*pCar).Display();
delete pCar;
pCar = nullptr;

//another way to dereferecne a pointer using -> rather than (*)
Car* pCar = new Car;
pCar->m_brand = "Ford";
pCar->m_year = 2018;
pCar->m_miles = 300;
pCar->Drive(100);
pCar->Display();
delete pCar;
pCar = nullptr;

}
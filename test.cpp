#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class A
{
private:
	int x;
	int *arr;
public:
	A();
	A(int s);
	A(const A& a1);
	A& operator = (const A& a1);
	~A();


	inline int getX()const{return x;};
	
	void printArr()const
	{
		for(int i=0; i<x; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
};

A::A() : x(5), arr(nullptr)
{
	cout << "default constructor çalıştı" << endl;
	arr = new int[x];
	for(int i=0; i<x; i++)
		arr[i] = i * 10;
}

A::A(int s) : x(s), arr(nullptr)
{
	cout << "conversion constructor çalıştı" << endl;
	arr = new int[x];
	for(int i=0; i<x; i++)
		arr[i] = i * 10;
}

A::A(const A& a1)
{
	cout << "copy constructor çalıştı" << endl;
	x = a1.getX();

	arr = new int[x];
	for(int i=0; i<x; i++)
		arr[i] = i * 10;
}

A& A::operator = (const A& a1)
{
	cout << "assignment operatorü çalıştı" << endl;
	if(arr != nullptr)
	{
		delete[] arr;
	}

	x = a1.getX();

	arr = new int[x];
	for(int i=0; i<x; i++)
		arr[i] = i * 10;

	return *this;
}

A::~A()
{
	cout << "destructor çalıştı" << endl;
	if(arr != nullptr)
		delete[] arr;
}


int main()
{
	int counter = 0;
	A* ptr = new A[2];

	cout << "----------------" << endl;

	ptr[counter++] = A();
	ptr[counter++] = A(8);

	cout << "----------------" << endl;	

	cout << "0th element : " << endl;
	ptr[0].printArr();
	cout << endl;

	cout << "1st element : " << endl;
	ptr[1].printArr();
	cout << endl;

	cout << "----------------" << endl;

	A* temp = new A[3];

	for(int i=0; i<counter; i++)
	{
		// assignment operator
		temp[counter] = ptr[counter];
	}

	temp[counter++] = A(9);

	delete[] ptr;
	ptr = nullptr;

	ptr = temp;

	temp = nullptr;

	cout << "----------------" << endl;
	for(int i=0; i<counter; i++)
	{
		ptr[i].printArr();
		cout << endl;
	}



	// vector <A> myVec;

	// myVec.push_back(A());
	// cout << "-------------" << endl;
	// myVec.push_back(A());
	// cout << "-------------" << endl;

	// // myVec.pop_back();

	// cout << "size : " << myVec.size() << endl;


	return 0;
}

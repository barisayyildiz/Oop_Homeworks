#include <iostream>

using namespace std;

class Test
{
private:
	int n;

	class Inner
	{
	private:
		int x;
	public:
		Inner(int val);
		int getX();
	};

public:
	// Burası neden böyle bilmiyorum!!!
	Inner i1 = Inner(1);
	
	Test();
	void setN(int num);
	int getN();

};

Test::Inner::Inner(int val) : x(val)
{/*left empty*/}

inline int Test::Inner::getX(){return x;}

Test::Test()
{
	cout << "hello world" << endl;
}

inline void Test::setN(int num)
{
	n = num;
}

inline int Test::getN(){ return n; }

int main()
{
	Test t1;
	t1.setN(9);
	cout << t1.getN() << endl;

	cout << t1.i1.getX() << endl;


	return 0;
}
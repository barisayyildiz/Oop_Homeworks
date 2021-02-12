#include <iostream>

using namespace std;

class A
{
private:
	int x;
public:
	class B
	{
	private:
		int y;
	public:
		explicit B(int s) : y(s)
		{/*left empty*/}
		inline int getY()const{return y;};
		inline void setY(int s){y = s;};
	};
	B *ptr;

	inline int getX()const{return x;};
	explicit A(int s, int a) : x(s), ptr(nullptr)
	{
		ptr = new A::B[a];
		for(int i=0; i<a; i++)
		{
			ptr.setY(i * 10);
		}
	}
};


int main()
{



	return 0;
}


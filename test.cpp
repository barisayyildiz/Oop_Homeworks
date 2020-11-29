#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class A
{
private:
	int x, y;
	string fileName;
public:
	A(int a, int b) : x(a), y(b)
	{/*left empty*/}

	inline int getX(){return x;};
	inline int getY(){return y;};
	inline string getFileName(){return fileName;};
	inline void setFileName(string s){fileName = s;};

	friend ofstream& operator << (std::ofstream &fout, A &a1);

};

ofstream& operator << (std::ofstream &fout, A &a1)
{
	fout << "x : " << a1.getX() << ", y : " << a1.getY();


	return fout;
}


int main()
{
	A obj(4564,12312412);

	ofstream fout;

	fout.open("board1.txt");

	fout << obj << endl;

	fout.close();

	return 0;
}

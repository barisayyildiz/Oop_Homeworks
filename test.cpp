#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "hex.h"

using namespace std;


int main()
{
	Hex h1;

	Hex h2;


	h2 = h1;

	cout << h2.getSize() << endl;
	

	return 0;
}

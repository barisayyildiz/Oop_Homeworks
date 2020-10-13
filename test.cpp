#include <iostream>

using namespace std;


int func(int *arr, int counter)
{
	if(counter == 2)
		return 1;

	//arr[counter++] = 1;

	

	func(arr, counter);
}

int main()
{

	int arr[4] = {0,0,0,0};

	func(arr, 0);


	for(int i=0; i<4; i++)
	{
		cout << arr[i] << endl;
	}


	



	return 0;
}
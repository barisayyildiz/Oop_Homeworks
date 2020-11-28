#include <iostream>
#include <string>

using namespace std;

int** initArr(int size)
{
	int **temp = nullptr;

	temp = new int*[size];

	for(int i=0; i<size; i++)
		temp[i] = new int[size];

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			temp[i][j] = 1;
		}
	}

	return temp;
}


void draw(int **arr, int size)
{
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

}

int** resize(int **arr, int oldSize, int newSize)
{
	int **temp = new int*[newSize];

	for(int i=0; i<newSize; i++)
		temp[i] = new int[newSize];

	for(int i=0; i<oldSize; i++)
	{
		for(int j=0; j<oldSize; j++)
		{
			temp[i][j] = arr[i][j];
		}
	}


	for(int i=oldSize; i<newSize; i++)
	{
		for(int j=0; j<newSize; j++)
		{
			temp[i][j] = 2;
		}
	}


	return temp;

}

int main()
{
	int size = 5;

	int **arr = nullptr;

	arr = initArr(size);

	draw(arr, size);

	arr = resize(arr, 5, 10);
	size = 10;

	cout << "------------------" << endl;

	draw(arr, size);


	for(int i=0; i<size; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;

	arr = nullptr;


	return 0;
}

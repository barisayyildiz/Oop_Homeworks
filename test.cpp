#include <iostream>
#include <vector>
#include <exception>
#include "hexbase.h"
#include "hexarray.h"
#include "hexvector.h"
#include "hexadapter.h"
#include "hexadapter.cpp"
#include "exception.h"

using namespace std;
using namespace hex;
using namespace excNamespace;


template<template<class ...> class T>
void test(const AbstractHex *h1)
{
	HexAdapter<T> *ptr = dynamic_cast<HexAdapter<T>*>(h1);
}

int main()
{
	// // vector < AbstractHex * > gameVector;

	// // gameVector.push_back(new HexAdapter<vector>());

	// HexAdapter<vector> h1;

	vector < AbstractHex * > gameVector;

	gameVector.push_back(new HexVector(8));
	gameVector.push_back(new HexArray1D(6));
	gameVector.push_back(new HexVector(9));

	bool val = *gameVector[0] == gameVector[2];

	cout << val << endl;

	gameVector.push_back(new HexAdapter<vector>(9));

	test(gameVector[3]);


}


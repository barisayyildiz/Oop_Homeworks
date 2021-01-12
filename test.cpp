#include <iostream>
#include <vector>
#include <deque>
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


	gameVector.push_back(new HexAdapter<deque>(9));
	gameVector.push_back(new HexVector(12));
	gameVector.push_back(new HexArray1D(9));
	
	
	bool val = *gameVector[0] == gameVector[2];

	cout << val << endl;


}


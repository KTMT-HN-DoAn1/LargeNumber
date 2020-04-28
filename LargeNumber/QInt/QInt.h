#pragma once
#include <iostream>
#include <string>

using namespace std;

class QInt
{
public:
	int data[4];

	QInt();
	QInt(QInt& q);
	~QInt();

	void scanQInt();
	void printQInt();
	
};

#pragma once
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

class QFloat
{
public:
	int data[4];
	QFloat();
	~QFloat();
	QFloat BinToDec(bool* bit);
	bool* DecToBin(QFloat x);
	void ABC(bool* bit, int a);
};

int countPoint(string s);
int checkNumber(string s);
int checkInputQFloat(string s);
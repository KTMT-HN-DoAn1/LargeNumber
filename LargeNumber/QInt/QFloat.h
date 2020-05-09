#pragma once
#include "QInt.h"
#include "Convert.h"


class QFloat
{
public:
	int data[4];
	QFloat();
	~QFloat();
	
};

int countPoint(string s);
int checkNumber(string s);
int checkInputQFloat(string s);

void ScanQFloat(QFloat& x, string s);
void ScanBinQFloat(QFloat& x, string s);
QFloat FBinToDec(bool* bit);
bool* FDecToBin(QFloat x);
void plusOneBit(bool* bit);
void printQfloat(QFloat out, int outForm);
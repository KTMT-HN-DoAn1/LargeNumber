#pragma once
#include "QInt.h"
#include "Convert.h"


class QFloat
{
public:
	int data[4];
	QFloat();
	QFloat(QFloat& q);
	~QFloat();
	QFloat operator=(QFloat& q);
	QFloat operator=(string s);

	void setZero();
	void setInfinity(bool signbit);
	void setNaN();
	
};

int countPoint(string s);
int checkNumber(string s);
int checkInputQFloat(string s);

void ScanQFloat(QFloat& x, istream& in);
void ScanBinQFloat(QFloat& x, istream& in);
QFloat FBinToDec(bool* bit);
bool* FDecToBin(QFloat x);
void plusOneBit(bool* bit);
void shiftRigthFrac(bool* bit);
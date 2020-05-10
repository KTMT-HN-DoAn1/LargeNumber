#pragma once
#include "QInt.h"
#include "Convert.h"
#include<fstream>
using namespace std;

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

void ScanQFloat(QFloat& x, string s);
void ScanBinQFloat(QFloat& x, string s);
QFloat FBinToDec(bool* bit);
bool* FDecToBin(QFloat x);
void plusOneBit(bool* bit);
void printQfloat(QFloat out, int outForm);
void shiftRigthFrac(bool* bit);

//in Qfloat ra file
void printQFloatToFile(fstream& f, QFloat out, int outForm);
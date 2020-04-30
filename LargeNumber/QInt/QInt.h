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

	//Hàm nhập từ console
	void scanQInt();
	//Hàm xuất ra console
	void printQInt();

	//Toán tử &.
	QInt operator&(const QInt&);
	//Toán tử |.
	QInt operator|(const QInt&);
	//Toán tử ^.
	QInt operator^(const QInt&);
	//Toán tử ~.
	QInt& operator~();
	//Phép toán dịch phải(Shift Right).
	QInt operator >> (const int&);
	//Phép toán dịch trái(Shift Left).
	QInt operator << (const int&);
	//Phép toán xoay trái.
	QInt& RoL(int n);
	//Phép toán xoay phải.
	QInt& RoR(int n);

	QInt operator + (QInt&);

};

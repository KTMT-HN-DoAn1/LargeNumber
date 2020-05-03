#include "Menu.h"

void gotoXY(int x, int y)
{
	// hàm tham khảo theo code tiêu chuẩn
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x,y };
	SetConsoleCursorPosition(h, c);
}

void Color(int colour)
{
	//hàm tham khảo tiêu chuẩn
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, colour);
}

int printMainMenu()
{
	int lenh;
	Color(14);
	gotoXY(30, 10);
	cout << "================================================================" << endl;
	gotoXY(30, 11);
	cout << "|                       MY CALCULATOR                          |" << endl;
	gotoXY(30, 12);
	cout << "================================================================" << endl;
	gotoXY(30, 13);
	cout << "|           1. QINT                                            |" << endl;
	gotoXY(30, 14);
	cout << "|           2. QFLOAT                                          |" << endl;
	gotoXY(30, 15);
	cout << "|                                YOUR CHOICE: [ ]              |" << endl;
	gotoXY(30, 16);
	cout << "================================================================" << endl;
	gotoXY(77,15);
	cin >> lenh;
	return lenh;
}

void printConvertFrame()
{
	gotoXY(30, 10);
	cout << "================================================================" << endl;
	gotoXY(30, 11);
	cout << "|                       MY CALCULATOR                          |" << endl;
	gotoXY(30, 12);
	cout << "================================================================" << endl;
	gotoXY(3, 13);
	cout << "1. DEC: " << endl;
	gotoXY(3, 14);
	cout << "2. BIN: " << endl;
	gotoXY(3, 15);
	cout << "1. HEX: " << endl;
	gotoXY(3, 16);
	cout << "Your Input: " << endl;
}

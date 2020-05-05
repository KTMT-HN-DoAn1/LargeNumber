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

void printFrame()
{
	Color(14);
	int x = startFrameX;
	int y = startFrameY;
	gotoXY(x, y);
	cout << "================================================================" << endl;
	gotoXY(x, y + 1);
	cout << "|                       MY CALCULATOR                          |" << endl;
	gotoXY(x, y + 2);
	cout << "================================================================" << endl;

	for (int i = 0; i <= heightMenu; ++i)
	{
		gotoXY(x, startMenuY + i);
		cout << "|                                                              |" << endl;
	}
	gotoXY(x, startMenuY + heightMenu + 1);
	cout << "================================================================" << endl;
}

int printMainMenu()
{
	int lenh;
	Color(14);
	
	gotoXY(startFrameX, startMenuY);
	cout << "|           1. QINT                                            |" << endl;
	gotoXY(startFrameX, startMenuY + 1);
	cout << "|           2. QFLOAT                                          |" << endl;
	gotoXY(startFrameX, startMenuY + 2);
	cout << "|                                YOUR CHOICE: [ ]              |" << endl;
	gotoXY(77, startMenuY + 2);
	cin >> lenh;
	return lenh;
}

void printModeFrame()
{
	printFrame();
	gotoXY(startMenuX + 2, startMenuY);
	cout << "1. Arithmetic: " << endl;
	gotoXY(startMenuX + 2, startMenuY + 1);
	cout << "2. Convertion: " << endl;
	gotoXY(startMenuX + 2, startMenuY + 2);
	cout << "Your Input: " << endl;
	int choice;
	gotoXY(startMenuX + 2 + 13, startMenuY + 3);
	cin >> choice;

	if (choice == 1)
	{

	}
	else {
		printConvertFrame();
	}
}

void printConvertFrame()
{
	printFrame();
	gotoXY(startMenuX + 2, startMenuY);
	cout << "Chosse your input state: " << endl;
	gotoXY(startMenuX + 2, startMenuY + 1);
	cout << "1. DEC: " << endl;
	gotoXY(startMenuX + 2, startMenuY + 2);
	cout << "2. BIN: " << endl;
	gotoXY(startMenuX + 2, startMenuY + 3);
	cout << "3. HEX: " << endl;
	gotoXY(startMenuX + 2, startMenuY + 4);
	cout << "Your Input: " << endl;
	int choice;
	gotoXY(startMenuX + 2 + 13, startMenuY + 5);
	cin >> choice;

}

void inputQInt()
{

}
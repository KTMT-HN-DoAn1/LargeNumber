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

string overLoadInput() {
	char c;
	string bits;
	int count = 0;
	while (c = _getch()) {

		_getch();
		if (c == '\r') break;
		if (c == '\b') {
			if (count <= 0) continue;
			printf("\b \b");
			count--;
			continue;
		}
		if (c == '1')
			cout << '1';
		if (c == '0')
			cout << '0';
		if (count % 4 == 0 && count != 0)
			cout << " ";

		if (count == 24)
			gotoXY(startMenuX + 1, startMenuY + 2 + 1);
		if (count == 23)
			gotoXY(startMenuX + 63, startMenuY + 2);

		bits.push_back(c);
		count++;
	}
	cout << endl;
	return bits;
}

void printQIntConvertResult(int choice, string s)
{
	switch (choice)
	{
	case 1:
		gotoXY(startMenuX + 2, startMenuY + 2);
		cout << "2. BIN: ";

		gotoXY(startMenuX + 2, startMenuY + 5);
		cout << "3. HEX: ";
		break;
	case 2:
		gotoXY(startMenuX + 2, startMenuY + 1);
		cout << "1. DEC: " << endl;

		gotoXY(startMenuX + 2, startMenuY + 5);
		cout << "3. HEX: " << endl;
		break;
	case 3:
		gotoXY(startMenuX + 2, startMenuY + 1);
		cout << "1. DEC: " << endl;
		gotoXY(startMenuX + 2, startMenuY + 2);
		cout << "2. BIN: " << endl;
		break;
	}
	gotoXY(startMenuX + 2, startMenuY + 1);
	cout << "1. DEC: " << endl;
	gotoXY(startMenuX + 2, startMenuY + 2);
	cout << "2. BIN: " << endl;
	gotoXY(startMenuX + 2, startMenuY + 3);
	cout << "3. HEX: " << endl;
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
	gotoXY(startMenuX + 2, startMenuY + 5);
	cout << "3. HEX: " << endl;
	gotoXY(startMenuX + 2, startMenuY + 6);
	cout << "Your Input: " << endl;
	int choice;
	gotoXY(startMenuX + 2 + 13, startMenuY + 5);
	cin >> choice;

	string s;
	switch (choice)
	{
	case 1:
		gotoXY(startMenuX + 2 + 8, startMenuY + 1);
		cin >> s;
		
		break;
	case 2:
		gotoXY(startMenuX + 2 + 8, startMenuY + 2);
		s = overLoadInput();

		break;
	case 3:
		gotoXY(startMenuX + 2 + 8, startMenuY + 5);
		cin >> s;

		break;
	}

	printQIntConvertResult(choice, s);
}

void inputQInt()
{

}
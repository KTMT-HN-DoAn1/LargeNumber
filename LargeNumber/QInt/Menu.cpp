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
	gotoXY(startMenuX + 2 + 12, startMenuY + 2);
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
	int countCh = 0;
	int countBit = 0;
	int line = 0;
	while (c = _getch()) {


		if (c == '\r') break;
		if (c == '\b') {
			if (countCh <= 0) continue;

			if (!(((countBit) % 4) == 0 && countBit != 0)) {
				countBit--;
			}

			countCh--;
			bits.resize(countCh);

			//Nhảy lên dòng trên nếu user xóa tới kí tự đầu dòng.
			//Dòng 1.
			if (countCh == 87 && line == 2) {
				gotoXY(startMenuX + 58, startMenuY + 2 + 1);
				line = 1;
			}
			//Dòng 2.
			if (countCh == 47 && line == 1) {
				gotoXY(startMenuX + 58, startMenuY + 2);
				line = 0;
			}
			printf("\b \b");
			continue;
		}

		if (countBit >= 128) continue;

		if (c == '1') {
			cout << '1';
			countBit++;
		}
		else if (c == '0') {
			cout << '0';
			countBit++;
		}
		else
			continue;

		bits.push_back(c);
		if ( ((countBit) % 4) == 0 && countBit != 0) {
			cout << " ";
			bits.push_back(' ');
			countCh++;
		}
		countCh++;

		//Xuống dòng khi chạm biên
		if (countCh == 48) {
			gotoXY(startMenuX + 1, startMenuY + 2 + 1);
			line = 1;
		}		

		if (countCh == 84) {
			gotoXY(startMenuX + 1, startMenuY + 2 + 2);
			line = 2;
		}
		
	}
	//bits.resize(count);
	return bits;
}

void printQIntConvertResult(int choice, string s)
{
	QInt q;
	switch (choice)
	{
	case 1:
		q.scanQInt(10, s);

		gotoXY(startMenuX + 2, startMenuY + 2);
		cout << "2. BIN: ";
		q.printQInt(2);

		gotoXY(startMenuX + 2, startMenuY + 5);
		cout << "3. HEX: ";
		q.printQInt(16);
		break;
	case 2:
		q.scanQInt(2, s);

		gotoXY(startMenuX + 2, startMenuY + 1);
		cout << "1. DEC: ";
		q.printQInt(10);

		gotoXY(startMenuX + 2, startMenuY + 5);
		cout << "3. HEX: ";
		q.printQInt(16);
		break;
	case 3:
		q.scanQInt(16, s);

		gotoXY(startMenuX + 2, startMenuY + 1);
		cout << "1. DEC: ";
		q.printQInt(10);

		gotoXY(startMenuX + 2, startMenuY + 2);
		cout << "2. BIN: ";
		q.printQInt(2);
		break;
	}

	_getch();
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
	gotoXY(startMenuX + 2, startMenuY + 7);
	cout << "Your Input: " << endl;
	int choice;
	gotoXY(startMenuX + 2 + 12, startMenuY + 7);
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
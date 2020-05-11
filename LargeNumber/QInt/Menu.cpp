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

void printNotif()
{
	gotoXY(startMenuX, startMenuY + heightMenu + 1);
	cout << "================================================================" << endl;
	gotoXY(startMenuX, startMenuY + heightMenu + 2);
	cout << "|                                                              |" << endl;
	gotoXY(startMenuX, startMenuY + heightMenu + 3);
	cout << "|                                                              |" << endl;
	gotoXY(startMenuX, startMenuY + heightMenu + 4);
	cout << "================================================================" << endl;
	Color(ColorCode_DarkGreen);
	gotoXY(startMenuX + 5, startMenuY + heightMenu + 2);
	cout << "- Press anykey to back the previous menu." << endl;
	gotoXY(startMenuX + 5, startMenuY + heightMenu + 3);
	cout << "- Press Enter to make a new one. " << endl;
	Color(14);
}

void printFrame()
{
	Color(14);
	int x = startFrameX;
	int y = startFrameY;

	gotoXY(x, y);
	cout << "================================================================" << endl;
	gotoXY(x, y + 1);
	cout << "|                                                              |" << endl;
	gotoXY(x, y + 2);
	cout << "================================================================" << endl;
	Color(ColorCode_Cyan);
	gotoXY(x + 26, y + 1);
	cout << "MY CALCULATOR" << endl;
	Color(14);
	
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
	cout << "|           0. EXIT                                            |" << endl;
	gotoXY(startFrameX, startMenuY + 3);
	cout << "|                                YOUR CHOICE: [ ]              |" << endl;
	gotoXY(77, startMenuY + 3);
	cin >> lenh;
	return lenh;
}

//Lựa chọn chế độ tính toán.
int printModeFrame()
{
	printFrame();
	gotoXY(startMenuX + 10, startMenuY);
	cout << "1. Arithmetic: " << endl;
	gotoXY(startMenuX + 10, startMenuY + 1);
	cout << "2. Convertion: " << endl;
	gotoXY(startMenuX + 10, startMenuY + 2);
	cout << "0. Back to menu" << endl;
	gotoXY(startMenuX + 20, startMenuY + 3);
	cout << "Your Input [ ]" << endl;
	int choice;
	gotoXY(startMenuX + 20 + 12, startMenuY + 3);

	cin >> choice;
	return choice;
}

//Hàm điều chỉnh chuỗi nhập cho số nhị phân (do tới 128 bits nên sẽ phải xuống dòng).
string overLoadInput() {
	//Kí tự nhập vô hiện tại.
	char c;
	//Chuỗi nhị phân cuối cùng.
	string bits;
	//Độ dài chuỗi.
	int countCh = 0;
	//Số bit trong chuỗi.
	int countBit = 0;
	//Hàng hiện tại.
	int line = 0;

	//Mỗi lần nhận 1 kí tự.
	while (c = _getch()) {

		//Kết thúc khi user nhập Enter.
		if (c == '\r' || c == ' ') {
			cout << c; break;
		}

		//Khi user nhập phím xóa:
		if (c == '\b') {
			//Bỏ qua nếu đã xóa hết chuỗi.
			if (countCh <= 0) continue;

			//Nếu đang ở vị trí sau dấu cách 1 bit thì xóa bit đó và dấu cách.
			if (((countBit) % 4) == 1 && countBit != 1) {
				printf("\b \b");
				
				countCh--;
				bits.resize(countCh);
			}
			countBit--;
			countCh--;
			bits.resize(countCh);

			//Nhảy lên dòng trên nếu user xóa tới kí tự đầu dòng.
				//Dòng 2.
			if (countCh == 109 && line == 2) {
				gotoXY(startMenuX + 61, startMenuY + 2 + 1);
				line = 1;
			}
			//Dòng 1.
			if (countCh == 49 && line == 1) {
				gotoXY(startMenuX + 60, startMenuY + 2);
				line = 0;
			}

			printf("\b \b");
			continue;
		}

		//Nhập tối đa 128 bits.
		if (countBit >= 128) continue;

		//Kết thúc 1 cụm 4 thì thêm dấu cách.
		if ( ((countBit) % 4) == 0 && countBit != 0) {
			cout << " ";
			bits.push_back(' ');
			countCh++;
		}

		//Xuống dòng khi chạm biên.
		//Xuống dòng 1.
		if (countCh == 50) {
			gotoXY(startMenuX + 1, startMenuY + 2 + 1);
			line = 1;
		}
		//Xuống dòng 2.
		if (countCh == 110) {
			gotoXY(startMenuX + 1, startMenuY + 2 + 2);
			line = 2;
		}

		//Chỉ nhận 2 kí tự 1 và 0.
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
		//Đẩy vào chuỗi.
		bits.push_back(c);
		countCh++;

		
	}
	//bits.resize(count);
	for (int i = 0; i < bits.length(); i++)
	{
		if (bits[i] == ' ')
		{
			bits.erase(bits.begin() + i);
		}
	}
	return bits;
}

//In ra bảng số đã được chuyển đổi, choice là lựa chọn hệ input, s là chuỗi số cần đổi.
void printQIntConvertResult(int choice, string s)
{
	QInt q;
	switch (choice)
	{
	case 1:
		//170141183460469231731687303715884105727
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
		if (s.size() > 32)
		{
			gotoXY(startMenuX + 2, startMenuY + 5);
			cout << "3. HEX: ";
			cout << "The size of this hexa number is over 128.            ";
			break;
		}
		q.scanQInt(16, s);

		gotoXY(startMenuX + 2, startMenuY + 1);
		cout << "1. DEC: ";
		q.printQInt(10);

		gotoXY(startMenuX + 2, startMenuY + 2);
		cout << "2. BIN: ";
		q.printQInt(2);
		break;
	}

}

//In ra bảng số đã được chuyển đổi, choice là lựa chọn hệ input, s là chuỗi số cần đổi.
void printQFloatConvertResult(int choice, string s)
{
	QFloat q;
	switch (choice)
	{
	case 1:
	{
		ScanQFloat(q, s);

		bool* bit = new bool[128];
		bit = FDecToBin(q);

		/*
		for (int i = 0; i < 128; i++)
		{
			if (i == 1 || i == 16)
				cout << " ";
			cout << bit[i];
		}
		_getch();
		*/
		gotoXY(startMenuX + 2, startMenuY + 2);
		cout << "2. BIN: ";
		printQfloat(q, 2);
		break;
	}
	case 2:
		ScanBinQFloat(q, s);

		gotoXY(startMenuX + 2, startMenuY + 1);
		cout << "1. DEC: ";
		printQfloat(q, 10);

		break;
	}

}

//In menu lựa chọn hệ cần chuyển đổi.
void printConvertFrame(string& s, int& choice, int mode)
{
	printFrame();
	gotoXY(startMenuX + 2, startMenuY);
	cout << "Chosse your input state: " << endl;
	gotoXY(startMenuX + 2, startMenuY + 1);
	cout << "1. DEC: " << endl;
	gotoXY(startMenuX + 2, startMenuY + 2);
	cout << "2. BIN: " << endl;
	//Chỉ QInt mới convert thành dạng HEX
	if (mode == 1) {
		gotoXY(startMenuX + 2, startMenuY + 5);
		cout << "3. HEX: " << endl;
	}
	gotoXY(startMenuX + 2, startMenuY + 7);

	cout << "Your Choice [ ]" << endl;
	gotoXY(startMenuX + 2 + 13, startMenuY + 7);

	cin >> choice;

	//Khi chọn 1 hệ nào đó, con trỏ sẽ nhảy lên dòng của hệ đó.
	switch (choice)
	{
	case 1:
		gotoXY(startMenuX + 2 + 8, startMenuY + 1);
		cin >> s;
		
		break;
	case 2:
		gotoXY(startMenuX + 2 + 8, startMenuY + 2);
		if (mode == 1)
			s = overLoadInput();
		else
			cin >> s;

		break;
	case 3:
		if (mode != 1)
			break;
		gotoXY(startMenuX + 2 + 8, startMenuY + 5);
		cin >> s;
		break;
	}
}

void printResultCovertFrame()
{
	printFrame();

	gotoXY(startMenuX + 2, startMenuY + 1);
	cout << "1. DEC: " << endl;
	gotoXY(startMenuX + 2, startMenuY + 2);
	cout << "2. BIN: " << endl;
	gotoXY(startMenuX + 2, startMenuY + 5);
	cout << "3. HEX: " << endl;
	printNotif();
}


void  printQIntinFrame(QInt q)
{
	bool* bit = DecToBin(q);
	gotoXY(startMenuX + 2 + 8, startMenuY + 1);
	q.printQInt(10);
	gotoXY(startMenuX + 2 + 8, startMenuY + 2);
	q.printQInt(2);
	gotoXY(startMenuX + 2 + 8, startMenuY + 5);
	q.printQInt(16);
}
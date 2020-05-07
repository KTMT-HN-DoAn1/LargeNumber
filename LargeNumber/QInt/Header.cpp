﻿#include "Header.h"

void CutString(string s, string& a, string& b,string& c)
{
	char e[5] = " ";
	char* p = NULL;
	int n = s.length();
	char* arr = new char[n + 1];

	strcpy(arr, s.c_str());
	p = strtok(arr, e);
	if (p == NULL) return;
	string temp(p);
	a = temp;
	for (int i = 0; i <= 1; i++)
	{
		p = strtok(NULL, e);
		switch (i)
		{
			case 0:
			{
				string temp1(p);
				c = temp1;
			}break;
			case 1:
			{
				string temp1(p);
				b = temp1;
			}break;
		}
	}

}

Arithmetic Type(string s)
{
	if (s == "+") return ADD;
	if (s == "-") return SUB;
	if (s == "*") return MULT;
	if (s == "/") return DIV;
	if (s == "<<") return SL;
	if (s == ">>") return SR;
	if (s == "<") return LESS;
	if (s == ">") return GREATER;
	if (s == "==") return EQUAL;
	if (s == ">=") return GROE;
	if (s == "<=") return LOE;
	if (s == "ROR") return ROR;
	if (s == "ROL") return ROL;
	if (s == "&") return AND;
	if (s == "|") return OR;
	if (s == "^") return XOR;
	if (s == "~") return NOT;
}

QInt calcuQInt(int& type, string a, string b, string c)
{
	QInt x, y;
	switch (type)
	{
	case 2://nếu là hệ 2
		//hàm thực hiện tính toán với hệ và các toán hạng, số hạng được truyền vào
		//chuyển a và b thành 2 dãy bit trong QInt
		x.scanQInt(2, a);
		y.scanQInt(2, b);
		break;
	case 10://nếu là hệ 10
		x.scanQInt(10, a);
		y.scanQInt(10, b);
		break;
	case 16://nế là hệ 16
		x.scanQInt(16, a);
		y.scanQInt(16, b);
		break;
	default:
		break;
	}
	if (c != "<" || c != ">" || c != "==" || c != ">=" || c != "<=")
	{
		type = -1;
	}//để đánh dáu nếu gặp toán tử logic

	Arithmetic k = Type(c);
	QInt res(0);
	switch (k)
	{
	case ADD:
		res = x + y;
		break;
	case SUB:
		res = x - y;
		break;
	case MULT:
		res = x * y;
		break;
	case DIV:
		res = x / y;
		break;
	case AND:
		res = x & y;
		break;
	case OR:
		res = x | y;
		break;
	case XOR:
		res = x ^ y;
		break;
	case NOT:
		res = ~x;
		break;
	case SL:
	{
		int shift_num = QIntToDec(y);
		res = x << shift_num;
	}break;
	case SR:
	{
		int shift_num = QIntToDec(y);
		res = x >> shift_num;
	}break;
	case ROL:
	{
		int shift_num = QIntToDec(y);
		res = x.RoL(shift_num);
	}break;
	case ROR:
	{
		int shift_num = QIntToDec(y);
		res = x.RoR(shift_num);
	}break;
	case LESS:
		if (x < y)
		{
			QInt res_temp(1);
			return res_temp;
		}
		break;
	case GREATER:
		if (x > y)
		{
			QInt res_temp(1);
			return res_temp;
		}
		break;
	case EQUAL:
		if (x == y)
		{
			QInt res_temp(1);
			return res_temp;
		}
		break;
	case LOE:
		if (x <= y)
		{
			QInt res_temp(1);
			return res_temp;
		}
		break;
	case GROE:
		if (x >= y)
		{
			QInt res_temp(1);
			return res_temp;
		}
		break;
	default:
		break;
	}
	return res;
}



QInt runArithmetic(string s, int& type)
{
	string a, b, c;
	CutString(s, a, b, c);//cắt chuỗi thành các số hạng và toán hạng
	return calcuQInt(type, a, b, c);
}

void funRunQIntArithmetic()
{
	int type; string str;
	
	printResultCovertFrame();

	gotoXY(startMenuX + 2, startMenuY + 7);
	cout << "Your Input: [  ]" << endl;
	gotoXY(startMenuX + 2 + 13, startMenuY + 7);
	cin >> type;
	gotoXY(startMenuX + 2, startMenuY + 8);
	cout << "Expression: " << endl;
	gotoXY(startMenuX + 2 , startMenuY + 9);
	cin.ignore();
	getline(cin, str); //nhận vào chuỗi phép toán
	QInt res = runArithmetic(str, type);

	if (type == -1)
	{
		//in kết quả ra màn hình
		printQIntinFrame(res);
	}
	else
	{
		gotoXY(startFrameX + 30, startFrameY + 7);
		if (res.data[3])
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;
	}

}

void funRunQInt()
{
	QInt qint;
	do
	{
		int lenh1 = printModeFrame();
		switch (lenh1)
		{
		case 1://thực hiện các phép toán
		{
			funRunQIntArithmetic();
		}
		break;
		case 2://các thao tác với chuyển dổi số giữa các hệ
		{
			string s;
			cin >> s;
			qint.scanQInt(10, s);
			printResultCovertFrame();
			ConvertToAll(qint);
			
		}break;
		default:

			break;
		}
		if (lenh1 == 0) break;
		_getch();
	} while (true);
}




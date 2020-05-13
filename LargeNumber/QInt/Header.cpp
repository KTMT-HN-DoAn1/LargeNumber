#include "Header.h"

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
	int k = 1;
	if (a == "~") { k = 0; }
	for (int i = 0; i <= k; i++)
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
	if (s == "ROR" || s == "ror") return ROR;
	if (s == "ROL" || s == "rol") return ROL;
	if (s == "&") return AND;
	if (s == "|") return OR;
	if (s == "^") return XOR;
	if (s == "~") return NOT;
}

QInt calcuQInt(int& type, string a, string b, string c)
{
	int temp = 1;
	QInt x, y;
	if (c == "<<" || c == ">>" || c == "ROL" || c == "ROR" || c == "rol" || c == "ror")
	{
		temp = 0;
	}//để đánh dáu nếu gặp toán tử dịch bit
	switch (type)
	{

	case 2://nếu là hệ 2
		//hàm thực hiện tính toán với hệ và các toán hạng, số hạng được truyền vào
		//chuyển a và b thành 2 dãy bit trong QInt
		if (a == "~")
			x.scanQInt(2, c);
		else
		{
			if (!temp) y.scanQInt(10, b);
			else
			{
				y.scanQInt(2, b);
			}
			x.scanQInt(2, a);
		}
		break;
	case 10: case 1://nếu là hệ 10
		if (a == "~") { x.scanQInt(10, c); break; }
		x.scanQInt(10, a);
		y.scanQInt(10, b);
		break;
	case 16: case 3://nế là hệ 16
		if (a == "~") { x.scanQInt(16, c); break; }
		x.scanQInt(16, a);
		if (!temp) y.scanQInt(10, b);
		else 	y.scanQInt(16, b);
		break;
	default:
		break;
	}
	if (c == "<" || c == ">" || c == "==" || c == ">=" || c == "<=")
	{
		type = -1;
	}//để đánh dáu nếu gặp toán tử logic
	Arithmetic k;
	if (a == "~")
		k = NOT;
	else
		k = Type(c);
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
		if (y.zero())
		{
			type = -3;
			return res;
		}
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
	if (type == -3)
	{
		gotoXY(startFrameX + 10, startFrameY + 7);
		cout << "MATH ERROR. The divisor must be different from zero." << endl;
		return;
	}

	if (type == -1)
	{
		gotoXY(startFrameX + 30, startFrameY + 7);
		if (res.data[3])
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;		
	}
	else
	{
		//in kết quả ra màn hình
		printQIntinFrame(res);
	}

}

void funRunQIntConvert()
{
	string s; int choice;
	//Lấy chuỗi đầu vào trên Frame tuong ứng với vị trí của hệ đã được in sẵn
	printConvertFrame(s, choice, 1);
	//in kết quả
	printQIntConvertResult(choice, s);
	//in thông báo cuỗi Frame
	printNotif();
}

void funRunQInt()
{
	QInt qint;
	do
	{
		system("cls");
		printFrame();
		int lenh1 = printModeFrame();
		switch (lenh1)
		{
		case 1://thực hiện các phép toán
		{
			do
			{
				funRunQIntArithmetic();
				int key = _getch();
				if (key != 13) break;
			} while (true);
		}
		break;
		case 2://các thao tác với chuyển dổi số giữa các hệ
		{

			funRunQIntConvert();

			
		}break;
		default:

			break;
		}
		if (lenh1 == 0) break;
		_getch();
	} while (true);
}

void funRunQFloat()
{
	string s; int choice;
	//Lấy chuỗi đầu vào trên Frame tuong ứng với vị trí của hệ đã được in sẵn
	printConvertFrame(s, choice, 2);
	//in kết quả
	printQFloatConvertResult(choice, s);
	//in thông báo cuối Frame
	printNotif();
	_getch();
}

void QIntFileProcessing(fstream& f, fstream& g)
{
	int i = 0;
	while (!f.eof())
	{
		cout << i++ << endl;
		char c;
		string s1, s2, s3, s4;
		f >> s1 >> s2 >> s3;
		f.get(c);
		cout << "fff";
		if (c != '\n') f >> s4;
		if (s4 == "" && s2 != "~")
			//1 dòng có 3 phần tử --> Convertion
		{
			g << convertRun(s1, s2, s3) << endl;
		}
		else
			//Arithmetic
		{
			int type = atoi(s1.c_str());
			if (s2 == "~") s4 = "0";
			QInt res = calcuQInt(type, s2, s4, s3);
			if (type != -1)
			{
				bool* bit = DecToBin(res);
				//in kết quả ra file đích
				if (s1 == "10")
				{
					g << BinToDecStr(bit) << endl;
					delete[]bit;
				}
				else
				{
					if (s1 == "2")
					{
						g << BoolToString(bit) << endl;
					}
					else
					{
						g << DecToHex(res) << endl;
					}
				}
			}
			else
			{
				if (res.data[3])
					g << "TRUE" << endl;
				else
					g << "FALSE" << endl;
			}
		}
	}
	f.close();
	g.close();
}

void QFloatFileProcessing(fstream& f, fstream& g)
{
	while (!f.eof())
	{
		string a, b, c;
		f >> a >> b >> c;
		QFloat res;
		if (a == "2" && b == "10")
		{
			bool* bit = BinStrToBin(c);
			res = FBinToDec(bit);
			printQFloatToFile(g, res, 10);
		}
		else if (a == "10" && b == "2")
		{
			ScanQFloat(res, c);
			printQFloatToFile(g, res, 2);
		}
	}
	f.close();
	g.close();
}






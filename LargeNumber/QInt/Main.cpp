#include "Convert.h"
#include"Menu.h"
#include<conio.h>
#include"Header.h"

int main(int argc, char* argv[])
{
	fstream f,g;
	f.open("QInt_input.txt");
	g.open("QInt_output.txt");
	while (!f.eof())
	//khi không thực hiện bằng Command Prompt

	if (argc == 1)
	{
		char c;
		string s1, s2, s3, s4;
		f >> s1 >> s2 >> s3;
		f.get(c);
		if (c != '\n') f >> s4;
		if (s4 == "" || s2 != "~")
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
			if (type == -1)
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
	//khi không thực hiện bằng Command Prompt
	//if (argc == 1)
	//{
	//	do
	//	{
	//		printFrame();
	//		int lenh = printMainMenu();
	//		switch (lenh)
	//		{
	//		case 1://thực hiện các chức năng với QInt
	//		{
	//			funRunQInt();
	//		}break;
	//		case 2://Hàm thực hiện các chức năng với QFloat
	//			
	//			break;
	//		case 0:
	//			lenh = 0;
	//			break;
	//		default:
	//			gotoXY(startFrameX + 10, startMenuY + 7);
	//			cout << "You entered the wrong code. Please try again.";
	//			_getch();
	//			break;
	//		}
	//		if (lenh == 0) break;
	//	} while (true);
	//	
	//}
	//else
	//{
	//	
	//}
	gotoXY(startFrameX, startMenuY + heightMenu + 5);
	
	return 0;

}
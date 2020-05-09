#include "Convert.h"
#include"Menu.h"
#include<conio.h>
#include"Header.h"

#include "QFloat.h"



int main(int argc, char* argv[])
{
	/*
	//khi không thực hiện bằng Command Prompt
	if (argc == 1)
	{
		do
		{
			printFrame();
			int lenh = printMainMenu();
			switch (lenh)
			{
			case 1://thực hiện các chức năng với QInt
			{
				funRunQInt();
			}break;
			case 2://Hàm thực hiện các chức năng với QFloat

				break;
			case 0:
				lenh = 0;
				break;
			default:
				gotoXY(startFrameX + 10, startMenuY + 7);
				cout << "You entered the wrong code. Please try again.";
				_getch();
				break;
			}
			if (lenh == 0) break;
		} while (true);

	}
	//khi thực hiện bằng Command Prompt
	else
	{
		//Kiểm tra file đầu vào là QInt_test hay là QFloat_test

		{
			fstream f, g;
			f.open("QInt_input.txt");//f.open(argv[1]);
			g.open("QInt_output.txt");//g.open("argv[2]);
			QIntFileProcessing(f, g);
		}

	}

	gotoXY(startFrameX, startMenuY + heightMenu + 5);
	*/

	/*QInt q;
	q.scanQInt(10, "1000");
	q.printQInt(16);*/

	QFloat qf;
	while (true)
	{


		ScanQFloat(qf, cin);
		bool* bit = new bool[128];
		bit = FDecToBin(qf);

		for (int i = 0; i < 128; i++)
		{
			if (i == 1 || i == 16)
				cout << " ";
			cout << bit[i];
		}


		system("pause");
	}
}

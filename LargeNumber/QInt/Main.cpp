#include "Convert.h"
#include"Menu.h"
#include<conio.h>
#include"Header.h"

#include "QFloat.h"



int main(int argc, char* argv[])
{
	//khi không thực hiện bằng Command Prompt
	if (argc == 1)
	{
		do
		{
			system("cls");
			printFrame();
			int lenh = printMainMenu();
			switch (lenh)
			{
			case 1://thực hiện các chức năng với QInt
			{
				funRunQInt();
			}break;
			case 2://Hàm thực hiện các chức năng với QFloat
				funRunQFloat();
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
		string temp1(argv[1]);
		
		//Kiểm tra file đầu vào là QInt_test hay là QFloat_test
		if (temp1=="1")
		{
			//cout << "Vao" << endl;
			fstream f, g;
			f.open("QInt_input.txt");//f.open(argv[1]);
			g.open("QInt_output.txt");//g.open("argv[2]);
			
			QIntFileProcessing(f, g);
			//cout << "Done" << endl;
		} 
		else if (temp1 == "2")
		{
			cout << "Qfolat vao" << endl;
			fstream f, g;
			f.open("QFloat_input.txt");//f.open(argv[1]);

			g.open("QFloat_output.txt", 'w');//g.open("argv[2]);
			QFloatFileProcessing(f, g);
		}
		
	}
	gotoXY(startFrameX, startMenuY + heightMenu + 5);
}

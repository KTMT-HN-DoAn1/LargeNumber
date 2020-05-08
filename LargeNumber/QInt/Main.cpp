#include "Convert.h"
#include "Menu.h"
#include "QFloat.h"


int main(int argc, char* argv[])
{
	//khi không thực hiện bằng Command Prompt
	/*
	if (argc == 1)
	{
		printFrame();
		int lenh = printMainMenu();

		switch (lenh)
		{
		case 1:
			printModeFrame();
			break;
		case 2:
			break;
		default:
			break;
		}
	}
	else
	{

	}
	return 0;
	/*
	cout << hexaAdd("ABCDEF234", "-ABCDEF234") << endl;

	QInt q;
	q.scanQInt(10, "1000");
	q.printQInt(16);
	*/
	while (1)
	{

		QFloat qf;
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
#include "Convert.h"
#include"Menu.h"


int main(int argc, char* argv[])
{
	//khi không thực hiện bằng Command Prompt
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
	cout << hexaAdd("ABCDEF234", "-ABCDEF234") << endl;
	system("pause");
}
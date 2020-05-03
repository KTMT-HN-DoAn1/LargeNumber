#ifndef _MENU_H_
#define _MENU_H_

#include"QInt.h"
#include<Windows.h>

#define ColorCode_Back			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7

#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define default_ColorCode		7

//Hàm di chuyển đến điểm có tọa độ x,y treenmanf hình console
void gotoXY(int x, int y);

// hàm thay đổi màu sắc chữ
void Color(int colour);

//Main Menu
int printMainMenu();

//Khung màn làm việc chuyển đổi giữa các hệ
void printConvertFrame();


#endif // !_MENU_H_



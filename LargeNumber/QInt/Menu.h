#ifndef _MENU_H_
#define _MENU_H_
#include<conio.h>
#include"QInt.h"
#include"Convert.h"
#include"QFloat.h"
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

#define startFrameX 30
#define startFrameY 8
#define startMenuX 30
#define startMenuY 11
#define heightMenu 10

//Hàm di chuyển đến điểm có tọa độ x,y treenmanf hình console
void gotoXY(int x, int y);

// hàm thay đổi màu sắc chữ
void Color(int colour);

//In thông báo
void printNotif();

//Frame
void printFrame();

//Main Menu
int printMainMenu();

//Khung làm việc chọn chế độ
int printModeFrame();

//Khung màn làm việc chuyển đổi giữa các hệ
void printConvertFrame(string& s, int& choice, int mode);

//Khung in kết quả
void printResultCovertFrame();

string overLoadInput();

void printQIntConvertResult(int choice, string s);

void printQFloatConvertResult(int choice, string s);

//Hàm in số QInt kết quả ra Frame trên console
void printQIntinFrame(QInt q);


#endif // !_MENU_H_



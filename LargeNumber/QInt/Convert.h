﻿#pragma once
#include "QInt.h"

//-----------------------------------------------------------------CÁC HÀM CHUYỂN ĐỔI CẦN DÙNG--------------------------------------------------//

bool* DecToBin(QInt x);
QInt BinToDec(bool* bit);

//Hàm chuyển đổi chuỗi thập phân thành chuỗi thập lục phân (DEC -> HEX)
string DectoHex(string decStr);

//Hàm chuyển đổi từ chuỗi nhị phân sang chuỗi thập lục phân
string BintoHex(string strbin);//char* BinToHex(bool* bit)

//Hàm chuyển đổi chuỗi thập lục phân thành chuỗi nhị phân (Hex -> Bin)
string HexToBin(string hexstr);

//Hàm chuyển QInt thập phân sang thập lục phân
string DecToHex(QInt x);

//-----------------------------------------------------------MỘT SỐ HÀM HỖ TRỢ------------------------------------------------------------------//

//Chuyển đơn vị 10 ->16
char DecHex(int a);

//Hàm tăng chuỗi thập phân lên một dơn vị
void increase(string& s);

//Hàm chuyển mảng bool bit sang chuỗi string bit tương ứng
string BoolToString(bool* bin);
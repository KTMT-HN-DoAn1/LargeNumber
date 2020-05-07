#ifndef _CONVERT_H_
#define _CONVERT_H_

#include "QInt.h"
#include"Menu.h"

enum TypeConvert
{
	Dec2Bin, Bin2Dec, Hex2Bin, Bin2Hex, Hex2Dec, Dec2Hex
};
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

//Hàm chuyển chuỗi số thập phân thành dãy nhị phân
bool* StrToBin(string decStr);
//Hàm chuyển dãy nhị phân thành chuỗi số thập phân
string BinToDecStr(bool* bit);

//Hàm chuyển từ chuỗi thập phân thành số thập phân
int QIntToDec(QInt q);

//-----------------------------------------------------------MỘT SỐ HÀM HỖ TRỢ------------------------------------------------------------------//

//Chuyển đơn vị 10 ->16
char DecHex(int a);

//Hàm tăng chuỗi thập phân lên một dơn vị
void increase(string& s);

//Hàm chuyển mảng bool bit sang chuỗi string bit tương ứng
string BoolToString(bool* bin);

//Hàm chuyển mảng string bit thành bool bit
bool* StringToBool(string bin);

//Hàm cộng 2 số thập lục phân
string hexaAdd(string hex1, string hex2);

//Xác định loại chuyển đổi giữa các hệ
TypeConvert identifyConvert(string s1, string s2);

//Hàm chyển đổi giữ các hệ trả về chuỗi ký tự kết quả của hệ tương ứng
string convertRun(string t1, string t2, string num);

//Hàm chuyển một số QInt sang tất cả các hệ và in ra màn hình theo định dạng
void ConvertToAll(QInt& x);

//Hàm xử lỹ chung cho các chức năng với QFloat


#endif // !_CONVERT_H_


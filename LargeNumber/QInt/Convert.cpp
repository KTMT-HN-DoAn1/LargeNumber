#include "Convert.h"


// chuyển từ thập phân sang nhị phân
bool* DecToBin(QInt x)
{
	bool* res = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		res[i] = 0;
	}
	for (int i = 0; i < 128; i++)
	{
		res[i] = (x.data[i / 32] >> (31 - i % 32) & 1);
	}
	return res;
}


// chuyển từ nhị phân sang thập phân
QInt BinToDec(bool* bit)
{
	QInt res;
	for (int i = 0; i < 128; i++)
	{
		if (bit[i] == 1)
		{
			res.data[i / 32] = res.data[i / 32] | (1 << (31 - i % 32));
		}
	}

	return res;
}



//Hàm chuyển đổi chuỗi thập phân thành chuỗi thập lục phân (DEC -> HEX)
string DectoHex(string decStr)
{
	string result, result_temp;
	int temp;

	//mỗi lần lập là một lần chia
	//Trường hợp chuỗi thập phân đang thể hiện là một số dương
	if (decStr[0] != '-')
	{
		while (decStr != "0")
		{
			temp = 0;
			for (int i = 0; i < decStr.size(); i++)
			{

				temp = temp * 10 + (decStr[i] - '0');
				//(decStr[i] - '0') chuyển ký tự thành số.
				if (i > 0 || temp >= 16)// để loại bỏ trường hợp ký tự đầu tiên và thức 2 ( số có một và hai chữ số nhỏ hơn 16)
				{
					result_temp.push_back(temp / 16 + '0');
				}
				temp = temp % 16;
			}
			//gán giá trị dư sau mỗi lần chia vào trong chuỗi kết quả
			result.push_back(DecHex(temp));//đồng thời chuyển đổi thành đơn vị cho phù hợp với Hex
			//chuyển các số dư sang hệ 16 để đưa vào chuỗi kết quả

			//gán lại kết quả vừa chia được lại cho decStr - chuỗi thập phân ban đầu để tieesnhanhf chia tiếp trong lần lập sau
			decStr.clear();
			decStr = result_temp;
			result_temp.clear();
		}

		//thêm vào cho đủ số lượng byte (nếu chưa đủ)
		while (result.size() < 32)
		{
			result.push_back('0');// do là số dương nên thêm vào '0'
		}
	}

	//Trường hợp chuỗi thập phân thể hiện là một số âm
	else
	{
		decStr.erase(decStr.begin());//loại bỏ dấu '-' và tiến hành thực hiện gần giống như số dương

		while (decStr != "1")
		{
			temp = 0;
			for (int i = 0; i < decStr.size(); i++)
			{
				temp = temp * 10 + (decStr[i] - '0');
				//(decStr[i] - '0') chuyển ký tự thành số.
				if (i > 0 || temp >= 16)// để loại bỏ trường hợp ký tự đầu tiên và thức 2 ( số có một và hai chữ số nhỏ hơn 16)
				{
					result_temp.push_back(temp / 16 + '0');
				}
				temp = temp % 16;
			}
			//đây là điểm khác biệt vói số dương
			//nếu không chia hết cho 16 thì thương và dư được tính như sau
			if (temp != 0)
			{
				increase(result_temp);//vẫn lấy thương của kết quả như ở dương chia 16 nhưng ở đây ta tăng lên 1 đơn vị
				temp = 16 - temp;// phần dư của -A%16 là 16 -(A%16)
			}
			//gán giá trị dư sau mỗi lần chia vào trong chuỗi kết quả
			result.push_back(DecHex(temp));//đồng thời chuyển đổi thành đơn vị cho phù hợp với Hex
			//chuyển các số dư sang hệ 16 để đưa vào chuỗi kết quả

			//gán lại kết quả vừa chia được lại cho decStr - chuỗi thập phân ban đầu để tieesnhanhf chia tiếp trong lần lập sau
			decStr.clear();
			decStr = result_temp;
			result_temp.clear();
		}

		//thêm vào cho đủ số lượng byte (nếu chưa đủ)
		while (result.size() < 32)
		{
			result.push_back('F');//do là số âm nên thêm vào F
		}
	}
	//cần đảo ngược lại chuỗi trước khi trả về chuỗi kết quả
	reverse(result.begin(), result.end());
	return result;
}

//Hàm chuyển đổi từ chuỗi nhị phân sang chuỗi thập lục phân
string BintoHex(string strbin)
{
	string hexstr;
	//thêm bit 0 vào đầu chuỗi cho đủ bit 
	while (strbin.size() % 4 != 0 && strbin.size() < 128)
	{
		strbin.insert(strbin.begin(), '0');
	}
	string temp;
	for (int i = 0; i < strbin.size(); i++)
	{
		//thêm từng bit vào trong một chuỗi tạm --> tạo block 4 bit
		temp.push_back(strbin[i]);
		//kiểm tra xem block đã đủ 4 bit chưa
		if ((i + 1) % 4 == 0)
		{
			if (temp == "0000") hexstr = hexstr + "0";//0
			else if (temp == "0001") hexstr = hexstr + "1";//1
			else if (temp == "0010") hexstr = hexstr + "2";//2
			else if (temp == "0011") hexstr = hexstr + "3";//3
			else if (temp == "0100") hexstr = hexstr + "4";//4
			else if (temp == "0101") hexstr = hexstr + "5";//5
			else if (temp == "0110") hexstr = hexstr + "6";//6
			else if (temp == "0111") hexstr = hexstr + "7";//7
			else if (temp == "1000") hexstr = hexstr + "8";//8
			else if (temp == "1001") hexstr = hexstr + "9";//9
			else if (temp == "1010") hexstr = hexstr + "A";//10
			else if (temp == "1011") hexstr = hexstr + "B";//11
			else if (temp == "1100") hexstr = hexstr + "C";//12
			else if (temp == "1101") hexstr = hexstr + "D";//13
			else if (temp == "1110") hexstr = hexstr + "E";//14
			else if (temp == "1111") hexstr = hexstr + "F";//15
			temp.clear();// làm rỗng chuỗi chưa block bit vừa xử lý xong để nạp block bit mới trong những lần lặp sau.
		}
	}
	return hexstr;//trả về chuỗi Hexa
}

//Hàm chuyển đổi chuỗi thập lục phân thành chuỗi nhị phân (Hex -> Bin)
string HexToBin(string hexstr)
{
	string binstr;
	if (hexstr.size() > 32)
	{
		cout << "The size of this hexa number is over 128." << endl;
		return "";
	}
	for (int i = 0; i < hexstr.size(); i++)
	{
		if (hexstr[i] == '0') binstr = binstr + "0000";//0
		else if (hexstr[i] == '1') binstr = binstr + "0001";//1
		else if (hexstr[i] == '2') binstr = binstr + "0010";//2
		else if (hexstr[i] == '3') binstr = binstr + "0011";//3
		else if (hexstr[i] == '4') binstr = binstr + "0100";//4
		else if (hexstr[i] == '5') binstr = binstr + "0101";//5
		else if (hexstr[i] == '6') binstr = binstr + "0110";//6
		else if (hexstr[i] == '7') binstr = binstr + "0111";//7
		else if (hexstr[i] == '8') binstr = binstr + "1000";//8
		else if (hexstr[i] == '9') binstr = binstr + "1001";//9
		else if (hexstr[i] == 'A') binstr = binstr + "1010";//10
		else if (hexstr[i] == 'B') binstr = binstr + "1011";//11
		else if (hexstr[i] == 'C') binstr = binstr + "1100";//12
		else if (hexstr[i] == 'D') binstr = binstr + "1101";//13
		else if (hexstr[i] == 'E') binstr = binstr + "1110";//14
		else if (hexstr[i] == 'F') binstr = binstr + "1111";//15
	}
	return binstr;
}

//Hàm chuyển QInt thập phân sang thập lục phân
string DecToHex(QInt x)
{
	//1. Chuyển QInt thành dãy bit nhị phân (dạnh mảng bool)
	//2. Chuyển dãy bit (mảng bool) thành chuỗi bit (string)
	//3. Chuyển dãy bit (string) thành  dãy Hex (string)
	return string(BintoHex(BoolToString(DecToBin(x))));
}

//Trả về chuỗi kết quả khi chia 1 chuỗi số thập phân cho 2
string strDivTwo(string s)
{
	int add, next_add = 0;
	for (int i = 0; i < s.length(); ++i) {
		int tmp = s[i] - '0';
		add = next_add;
		if (tmp % 2 == 0) {
			next_add = 0;
		}
		else {
			next_add = 5;
		}

		char res = '0' + (add + (tmp / 2));
		s[i] = res;
	}

	while (s[0] == '0' && s.length() > 1)
	{
		s.erase(0, 1);
	}

	return s;
}

//Tìm số bù 2 của 1 dãy 128bits
bool* twoComlement(bool* bit)
{
	//
	bit[0] = bit[0] ^ 1;

	int flag = -1;
	for (int i = 127; i > 0; --i) {
		if (bit[i]) {
			flag = i;
			break;
		}
	}

	for (int i = flag - 1; i > 0; --i) {
		bit[i] = bit[i] ^ 1;
	}

	return bit;
}

//Hàm chuyển chuỗi số thập phân thành dãy nhị phân.
bool* StrToBin(string decStr)
{
	// Mảng chứa 128bits.
	bool* bit = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		bit[i] = 0;
	}

	//Kiểm tra số âm.
	bool isNegative = false;
	if (decStr[0] == '-')
	{
		isNegative = true;
		decStr.erase(0, 1);
	}

	//Đưa chuỗi số về dạng tối giản (không dư số 0 đằng trước).
	while (decStr[0] == '0')
	{
		decStr.erase(0, 1);
	}

	//Thực hiện chuyển chuỗi số thập phân về dạng bit.
	//Chia 2 liên tục cho tới khi có được dãy bit.
	int count = 0;
	while (decStr[0] != '0')
	{
		//Kiểm tra chuỗi số hiện tại có chia hết cho 2 hay không?
		int tmp = decStr[decStr.length() - 1] - '0';
		//Nếu chia hết thì lưu 0, dư thì lưu 1.
		if (tmp % 2 != 0) {
			bit[127 - count] = 1;
		}

		//Tìm phần nguyên của dãy số khi chia cho 2.
		decStr = strDivTwo(decStr);
		count++;
	}

	//Nếu là số âm thì ta tìm bù 2 của dãy số hiện tại.
	if (isNegative) {
		bit = twoComlement(bit);
	}

	return bit;
}

//Hàm nhân chuỗi thập phân cho 2.
string strMultiTwo(string s)
{
	int add = 0;
	for (int i = s.length() - 1; i >= 0; --i) {
		int tmp = s[i] - '0';
		int calc = tmp * 2 + add;
		if (calc >= 10) {
			add = 1;
		}
		else {
			add = 0;
		}

		char res = '0' + (calc % 10);
		s[i] = res;

		if (add == 1 && i == 0) {
			s.insert(0, "1");
		}
	}

	return s;
}

//Hàm cộng chuỗi thập phân cho 1.
string strPlusOne(string s)
{
	int add = 1;

	for (int i = s.length() - 1; i >= 0; --i) {
		int tmp = s[i] - '0';
		int calc = tmp + add;
		if (calc >= 10) {
			add = 1;
		}
		else {
			add = 0;
		}

		char res = '0' + (calc % 10);
		s[i] = res;

		if (add == 0) {
			return s;
		}

		if (add == 1 && i == 0) {
			s.insert('1', 0);
		}
	}

	return s;
}


//Hàm chuyển dãy nhị phân thành chuỗi số thập phân.
string BinToStr(bool* bit)
{
	//Kiểm tra âm, nếu âm thì chuyển về dạng bù 2 (dương).
	bool isNegative = false;
	if (bit[0])
	{
		isNegative = true;
		bit = twoComlement(bit);
	}

	string s = "0";

	//Tìm vị trí bắt đầu của dãy bits (số 1 đầu tiên).
	int index = 0;
	for (int i = 0; i < 128; ++i)
	{
		if (bit[i]) {
			index = i;
			break;
		}
	}

	//Tìm số thập phân tương ứng với dãy bits.
	//Với mỗi bit trong dãy, ta nhân 2, nếu là 1 thì cộng thêm 1 (do khi chia dư ra).
	for (int i = index; i < 128; ++i)
	{
		s = strMultiTwo(s);
		if (bit[i]) {
			s = strPlusOne(s);
		}
	}

	//Nếu là số âm, thêm dấu '-' phía trước chuỗi.
	if (isNegative)
	{
		s.insert(s.begin(), '-');
	}

	return s;
}

//-----------------------CÁC HÀM HỖ TRỢ-------------------------------------------------//
//Chuyển đơn vị 10 ->16
char DecHex(int a)
{
	if (a < 10) return (a + '0');
	else
	{
		switch (a)
		{
		case 10: return 'A';
		case 11: return 'B';
		case 12: return 'C';
		case 13: return 'D';
		case 14: return 'E';
		case 15: return 'F';
		default:
			break;
		}
	}
}

//Hàm tăng chuỗi thập phân lên một dơn vị
void increase(string& s)
{
	int k = s.size() - 1;
	while (k >= 0)
	{
		switch (s[k])
		{
			//gặp các trường hợp này thì chỉ cần tăng rồi kết thúc
		case '0':case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8':
			s[k] += 1;
			return;
			//thì gán lại bằng không và tăng giá trị chữ số liền trước lên một
		case '9':
			s[k] = '0';
			k--;
			if (k < 0)//hết chuổi nhưng vẫn còn nhớ 1 thì chèn thêm vào phía đầu chuỗi '1'. 
			{
				s.insert(s.begin(), '1');
			}
			break;
		default:
			break;
		}
	}
}

//Hàm chuyển mảng bool bit sang chuỗi string bit tương ứng
string BoolToString(bool* bin)
{
	//mảng bool bit đã được chuẩn hóa từ trước ( có đủ 128 bits)
	string result;
	if (bin != NULL)
	{
		for (int i = 0; i < 128; i++)
		{
			result.push_back(bin[i] + '0');
		}
	}
	return result;
}

//Hàm chuyển mảng string bit thành bool bit
bool* StringToBool(string bin)
{
	bool* bin_res = new bool[128];
	while (bin.size()!=128)
	{
		bin.insert(bin.begin(), '0');
	}
	for (int i = 0; i < 128; i++)
	{
		bin_res[i] = bin[i] - '0';
	}
	return bin_res;
}

//Hàm cộng 2 số thập lục phân
string hexaAdd(string hex1, string hex2)
{
	bool sub = false;
	if (hex2[0] == '-')
	{
		sub = true;
		hex2.erase(0, 1);//bỏ dấu '-' ra khỏi chuỗi
	}
	//chuyển 2 số Hexa cần tính thành chuỗi nhị phân
	string binstr1 = HexToBin(hex1);
	string binstr2 = HexToBin(hex2);
	//biến chuỗi nhị phân thành mảng nhị phân
	bool* bin1 = StringToBool(binstr1);
	bool* bin2 = NULL;
	if (sub)//nếu là số âm thì chuyển về dạng bù 2
	{
		bin2 = StringToBool(binstr2);
		bin2 = twoComlement(bin2);
	}
	else
	{
		bin2 = StringToBool(binstr2);
	}
	//chuyển mảng nhị phân thành QInt
	QInt qint1,qint2,result;
	qint1 = BinToDec(bin1);
	qint2 = BinToDec(bin2);
	
	//tiến hành cộng 2 số
	result = qint1 + qint2;

	//chuyển Qint thàng mảng bool bit
	bool* resbin = DecToBin(result);

	//chuyển mảng bool bit thành string bit -->chuyển string bit thành string Hexa
	return BintoHex(BoolToString(resbin));
}

TypeConvert identifyConvert(string s1, string s2)
{
	if (s1 == "2")
	{
		if (s2 == "10") return Bin2Dec;
		if (s2 == "16") return Bin2Hex;
	}
	else
	{
		if (s1 == "10")
		{
			if (s2 == "2") return Dec2Bin;
			if (s2 == "16") return Dec2Hex;
		}
		else
		{
			if (s2 == "2") return Hex2Bin;
			if (s2 == "10") return Hex2Dec;
		}
	}
}

void convertRun(string t1, string t2, string num)
{
	TypeConvert type = identifyConvert(t1, t2);
	QInt res;
	switch (type)
	{
	case Dec2Bin:

		break;
	case Bin2Dec:
	{
		bool* bit = StringToBool(num);
		res = BinToDec(bit);
		
	}break;
	case Hex2Bin:
	{
		string bit = HexToBin(num);
		
	}break;
	case Bin2Hex:
		break;
	case Hex2Dec:
		break;
	case Dec2Hex:
		break;
	default:
		break;
	}
	res.printQInt();
}

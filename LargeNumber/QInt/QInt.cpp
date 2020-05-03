#include "QInt.h"

QInt::QInt()
{
	for (int i = 0; i < 4; i++)
		data[i] = 0;
}

QInt::QInt(const QInt& q)
{
	for (int i = 0; i < 4; i++)
		data[i] = q.data[i];
}


QInt::QInt(int q)
{
	for (int i = 0; i < 3; i++)
	{
		data[i] = 0;
	}
	data[3] = q;
}
QInt::~QInt()
{
}

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

string strPlusOne(string s)
{
	int add = 1;

	for (int i = s.length() - 1; i >= 0; --i) {
		int tmp = s[i] - '0';
		int calc = tmp + add;
		if (calc >= 10) {
			add = 1;
		}
		else{
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

string BinToDecStr(bool* bit)
{
	string s = "0";
	int index = 0;
	for (int i = 0; i < 128; ++i)
	{
		if (bit[i]) {
			index = i;
			break;
		}
	}
	for (int i = index; i < 128; ++i)
	{
		s = strMultiTwo(s);
		if (bit[i]) {
			s = strPlusOne(s);
		}
	}
	if (bit[0])
	{
		s.insert(s.begin(), '-');
	}

	return s;
}
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

void QInt::scanQInt()
{
	string s;
	cin >> s;

	// Mảng chứa 128bits
	bool* bit = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		bit[i] = 0;
	}

	bool isNegative = false;
	if (s[0] == '-')
	{
		isNegative = true;
		s.erase(0, 1);
	}

	//
	while (s[0] == '0')
	{
		s.erase(0, 1);
	}

	//
	int count = 0;
	while (s[0] != '0')
	{
		int tmp = s[s.length() - 1] - '0';

		if (tmp % 2 != 0) {
			bit[127 - count] = 1;
		}

		s = strDivTwo(s);
		count++;
	}

	if (isNegative) {
		bit = twoComlement(bit);
	}

	for (int i = 0; i < 128; i++)
	{
		if (bit[i] == 1)
		{
			this->data[i / 32] = this->data[i / 32] | (1 << (31 - i % 32));
		}
	}

	delete[]bit;
}

void QInt::printQInt()
{
	
	// Mảng chứa 128bits
	bool* bit = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		bit[i] = 0;
	}

	for (int i = 0; i < 128; i++)
	{
		bit[i] = (this->data[i / 32] >> (31 - i % 32) & 1);
	}

	bool isNegative = false;
	if (bit[0])
	{
		isNegative = true;
		bit = twoComlement(bit);
	}
	string s = BinToDecStr(bit);

	cout << s;
}

QInt QInt::operator&(const QInt& qint)
{
	QInt result;
	for (int i = 0; i < 4; i++)
	{
		result.data[i] = this->data[i] & qint.data[i];
	}
	return result;
}

QInt QInt::operator|(const QInt& qint)
{
	QInt result;
	for (int i = 0; i < 4; i++)
	{
		result.data[i] = this->data[i] | qint.data[i];
	}
	return result;
}

QInt QInt::operator^(const QInt& qint)
{
	QInt result;
	for (int i = 0; i < 4; i++)
	{
		result.data[i] = this->data[i] ^ qint.data[i];
	}
	return result;
}

QInt& QInt::operator~()
{
	for (int i = 0; i < 4; i++)
	{
		this->data[i] = ~this->data[i];
	}
	return *this;
}
QInt QInt::operator>>(const int& number)
{
	QInt result,temp;
	int num = 0;
	if (number >= 128) return result;
	if (number < 32)
	{
		//Dịch phải phần tử đầu tiên của mảng data.
		//(number >= 32) ? (result.data[0] = 0) : (result.data[0] = (this->data[0] >> number));
		result.data[0] = this->data[0] >> number;
		for (int i = 1; i < 4; i++)
		{
			//(number >= 32) ? (result.data[i] = 0) : (result.data[i] = this->data[i] >> number);
			result.data[i] = this->data[i] >> number;

			for (int j = 0; j < number; j++)
			{
				result.data[i] = result.data[i] | (((1 << j) & this->data[i - 1]) << (32 - number + j));
			}
		}
	}
	else if (number < 64)
	{

		for (int i = 1; i < 4; i++)
		{
			temp.data[i] = this->data[i - 1];
		}
		num = number % 32;
		for (int i = 2; i < 4; i++)
		{
			result.data[i] = temp.data[i] >> num;

			for (int j = 0; j < num; j++)
			{
				result.data[i] = result.data[i] | (((1 << j) & temp.data[i - 1]) << (32 - num + j));
			}
		}
	}
	else if (number < 96)
	{

		for (int i = 3; i < 4; i++)
		{
			temp.data[i] = this->data[i - 2];
		}
		num = number % 32;
		for (int i = 1; i < 4; i++)
		{
			result.data[i] = temp.data[i] >> num;

			for (int j = 0; j < num; j++)
			{
				result.data[i] = result.data[i] | (((1 << j) & temp.data[i - 1]) << (32 - num + j));
			}
		}
	}
	else if (number < 128)
	{
		for (int i = 0; i < 3; i++)
		{
			result.data[i] = 0;
		}
		result.data[3] = this->data[0];
		result.data[3] >>= number % 32;

	}
	return result;
}

QInt QInt::operator<<(const int& number)
{
	QInt result;
	//Dịch trái phần tử cuối của mảng data.
	result.data[3] = this->data[3] << number;
	for (int i = 2; i >= 0; i--)
	{

		for (int j = 0; j < number; j++)
		{
			result.data[i + 1] = result.data[i + 1] | (((1 << (32 - j - 1)) & this->data[i]) >> (32 - number));
		}
		//Dịch trái các phần tử còn lại.
		result.data[i] = this->data[i] << number;
	}
	return result;

}


QInt& QInt::RoL(int n)
{
	for (int i = 0; i < n; i++)
	{
		//Lấy bit đầu ra
		int temp = (1 << (32 - 1)) & this->data[0];
		//Dịch trái 1 bit
		*this = *this << 1;
		//Lấy bit temp gán vào bit cuối cùng
		this->data[3] = this->data[3] | (temp >> (32 - 1));
	}
	return *this;
}

QInt& QInt::RoR(int n)
{
	for (int i = 0; i < n; i++)
	{
		//Lấy bit cuối ra
		int temp = 1 & this->data[3];
		//Dịch phải 1 bit
		*this = *this >> 1;
		//Lấy bit temp gán vào bit đầu tiên
		this->data[0] = this->data[0] | (temp << (32 - 1));
	}
	return *this;
}

QInt QInt::operator+(QInt& q)
{
	QInt res;
	int nho = 0;
	int bitRes = 0,temp1,temp2;
	for (int i = 0; i < 128; i++)
	{
		if (i == 32)
		{
			i = 32;
		}
 		temp1 = (*this >> i).data[3] & 1;
		temp2 = (q >> i).data[3] & 1;
		bitRes = temp1 + temp2 + nho;
		
		if (bitRes == 1)
		{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
			res.data[(127 - i) / 32] = res.data[(127 - i) / 32] | (1 << (i % 32));
			nho = 0;
		}
		else if (bitRes == 2)
		{
			nho = 1;
		}
		else if (bitRes == 3)
		{
			res.data[(127 - i) / 32] = res.data[(127 - i) / 32] | (1 << (i % 32));
			nho = 1;
		}
	}
	return res;
}

QInt QInt::operator-(QInt& q)
{
	QInttoTwoComplement(q);
	return(*this + q);
}

QInt QInt::operator*(QInt& q)
{
	bool negative = false;
	if ((this->negative() && !q.negative()) || (!this->negative() && q.negative()))
	{
		negative = true;
	}
	if (this->negative())
	{
		QInttoTwoComplement(*this);
	}
	if (q.negative())
	{
		QInttoTwoComplement(q);
	}
	QInt result;
	QInt p(1);
	while (!q.zero())
	{
		if (((q & p) - p).zero()) result = result + *this;
		*this = *this << 1;
		q = q >> 1;
	}
	if (negative)
	{
		QInttoTwoComplement(result);
	}
	return result;
}

QInt QInt::operator/(QInt& q)
{
	QInt temp;
	QInt p(1);
	if (this->zero() || q.zero())return temp;
	int k = 128;
	bool negative = false;
	if ((this->negative() && !q.negative()) || (!this->negative() && q.negative()))
	{
		negative = true;
	}
	if (this->negative())
	{
		QInttoTwoComplement(*this);
	}
	if (q.negative())
	{
		QInttoTwoComplement(q);
	}
	QInt result;
	while (k != 0)
	{
		temp = temp | ((*this >> k)& p);
		if (temp >= q)
		{
			result = result + p;
			temp = temp - q;
		}
		else result = result << 1;
		temp = temp << 1;
		k--;
	}
	if (negative)
	{
		result = ~result + p;
	}
	return result;
}

bool QInt::operator>(QInt& q)
{
	if ((this->negative()) && (!q.negative()))
	{
		return false;
	}
	if ((!this->negative()) && (q.negative()))
	{
		return true;
	}
	if ((this->negative()) && (q.negative()))
	{
		QInttoTwoComplement(*this);
		QInttoTwoComplement(q);
		for (int i = 127; i >= 0; i--)
		{
			if (((*this >> i).data[3] & 1) < (q >> i).data[3] & 1)return true;
		}
		return false;
	}
	for (int i = 127; i >= 0; i--)
	{
		if (((*this >> i).data[3] & 1) > (q >> i).data[3] & 1)return true;
	}
	return false;
}

bool QInt::operator<(QInt& q)
{
	if ((this->negative()) && (!q.negative()))
	{
		return true;
	}
	if ((!this->negative()) && (q.negative()))
	{
		return false;
	}
	if ((this->negative()) && (q.negative()))
	{
		QInttoTwoComplement(*this);
		QInttoTwoComplement(q);
		for (int i = 127; i >= 0; i--)
		{
			if (((*this >> i).data[3] & 1) > (q >> i).data[3] & 1)return true;
		}
		return false;
	}
	for (int i = 127; i >= 0; i--)
	{
		if (((*this >> i).data[3] & 1) < (q >> i).data[3] & 1)return true;
	}
	return false;
}

bool QInt::operator==(QInt& q)
{
	if ((*this > q) || (*this < q))return false;
	return true;
}

bool QInt::operator<=(QInt& q)
{
	if ((*this < q) || (*this == q))return true;
	return false;
}

bool QInt::operator>=(QInt& q)
{
	if ((*this > q) || (*this == q))return true;
	return false;
}

QInt QInt::operator=(const QInt& q)
{
	if (this != &q)
	{
		for (int i = 0; i < 4; i++)
		{
			this->data[i] = q.data[i];
		}
	}
	return *this;
}


bool QInt::negative()
{
	if ((*this >> 127).data[3] == 1)
		return true;
	return false;
}

bool QInt::zero()
{
	for (int i = 0; i < 4; i++)
	{
		if (this->data[i] != 0)return false;
	}
	return true;
}

QInt QInttoTwoComplement(QInt&x)
{
	QInt q(1);
	x = ~x + q;
	return (x);
}

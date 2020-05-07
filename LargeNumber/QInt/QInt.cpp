#include "QInt.h"
#include "Convert.h"
#include "Menu.h"

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

//Đọc số QInt dưới dạng chuỗi, với hệ choice (2, 10, 16).
void QInt::scanQInt(int choice, string s)
{
	bool* bit = NULL;
	switch (choice)
	{
	//Biển chuỗi nhị phân thành mảng nhị phân (chuẩn hóa), sau đó chuyển thành QInt.
	case 2:
		bit = BinStrToBin(s);
		*this = BinToDec(bit);

		delete[]bit;
		break;

	// Chuyển chuỗi thập phân thành mảng nhị phân, sau đó chuyển thành QInt.
	case 10:
		bit = StrToBin(s);
		*this = BinToDec(bit);

		delete[]bit;

		break;

	//Chuẩn hóa chuỗi hex nhập vào, chuyển thành nhị phân, sau đó thành QInt.
	case 16:
		s = preparationHexStr(s);
		string binStr = HexToBin(s);
		bit = BinStrToBin(binStr);
		*this = BinToDec(bit);
		delete[]bit;
		break;
	}
	
}

//Hàm in số QInt với hệ outChoice (2, 10, 16).
void QInt::printQInt(int outChoice)
{
	//init mảng nhị phân.
	bool* bit = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		bit[i] = 0;
	}

	switch (outChoice)
	{
	//Chuyển QInt thành mảng nhị phân và in dưới dạng cụm 4 bits.
	case 2:
		bit = DecToBin(*this);
		for (int i = 0; i < 128; ++i)
		{
			//Mỗi 4 bits là 1 cụm.
			if ((i + 1) % 4 == 1 && i != 0)
			{
				cout << " ";
			}

			//Xuống dòng.
			if (i == 40)
				gotoXY(startMenuX + 1, startMenuY + 2 + 1);
			if (i == 88)
				gotoXY(startMenuX + 1, startMenuY + 2 + 2);

			if (bit[i])
				cout << "1";
			else
				cout << "0";
		}

		break;

	//Chuyển QInt thành mảng nhị phân và từ đó chuyển sang chuỗi thập phân.
	case 10:
		bit = DecToBin(*this);

		cout << BinToStr(bit);

		break;

	//Chuyển thành chuỗi thập lục phân và in ra.
	case 16:
		string res = DecToHex(*this);
		cout << res;
		break;
	}

	delete[]bit;
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

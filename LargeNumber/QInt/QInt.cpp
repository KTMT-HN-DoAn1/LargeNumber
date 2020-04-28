#include "QInt.h"

QInt::QInt()
{
	for (int i = 0; i < 4; i++)
		data[i] = 0;
}

QInt::QInt(QInt& q)
{
	for (int i = 0; i < 4; i++)
		data[i] = q.data[i];
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
	string s = "0";

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

	//
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

	if (isNegative)
		cout << '-';
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

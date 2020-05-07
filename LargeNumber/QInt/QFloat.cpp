#include "QFloat.h"


QFloat::QFloat()
{
	for (int i = 0; i < 4; i++)
	{
		data[i] = 0;
	}
}


QFloat::~QFloat()
{
}

QFloat QFloat::BinToDec(bool* bit)
{
	QFloat res;
	for (int i = 0; i < 128; i++)
	{
		if (bit[i] == 1)
		{
			res.data[i / 32] = res.data[i / 32] | (1 << (31 - i % 32));
		}
	}
	return res;
}

bool* QFloat::DecToBin(QFloat x)
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

void QFloat::ABC(bool* bit, int a)
{
	for (int i = 1; i < 16; i++)
	{
		bit[16 - i] = (a >> (i - 1)) & 1;
	}
}

int countPoint(string s)
{
	int n = s.length();
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '.')
			count++;
	}
	if (count <= 1)
		return 1;
	return 0;
}

int checkNumber(string s)
{
	int n = s.length();
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (((s[i] >= 48) && (s[i] <= 57)) | (s[i] == '.'))
			count++;
	}
	if (count == n)
		return 1;
	return 0;
}

int checkInputQFloat(string s)
{
	if ((checkNumber(s) == 1) && (countPoint(s) == 1))
		return 1;
	return 0;
}
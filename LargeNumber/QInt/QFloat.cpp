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

QFloat FBinToDec(bool* bit)
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

bool* FDecToBin(QFloat x)
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

void plusOneBit(bool* bit)
{
	int nho = 1;
	int tem;
	for (int i = 127; i > 15; i--)
	{
		tem = bit[i] + nho;
		if (tem == 1)
		{
			bit[i] = 1;
			nho = 0;
			return;
		}
		else if (tem == 2)
		{
			bit[i] = 0;
			nho = 1;
		}
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



void ScanQFloat(QFloat& q, istream& in)
{
	string s;
	in >> s;


	bool isNegative = false;
	if (s[0] == '-')
	{
		isNegative = true;
		s.erase(0, 1);
	}


	//tach thanh phan nguyen va phan thap phan
	string strNguyen = "";
	string strTPhan = "";
	int pos = s.find('.');
	if (pos < 0)
	{
		strNguyen = s;
	}
	else
	{
		strNguyen = s.substr(0, pos);
		strTPhan = s.substr(pos + 1);
	}


	//bo so 0 thua
	while (strNguyen.length() > 0 && strNguyen[0] == '0')
	{
		strNguyen.erase(0, 1);
	}

	while (strTPhan.length() > 0 && strTPhan[strTPhan.length() - 1] == '0')
	{
		strTPhan.erase(strTPhan.length() - 1, 1);
	}

	//chuoi toan so 0
	if (strNguyen == "" && strTPhan == "")
	{
		//q = "0";
		return;
	}



	int exponent = -1;

	// Mảng chứa 128bits
	bool* bit = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		bit[i] = 0;
	}

	//chuyen phan nguyen thanh nhi phan

	int count = 0;

	while (strNguyen.length() > 0 && strNguyen[0] != '0')
	{
		if (count > 127) break;
		int tmp = strNguyen[strNguyen.length() - 1] - '0';

		if (tmp % 2 != 0) {
			bit[127 - count] = 1;
		}

		strNguyen = strDivTwo(strNguyen);
		count++;
	}

	//so mu bang so chu so phan nguyen - 1
	if (count > 0)
		exponent = count - 1;

	//doi ve dau day bit
	int k = 16; //vi tri bit dau tien phan fraction

	for (int i = 128 - count; i < 128; i++)
	{
		swap(bit[k++], bit[i]);
		if (k > 127)
			break;
	}


	//chuyen phan thap phan thanh nhi phan
	bool ignore = !bool(count);
	strTPhan.insert(0, "0");
	while (strTPhan.length() > 1)
	{
		strTPhan = strMultiTwo(strTPhan);
		if (k > 127)
		{
			plusOneBit(bit);
			break;
		}
		if (strTPhan[0] == '1')
		{
			strTPhan[0] = '0';
			if (ignore)
			{
				count++;
				ignore = false;
				continue;
			}
			bit[k++] = 1;
		}
		else
		{
			if (ignore)
			{
				count++;
			}
			else
			{
				bit[k++] = 0;
			}
		}
		while (strTPhan.length() > 0 && strTPhan[strTPhan.length() - 1] == '0')
		{
			strTPhan.erase(strTPhan.length() - 1, 1);
		}
	}

	//so mu truong hop dich phai
	if (exponent < 0)
	{
		exponent = -count;
	}

	//so mu qua 2^14-1
	exponent += 16383;
	for (int i = 1; i < 16; i++)
	{
		bit[16 - i] = (exponent >> (i - 1)) & 1;
	}


	if (isNegative) {
		bit[0] = 1;
	}

	//ghi bit[] vao QFloat
	for (int i = 0; i < 4; i++)
	{
		q.data[i] = 0;
	}

	for (int i = 0; i < 128; i++)
	{
		if (bit[i] == 1)
		{
			q.data[i / 32] = q.data[i / 32] | (1 << (31 - i % 32));
		}
	}

	delete[]bit;
}

void ScanBinQFloat(QFloat& x, istream& in)
{
	string s;
	in >> s;

	if (s[0] == '.')
	{
		s.insert(0, "0");
	}

	for (int i = 0; i < 4; i++)
	{
		x.data[i] = 0;
	}

	// Mảng chứa 128bits
	bool* bit = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		bit[i] = 0;
	}

	while (s[0] == '0' && s[1] != '.')
	{
		s.erase(0, 1);
	}

	int isNegative = 0;
	if (s[0] == '1')
	{
		isNegative = 1;
	}

	bit[0] = isNegative;
	int exponent = 0;

	int viTriSo1DauTienTrongChuoiS = s.find('1');
	int viTriDauCham = s.find('.');

	if (viTriSo1DauTienTrongChuoiS == -1)
	{
		return;
	}
	else
	{
		if (viTriDauCham == -1)
		{
			exponent = s.length() - 1;
		}
		else
		{
			int Hieu = viTriSo1DauTienTrongChuoiS - viTriDauCham;
			if (Hieu > 0)
			{
				exponent = -Hieu;
			}
			if (Hieu < 0)
			{
				exponent = -(Hieu + 1);
			}
		}

		exponent += 16383;
		for (int i = 1; i < 16; i++)
		{
			bit[16 - i] = (exponent >> (i - 1)) & 1;
		}

		int k = 16;
		for (int i = viTriSo1DauTienTrongChuoiS + 1; i < s.length(); i++)
		{
			if (s[i] != '.')
			{
				bit[k] = (s[i] - '0');
				k++;
			}
		}
		if (k < 127)
		{
			for (int i = k; i < 128; i++)
			{
				bit[i] = 0;
			}
		}

		for (int i = 0; i < 128; i++)
		{
			if (bit[i] == 1)
			{
				x.data[i / 32] = x.data[i / 32] | (1 << (31 - i % 32));
			}
		}

		delete[]bit;
	}
}

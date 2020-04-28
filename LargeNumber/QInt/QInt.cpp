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

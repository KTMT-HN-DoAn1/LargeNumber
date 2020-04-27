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

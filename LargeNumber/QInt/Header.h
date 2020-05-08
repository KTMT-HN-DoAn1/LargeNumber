#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS	


#pragma once

#include<iostream>
#include<string>
#include<fstream>
using namespace std;
#include"Convert.h"


enum Arithmetic { ADD, SUB, MULT, DIV, SL, SR, ROL, ROR, LESS, GREATER, EQUAL, LOE, GROE , AND, OR, XOR,NOT};

//Hàm cắt chuồi thô ban đầu thành các số hạng và toán hạng với s là chuỗi thô ban đầu--> a, b là 2 số cần tính và c là phép tính
void CutString(string s, string& a, string& b, string& c);

//Xác định loại phép tính
Arithmetic Type(string s);

//Tính toán QInt từ các phần tử đã lọc
QInt calcuQInt(int& type, string a, string b, string c);

//Hàm thực thi tính toán cho QInt từ chuỗi thô
QInt runArithmetic(string s, int& type);

//Hàm chạy chức năng tính toán cho QInt
void funRunQIntArithmetic();

//Hàm thao tác với QInt
void funRunQInt();

//Hàm xử lý các thao tác làm việc qua file
void QIntFileProcessing(fstream& f, fstream& g);


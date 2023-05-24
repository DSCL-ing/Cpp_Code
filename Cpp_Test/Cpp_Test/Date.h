#pragma once
#define  _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<stdlib.h>

using namespace std;


class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1);

	//运算符构造函数重载
	Date& operator=(const Date& d);
	bool operator==(const Date& d);
	bool operator< (const Date& d);
	bool operator<=(const Date& d);
	bool operator> (const Date& d);
	bool operator>=(const Date& d);
	bool operator!=(const Date& d);

	//d + 100
	Date operator+ (int day);

	//d += 100
	Date& operator+=(int day);

	//d - 100
	
	//d1 - d2

	//++d

	//d++

	//--d

	//d--

	//年月日规定
	int getRegulationsMonthDays(int year, int Month);


	//打印
	void print();

	//private:
	int _year; // 年
	int _month; // 月
	int _day; // 日
};


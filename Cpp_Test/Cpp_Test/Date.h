#pragma once
#define  _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<stdlib.h>

using namespace std;


class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1);

	//��������캯������
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

	//�����չ涨
	int getRegulationsMonthDays(int year, int Month);


	//��ӡ
	void print();

	//private:
	int _year; // ��
	int _month; // ��
	int _day; // ��
};


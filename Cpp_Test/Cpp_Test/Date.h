#pragma once
#define  _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<stdlib.h>

using namespace std;

//类里面短小函数，适合做内联的函数，一般是直接在类里面定义
//更符合我们习惯，小函数声明与定义分析用户实现麻烦。
//其次编译器要进符号表，链接...太小没意义,小函数内联更快

class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1);

	//友元函数:只是修改权限,不是类成员
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);

	//运算符构造函数重载
	Date& operator= (const Date& d);
	bool  operator==(const Date& d);
	bool  operator< (const Date& d);
	bool  operator<=(const Date& d);
	bool  operator> (const Date& d);
	bool  operator>=(const Date& d);
	bool  operator!=(const Date& d);
	Date  operator+ (int day);//d + 100
	Date& operator+=(int day);//d += 100
	Date& operator++(		);//++d
	Date  operator++(int	);//d++
	Date& operator-=(int day);//d -= 100
	Date  operator- (int day);//d - 100
	Date& operator--(		);//--d
	Date  operator--(int	);//d--
	int   operator- (const Date& d);//d1 - d2

	//年月日规定
	int getRegulationsMonthDays(int year, int Month);

	//恢复初始化
	Date& Init(int year = 1, int month = 1, int day = 1);

	//打印
	void print();

private:
	int _year; // 年
	int _month; // 月
	int _day; // 日
};

inline ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "/" << d._month << "/" << d._day;
	return out;
}

inline istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}
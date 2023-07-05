#pragma once
#define  _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<stdlib.h>
#include<assert.h>

using namespace std;

//类里面短小函数，适合做内联的函数，一般是直接在类里面定义
//更符合我们习惯，小函数声明与定义分析用户实现麻烦。
//其次编译器要进符号表，链接...太小没意义,小函数内联更快

class Date
{

private:
	int _year; // 年
	int _month; // 月
	int _day; // 日
	//int& _ref ;
	const int c = 1;

public:
	Date()
		:_year()
		,_day()
		,_month()
		//,_ref()//引用必须在,且必须有引用对象,且必须引用对象初始化过
		,c()//const修饰的成员必须在,且必须赋值(初始化列表能给0)
		//还有一个没带无参构造的自定义类型(类)成员
	{}

	Date(int year, int month, int day);


	//友元函数:只是修改权限,不是类成员
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);

	//运算符构造函数重载
	Date& operator= (const Date& d);
	bool  operator==(const Date& d)const;
	bool  operator< (const Date& d)const;
	bool  operator<=(const Date& d)const;
	bool  operator> (const Date& d)const;
	bool  operator>=(const Date& d)const;
	bool  operator!=(const Date& d)const;
	Date  operator+ (int day)const;//d + 100
	Date& operator+=(int day);//d += 100
	Date& operator++(		);//++d
	Date  operator++(int	);//d++
	Date& operator-=(int day);//d -= 100
	Date  operator- (int day)const;//d - 100
	Date& operator--(		);//--d
	Date  operator--(int	);//d--
	int   operator- (const Date& d)const;//d1 - d2

	//取地址运算符函数重载(天选之子5)
	Date* operator& () 
	{
		return this;  
	}

	//const修饰的取地址运算符函数重载(天选之子6)
	const Date* operator& ()const //不能只在函数名后面加const,因为那样返回值会权限放大
	{
		
		return this;
	}

	//数组数据获取运算符重载
	int& operator[](int i)
	{
		assert(i >= 0 );  
		int a[10];//演示用,实际在外部
		return a[i];
	}

	//const修饰的数组数据获取运算符重载([]的函数重载:参数不同,const * this)
	const int& operator[](int i) const
	{
		assert(i >= 0);
		int a[10];//演示用,实际在外部
		return a[i];
	}


	//年月日规定
	int getRegulationMonthDays(int year, int Month)const;

	//恢复初始化
	Date& Init(int year = 1, int month = 1, int day = 1);

	//打印
	void print()const;


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
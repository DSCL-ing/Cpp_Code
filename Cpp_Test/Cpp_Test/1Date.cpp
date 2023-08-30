#pragma once

#include"1Date.h"



Date& Date::operator=(const Date& d)
{
	if (this != &d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	return *this;
}

bool Date::operator==(const Date& d)const
{
	return _day == d._day &&
		_month == d._month &&
		_year == d._year;
}

bool Date::operator< (const Date& d)const
{
	return _year < d._year
		|| _year == d._year && _month < d._month
		|| _year == d._year && _month == d._month && _day < d._day;
}

bool Date::operator<=(const Date& d)const
{
	return *this < d || *this == d;
}

bool Date::operator> (const Date& d)const
{
	return !(*this <= d);
}

bool Date::operator>=(const Date& d)const
{
	return *this > d || *this == d;
}

bool Date::operator!=(const Date& d)const
{
	return !(*this == d);
}

//无参默认是右操作数,还有operator*()
Date& Date::operator++() //前置++
{

	return (*this+=1);
}

Date Date::operator++(int) //后置++.int用于占位,区别前置++构成重载,语法规定
{
	Date tmp(*this);
	*this += 1;
	return tmp;
}

Date& Date::operator+=(int day)
{
	//*this = *this + day;//如果复用+来实现，开销：调用+(拷贝),调用赋值

	if ( day < 0)
	{
		*this -= -day;
		return *this;
	}

	_day += day;
	while (_day > getRegulationMonthDays(_year, _month))
	{
		_day -= getRegulationMonthDays(_year, _month);
		_month++;
		if (_month == 13)
		{
			_month = 1;
			++_year;
		}
	}
	return *this;
}

Date Date::operator+ (int day)const
{
						//Date tmp1(*this);
	Date tmp = *this; //1.调用拷贝构造
	tmp += day;		//2.调用+=(引用)

	//Date tmp = *this;
	//tmp._day += day;
	//while (tmp._day > tmp.getRegulationMonthDays(tmp._year, tmp._month))
	//{
	//	tmp._day -= tmp.getRegulationMonthDays(tmp._year, tmp._month);
	//	tmp._month++;
	//	if (tmp._month == 13)
	//	{
	//		tmp._month = 1;
	//		++tmp._year;
	//	}
	//}
	return tmp;  //3.传值返回调用拷贝构造
	//1,2,3点开销更大,所以复用+=来实现+(引用底层就是好)
}

Date& Date::operator-= (int day)
{
	if ( day < 0)
	{
		*this += -day;
		return *this;
	}

	_day -= day;
	while (_day <= 0)
	{
		--_month;
		if (_month == 0)
		{
			--_year;
			_month = 12;
		}
		_day += getRegulationMonthDays(_year, _month);
	}
	return *this;
}



Date Date::operator- (int day)const
{
	Date tmp(*this);
	return tmp -= day;
}

int Date::operator-(const Date& d)const
{
	Date max = *this;
	Date min = d;
	int flag = 1;
	if (*this < d)
	{
		max = d;
		min = *this;
		flag = -1;
	}
	
	int count = 0;

	while (max != min)
	{
		--max;
		++count;
	}

	return flag * count;
}


Date& Date::operator--()
{
	return *this -= 1;
}

Date Date::operator--(int)
{
	Date tmp(*this);
	*this -= 1;
	return tmp;
}



//获取一个月有多少天
int Date::getRegulationMonthDays(int year, int month)const
{
	int monthDaysArray[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if ( month == 2 && ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0)))
	{
		return 29;
	}
	else
	{
		return monthDaysArray[month];
	}
}



Date& Date::Init(int year, int month, int day)
{
	if (month > 0 && month < 13 && day>0 && day < getRegulationMonthDays(year, month))
	{
		_year = year;
		_month = month;
		_day = day;
		return *this;
	}
	else
	{
		cout << "日期无效" << endl;
		exit(-1);
	}
}



Date::Date(int year, int month, int day)
{
	if (month > 0 && month < 13 && day>0 && day < getRegulationMonthDays(year, month))
	{
		_year = year;
		_month = month;
		_day = day;
	}
	else
	{
		cout << "日期无效" << endl;
		exit(-1);
	}
}

void Date::print()const
{
	cout << _year << "/" << _month << "/" << _day << endl;
}

//ostream& operator<<(ostream& out, const Date& d)
//{
//	out << d._year << "/" << d._month << "/" << d._day;
//	return out;
//}
//
//istream& operator>>(istream& in, Date& d)
//{
//	in >> d._year >> d._month >> d._day;
//	return in;
//}

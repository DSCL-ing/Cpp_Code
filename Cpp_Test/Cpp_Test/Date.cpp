

#include"Date.h"

Date& Date::operator-= (int day)
{
	_day -= day;
	while (_day <= 0)
	{
		_month--;
		if (_month == 0)
		{
			_month = 12;
			--_year;
		}
		_day += getRegulationsMonthDays(_year, _month);
	}
	return *this;
}

Date Date::operator- (int day)
{
	Date tmp(*this);
	return tmp-=1;
}

int Date::operator-(const Date& d)
{




	_year -= d._year;
	if (_month - d._month>0 )
	{
		_month -= d._month;
	}
	else
	{
		--_year;
		_month += 12 - d._month;
	}
	if (_day - d._day > 0)
	{
		_day = d._day;
	}
	else
	{
		if (--_month == 0)
		{
			_month = 12;
		}
		_day += getRegulationsMonthDays(_year, _month) - d._day;
	}

	

	return 1;
}

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

bool Date::operator==(const Date& d)
{
	return _day == d._day &&
		_month == d._month &&
		_year == d._year;
}

bool Date::operator< (const Date& d)
{
	return _year < d._year
		|| _year == d._year && _month < d._month
		|| _year == d._year && _month == d._month && _day < d._day;

}

bool Date::operator<=(const Date& d)
{
	return *this < d || *this == d;
}

bool Date::operator> (const Date& d)
{
	return !(*this <= d);
}

bool Date::operator>=(const Date& d)
{
	return *this > d || *this == d;
}

bool Date::operator!=(const Date& d)
{
	return !(*this == d);
}

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
	//*this = *this + day;//调用+(拷贝),调用赋值

	_day += day;
	while (_day > getRegulationsMonthDays(_year, _month))
	{
		_day -= getRegulationsMonthDays(_year, _month);
		_month++;
		if (_month == 13)
		{
			_month = 1;
			++_year;
		}
	}
	return *this;
}

Date Date::operator+ (int day)
{
						//Date tmp1(*this);
	Date tmp = *this; //1.调用拷贝构造
	tmp += day;		//2.调用+=(引用)

	//Date tmp = *this;
	//tmp._day += day;
	//while (tmp._day > tmp.getRegulationsMonthDays(tmp._year, tmp._month))
	//{
	//	tmp._day -= tmp.getRegulationsMonthDays(tmp._year, tmp._month);
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

//获取一个月有多少天
int Date::getRegulationsMonthDays(int year, int month)
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



void Date::Init(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}


Date::Date(int year, int month, int day)
{
	//判断日期规则是否正确
	_year = year;
	_month = month;
	_day = day;
}

void Date::print()
{
	cout << _year << "/" << _month << "/" << _day << endl;
}



#include<iostream>
#include<stdlib.h>
#include"¿‡.h"

Date& Date::operator=(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
	return *this;
}

bool Date::operator==(const Date& d)
{
	return _day == d._day &&
		_month == d._month &&
		_year == d._year;
}

bool Date::operator<(const Date& d)
{
	return _year < d._year 
		||_year == d._year && _month < d._month 
		||_year == d._year && _month == d._month && _day < d._day;

}

bool Date::operator<=(const Date& d)
{
	return *this < d || *this == d;
}

bool Date::operator>(const Date& d)
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

Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}

void Date::print()
{
	cout << _year << "//" << _month << "//" << _day << endl;
}

Stack::Stack()
{
	//this->_a = nullptr;
	//this->_size = 0;
	//this->_capacity = 0;
}

Stack::Stack(int n)
{
	this->_size = 0;
	this->_capacity = n;
	this->_a = (int*)malloc(n * sizeof(int));
	if (_a == nullptr)
	{
		perror("malloc fail!");
		return;
	}
}

void Stack::Push(int x)
{
	this->_a[this->_size] = x;
}

Stack::~Stack()
{
	free(this->_a);
	this->_a = nullptr;
}






void Stack1::Init(int n) //
{
	a = (int*)malloc(sizeof(int) * n);
	if (a == nullptr)
	{
		perror("malloc fail!");
		return;
	}
	capacity = n;
	size = 0;
}


void Stack1::Push(int x)

{
	//..
	a[size++] = x;
}


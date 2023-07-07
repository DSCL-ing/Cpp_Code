#pragma once


class Date
{
public:
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}

	bool operator==(const Date& d)
	{
		return _day == d._day &&
			_month == d._month &&
			_year == d._year;
	}
	bool operator<(const Date& d)
	{

		return _year < d._year 
			||_year == d._year && _month < d._month 
			||_year == d._year && _month == d._month && _day < d._day;
	}

	bool operator<=(const Date& d)
	{
		return *this < d || *this == d;
	}

	bool operator>(const Date& d)
	{
		return !(*this <= d);
	}

	bool operator>=(const Date & d)
	{
		return *this > d || *this == d;
	}

	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}

	//private:
	int _year; // 年
	int _month; // 月
	int _day; // 日
};










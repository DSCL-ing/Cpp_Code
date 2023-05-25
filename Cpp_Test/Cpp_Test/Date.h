#pragma once
#define  _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<stdlib.h>

using namespace std;

//�������С�������ʺ��������ĺ�����һ����ֱ���������涨��
//����������ϰ�ߣ�С���������붨������û�ʵ���鷳��
//��α�����Ҫ�����ű�����...̫Сû����,С������������

class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1);

	//��Ԫ����:ֻ���޸�Ȩ��,�������Ա
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);

	//��������캯������
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

	//�����չ涨
	int getRegulationsMonthDays(int year, int Month);

	//�ָ���ʼ��
	Date& Init(int year = 1, int month = 1, int day = 1);

	//��ӡ
	void print();

private:
	int _year; // ��
	int _month; // ��
	int _day; // ��
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
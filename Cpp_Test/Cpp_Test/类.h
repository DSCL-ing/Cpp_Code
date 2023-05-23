#pragma once
#define  _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<stdlib.h>
#include<stdbool.h>

using namespace std;

class Date
{
public:
	Date(int year = 1 , int month =1 ,int day = 1);

	//运算符构造函数重载
	Date& operator=(const Date& d);
	bool operator==(const Date& d2);
	bool operator<(const Date& d2);
	bool operator<=(const Date& d);
	bool operator>(const Date& d2);
	bool operator>=(const Date& d);
	bool operator!=(const Date& d);

	//打印
	void print();
//private:
	int _year; // 年
	int _month; // 月
	int _day; // 日
};

//一般定义方式
class Stack
{
public:
	//成员函数
	//void Init(int n = 4); //缺省参数
	Stack();			//构造函数
	Stack(int n);
	void Push(int x);
	~Stack();			//析构函数
private:
	//成员变量
	int* _a = 0;
	int _size = 0;
	int _capacity = 0;
};



//方式1：未学权限，先使用struct
struct Stack1
{
	//成员函数
	void Init(int n = 4); //缺省参数
	void Push(int x);
	//成员变量
	int* a ;
	int size ;
	int capacity ;
};

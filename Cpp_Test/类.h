#pragma once

#include<iostream>
#include<stdlib.h>


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
	int* _a;
	int _size;
	int _capacity;
};



//方式1：未学权限，先使用struct
struct Stack1
{
	//成员函数
	void Init(int n = 4); //缺省参数
	void Push(int x);
	//成员变量
	int* a;
	int size;
	int capacity;
};
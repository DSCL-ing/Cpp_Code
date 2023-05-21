#pragma once

#include<iostream>
#include<stdlib.h>

//方式1：未学权限，先使用struct
struct Stack
{
	//成员函数
	void Init(int n = 4); //缺省参数
	void Push(int x);
	//成员变量
	int* a;
	int size;
	int capacity;
};


//一般定义方式
class Stack2
{
public:
	//成员函数
	void Init(int n = 4); //缺省参数
	void Push(int x);
private:
	//成员变量
	int* a;
	int size;
	int capacity;
};




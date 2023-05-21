#pragma once

<<<<<<< HEAD
#include<iostream>
#include<stdlib.h>

//方式1：未学权限，先使用struct
struct Stack1 
=======

struct Stack
>>>>>>> 880599d5e492cc651fa1e142333ded81f312b5b2
{
	//成员函数
	void Init(int n = 4); //缺省参数
	void Push(int x);
	//成员变量
	int* a;
	int size;
	int capacity;
};
<<<<<<< HEAD

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


=======
>>>>>>> 880599d5e492cc651fa1e142333ded81f312b5b2

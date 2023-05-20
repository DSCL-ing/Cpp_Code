#pragma once


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

#pragma once

#include<iostream>
#include<stdlib.h>

//��ʽ1��δѧȨ�ޣ���ʹ��struct
struct Stack
{
	//��Ա����
	void Init(int n = 4); //ȱʡ����
	void Push(int x);
	//��Ա����
	int* a;
	int size;
	int capacity;
};


//һ�㶨�巽ʽ
class Stack2
{
public:
	//��Ա����
	void Init(int n = 4); //ȱʡ����
	void Push(int x);
private:
	//��Ա����
	int* a;
	int size;
	int capacity;
};




#pragma once

#include<iostream>
#include<stdlib.h>


//һ�㶨�巽ʽ
class Stack
{
public:
	//��Ա����
	//void Init(int n = 4); //ȱʡ����
	Stack();			//���캯��
	Stack(int n);
	void Push(int x);
	~Stack();			//��������
private:
	//��Ա����
	int* _a;
	int _size;
	int _capacity;
};



//��ʽ1��δѧȨ�ޣ���ʹ��struct
struct Stack1
{
	//��Ա����
	void Init(int n = 4); //ȱʡ����
	void Push(int x);
	//��Ա����
	int* a;
	int size;
	int capacity;
};
#pragma once
#define  _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<stdlib.h>
#include<stdbool.h>

using namespace std;



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
	int* _a = 0;
	int _size = 0;
	int _capacity = 0;
};

//��ʽ1��δѧȨ�ޣ���ʹ��struct
struct Stack1
{
	//��Ա����
	void Init(int n = 4); //ȱʡ����
	void Push(int x);
	//��Ա����
	int* a ;
	int size ;
	int capacity ;
};

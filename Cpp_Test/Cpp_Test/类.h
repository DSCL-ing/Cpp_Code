#pragma once


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

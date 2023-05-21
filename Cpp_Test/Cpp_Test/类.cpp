
#include<iostream>
#include<stdlib.h>
#include"类.h"


Stack::Stack()
{
	this->_a = nullptr;
	this->_size = 0;
	this->_capacity = 0;
}

Stack::Stack(int n)
{
	this->_size = 0;
	this->_capacity = n;
	this->_a = (int*)malloc(n * sizeof(int));
	if (_a == nullptr)
	{
		perror("malloc fail!");
		return;
	}
}

void Stack::Push(int x)
{
	this->_a[this->_size] = x;
}

Stack::~Stack()
{
	free(this->_a);
	this->_a = nullptr;
}












void Stack1::Init(int n) //
{
	a = (int*)malloc(sizeof(int) * n);
	if (a == nullptr)
	{
		perror("malloc fail!");
		return;
	}
	capacity = n;
	size = 0;
}



void Stack1::Push(int x)

{
	//..
	a[size++] = x;
}

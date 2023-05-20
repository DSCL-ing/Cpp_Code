#include<iostream>
#include<stdlib.h>
#include"¿‡.h"

void Stack::Init(int n) //
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

void Stack::Push(int x)
{
	//..
	a[size++] = x;
}

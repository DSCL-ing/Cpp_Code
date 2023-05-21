<<<<<<< HEAD

#include"Àà.h"

void Stack1::Init(int n) //
=======
#include<iostream>
#include<stdlib.h>
#include"Àà.h"

void Stack::Init(int n) //
>>>>>>> 880599d5e492cc651fa1e142333ded81f312b5b2
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

<<<<<<< HEAD
void Stack1::Push(int x)
=======
void Stack::Push(int x)
>>>>>>> 880599d5e492cc651fa1e142333ded81f312b5b2
{
	//..
	a[size++] = x;
}

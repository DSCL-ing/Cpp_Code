
#include"¿‡.h"

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

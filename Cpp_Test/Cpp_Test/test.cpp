#pragma once

#define _CRT_SECURE_NO_WARNINGS

//#include <ctime>
//#include <random>
#include <iostream>
using std::cout;
using std::endl;
#include<string.h>
int main()
{
	for (int i = 0; i < 200; ++i)
	{
		printf("%d : %s\n", i, strerror(i));
	}
	return 0;
}


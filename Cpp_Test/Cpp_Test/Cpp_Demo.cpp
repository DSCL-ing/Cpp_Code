#define  _CRT_SECURE_NO_WARNINGS 1
//#include"Cpp_Demo.h"

#include<iostream>
using namespace std;

int main()
{
	cout << "hello world" << endl;
	cout << "hello world" << '\n';

	char name[10] = "����";
	int age = 10;
	cout << "����:" << name << endl;
	cout << "����:" << age << endl;

	printf("����:%s\n", name);
	printf("����:%d\n", age);


}
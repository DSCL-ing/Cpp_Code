#define  _CRT_SECURE_NO_WARNINGS 1
//#include"Cpp_Demo.h"

#include<iostream>
using namespace std;

int main()
{
	cout << "hello world" << endl;
	cout << "hello world" << '\n';

	char name[10] = "张三";
	int age = 10;
	cout << "姓名:" << name << endl;
	cout << "年龄:" << age << endl;

	printf("姓名:%s\n", name);
	printf("年龄:%d\n", age);


}
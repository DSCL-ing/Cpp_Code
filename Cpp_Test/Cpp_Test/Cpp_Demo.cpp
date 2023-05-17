#define  _CRT_SECURE_NO_WARNINGS 1
//#include"Cpp_Demo.h"

#include<iostream>
using namespace std;







void Swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

int main()
{
	int a;
	int& i = a; //i ,a指向同一个对象
	
	int* j;
	int*& rj = j;//指针引用


	int a = 1;
	int b = 2;
	Swap(a, b);
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	return 0;
}




int main1()
{
	cout << "hello world" << endl;
	cout << "hello world" << '\n';

	char name[10] = "张三";
	int age = 10;
	cout << "姓名:" << name << endl;
	cout << "年龄:" << age << endl;


	printf("姓名:%s\n", name);
	printf("年龄:%d\n", age);





	//ctrl是光标不动,往上插入一行
	//ctrl+shift(shift) 是往下插入一行,光标跟随

	return 0;
}
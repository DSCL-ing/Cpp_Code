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
	int& i = a; //i ,aָ��ͬһ������
	
	int* j;
	int*& rj = j;//ָ������


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

	char name[10] = "����";
	int age = 10;
	cout << "����:" << name << endl;
	cout << "����:" << age << endl;


	printf("����:%s\n", name);
	printf("����:%d\n", age);





	//ctrl�ǹ�겻��,���ϲ���һ��
	//ctrl+shift(shift) �����²���һ��,������

	return 0;
}
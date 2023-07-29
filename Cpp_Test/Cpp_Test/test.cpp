
#pragma once
#include<iostream>
using std::cout;
using std::endl;
using std::cin;
using std::swap;
using std::max;

//int main()
//{
//	double d = 1.1;
//	int& ri = d;
//	return 0;
//}

#include"21polymorphism.h"
int main()
{
	//test::test_polymorphism1();
	//test1::test_polymorphism2();
	//test2::test_VFTable1();
	//test2::test_VFTable2();
	test3::test_VFTable1();
	return 0;
}

//#include"20inheritance.h"
//int main()
//{
//	Student s1("zhangsan" , 20);
//	Student s2(s1);
//	Person p = s1;
//
//	return 0;
//}


#pragma once




#include<iostream>
#include"myVector.h"

using std::cout;
using std::endl;
using std::cin;
using std::swap;
using std::max;


void test_vector4()
{
	vector<int> v1;
	v1.resize(10, 0);
	vector<int> v2(v1.begin(), v1.end());
	for (auto e : v2)
	{
		cout << e << " ";
	}
}



int main()
{
	test_vector4();

	//TestVectorExpand();

	return 0;
}




//#include<string>
//using std::string;
#include"myString.h"
int main1()
{
	//test::test1_string();
	//test::test2_string();
	//test::test3_string();
	//test::test4_string();
	//test::test5_string();
	//test::test6_string();
	return 0;
}
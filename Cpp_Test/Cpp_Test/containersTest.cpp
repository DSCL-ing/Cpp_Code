
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
	vector<int> v2(10, 0);
}

void test_vector5()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	//vector<int>::iterator pos = std::find(v.begin(), v.end(), 2);
	//if (pos != v.end())
	//{
	//	v.insert(pos, 20);
	//}

	//for (auto e : v)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;

	//pos = std::find(v.begin(), v.end(), 2);
	//if (pos != v.end())
	//{
	//	v.erase(pos);
	//}

	//for (auto e : v)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;

	//v.erase(v.begin());

	//for (auto e : v)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;
}

int main()
{
	test_vector5();

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
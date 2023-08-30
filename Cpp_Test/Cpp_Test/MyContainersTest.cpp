
#pragma once
#include<iostream>
using std::cout;
using std::endl;
using std::cin;

#include"28myMap_unordered.h"
#include"28mySet_unordered.h"
int main()
{
	test::test_My_unordered_map1();
	test::test_My_unordered_set1();
	return 0;
}

//#include"26myMap.h"
//#include"26mySet.h"
//int main()
//{
//	test::test_myMap1();
//	//test::test_mySet1();
//
//	//test::test_myMap2();
//	//test::test_myMap3();
//	return 0;
//}




//#include<set>
//#include<iostream>
//using std::cout;
//using std::endl;
//using std::cin;
//using std::set;
//void test_set1()
//{
////集合的互异性验证 -- 迭代器
//	std::set<int> s1;
//	s1.insert(3);
//	s1.insert(1);
//	s1.insert(4);
//	s1.insert(2);
//	s1.insert(1);
//	s1.insert(2);
//	std::set<int>::iterator it1 = s1.begin();
//	while (it1 != s1.end())
//	{
//		std::cout << *it1 << " ";
//		++it1;
//	} //Result:>1 2 3 4
//	cout << endl;
//	//范围for
//	for (auto e : s1)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//}
//void test_set2()
//{
//	//测试元素存在函数
//	std::set<int> s1;
//	s1.insert(3);
//	s1.insert(1);
//	s1.insert(4);
//	s1.insert(2);
//	s1.insert(1);
//	s1.insert(2);
//	int x;
////func:find() -> Test -- 间接判断
//	/*while (cin >> x)
//	{
//		auto ret = s1.find(x);
//		if (ret != s1.end())
//		{
//			cout << "在" << endl;
//		}
//		else
//		{
//			cout << "不在" << endl;
//		}
//	}*/
////count 直接判断 
//	while (cin >> x)
//	{
//		if (s1.count(x))
//		{
//			cout << "在" << endl;
//		}
//		else
//		{
//			cout << "不在" << endl;
//		}
//	}
//
//
//}
//
//void test_multiset1()
//{
//	std::multiset<int> s1;
//	s1.insert(3);
//	s1.insert(1);
//	s1.insert(4);
//	s1.insert(2);
//	s1.insert(1);
//	s1.insert(1);
//	s1.insert(1);
//	s1.insert(2);
//	//初识multiset
//	//std::set<int>::iterator it1 = s1.begin(); //也可以用set
//	std::multiset<int>::iterator it1 = s1.begin();
//	while (it1 != s1.end())
//	{
//		std::cout << *it1 << " ";
//		++it1;
//	} //Result:>1 2 3 4
//	cout << endl;
//
//	//验证multiset的第一个重复值是中序遍历到的第一个key
//	//思路:将第一个find及后面所有相同的值打印出来,查看是否包含了所有的该值
//
//	auto ret = s1.find(1);
//	while (ret != s1.end() && *ret == 1)
//	{
//		cout << *ret << " ";
//			++ret;
//	}
//
//}
//#include<map>
//#include<string>
//using std::string;
//void test_map1()
//{
//	//map的使用
//	std::map<string, string>  dict;
//	dict.insert(std::pair<string, string>("sort", "排序")); //匿名对象插入
//	dict.insert(std::make_pair("string", "字符串"));    //pair封装插入
//	dict.insert(std::make_pair("count", "计数"));
//	auto it = dict.begin();
//	while (it != dict.end())
//	{
//		cout << it->first << ":" << it->second << endl;
//		++it;
//	}
//}
//
//void test_map2()
//{
//	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜","苹果", "香蕉", "苹果", "香蕉" };
//	std::map<string, int> countMap;
//	/*for (auto e : arr)
//	{
//		auto ret = countMap.find(x);
//		if (ret==countMap.end())
//		{
//			countMap.insert(std::pair<string, int>(x, 1));
//		}
//		else
//		{
//			++ret->second;
//		}
//	}*/
//
//	for (auto& e : arr)
//	{
//		++countMap[e];
//	}
//
//	for (auto& s : countMap)
//	{
//		cout <<  s.first << ":" << s.second << endl;
//	}
//
//
//}
//
//
//
//int main()
//{
//	//test_set1();
//	//test_set2();
//	//test_multiset1();
//	//test_map1();
//	test_map2();
//
//
//	return 0;
//}

//#include"myPriority_Queue.h"
//int main()
//{
//	//test::test_priority_queue2();
//	//test::test_priority_queue1();
//	return 0;
//}

//#include<list>
//#include"myQueue.h"
//int main()
//{
//	test::test_quque1();
//	return 0;
//}

////#include<stack>
//#include<vector>
//#include<list>
//#include"myStack.h"
//int main()
//{
//	//test::test_stack1();
//	test::test_stack2();
//	return 0;
//}

//#include<stack>
//class MinStack {
//private:
//    std::stack<int> st;
//    std::stack<int> mst;
//public:
//    MinStack() {
//
//    }
//
//    void push(int val) {
//        st.push(val);
//        if (mst.empty() || mst.top() > val)
//        {
//            mst.push(val);
//        }
//    }
//
//    void pop() {
//        if (mst.top() == st.top())
//        {
//            mst.pop();
//        }
//        st.pop();
//    }
//
//    int top() {
//        return st.top();
//    }
//
//    int getMin() {
//        return mst.top();
//    }
//};
//int main()
//{
//    MinStack ms;
//    ms.push(0);
//    ms.push(1);
//    ms.push(0);
//    cout << ms.getMin() << endl;
//    ms.pop();
//    cout << ms.getMin() << endl;
//    
//    return 0;
//}


//#include<iostream>
//using std::cout;
//using std::endl;
//using std::cin;
//#include"Test.h"
//#include"12myList.h"
//int main()
//{
//	//test::test_list1();
//	//test::test_list2();
//	//test::test_list3();
//	//test::test_list4();
//
//	//深拷贝测试
//	using namespace b;
//	list<int> lt(1);
//	lt.push_back(2);
//	lt.push_back(3);
//	lt.push_back(4);
//	list<list<int>> lt1;
//	lt1.push_back(lt);
//	list<list<int>> lt2(lt1); 
//	return 0;
//}



////#include"myVector.h"
//int main()
//{
//	test_vector4();
//
//	return 0;
//}




//#include<string>
//using std::string;
//#include"myString.h"
//int main1()
//{
	//test::test1_string();
	//test::test2_string();
	//test::test3_string();
	//test::test4_string();
	//test::test5_string();
	//test::test6_string();
//	return 0;
//}
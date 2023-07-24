
#pragma once




#include<iostream>

using std::cout;
using std::endl;
using std::cin;
using std::swap;
using std::max;

#include"myPriority_Queue.h"

int main()
{
	test::test_priority_queue2();
	//test::test_priority_queue1();
	return 0;
}

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




////#include"Test.h"
//#include"myList.h"
//int main()
//{
//	test::test_list1();
//	//test::test_list2();
//	//test::test_list3();
//	//using namespace bit;
//	//list<int> l(1);
//	//l.push_back(2);
//	//l.push_back(3);
//	//l.push_back(4);
//	//list<list<int>> lt1;
//	//lt1.push_back(l);
//	//list<list<int>> lt2(lt1);
//
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
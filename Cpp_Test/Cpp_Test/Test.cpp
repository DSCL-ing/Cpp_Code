﻿
#pragma execution_character_set("utf-8")//解决中文乱码

#include"类.h"
#include"Date.h"

#include<iostream>

//using namespace std;

using std::cout;
using std::endl;

//class A
//{
//public:
//	static int count;
//};
//
//int A::count  = 0;
//
// int main()
// {
//
//	 A* ptr = nullptr;
//	 cout << ptr->count << endl;
//
//	 return 0;
// }

class A {
public:
	int _a;
	void fun() {
	};
	void fun(int a) {
		_a = a;
	};
};
int main() {
	Date d1;
	Stack s;
	A* ptr = nullptr;
	ptr->fun();
	//ptr->fun(1);
	return 0;
}


//运算符重载
//int main()
//{
//	
//	Date d1(2023,5,24);		 
//	Date d2;				 
//	Date d3;
//
//	//正常调用：d1.operator+(100);
//
//	//验证‘=’和‘d+=100’
//	d2 = d1 += 2000;		 
//	d1.print();				 //2028/11/13
//	d2.print();				 //2028/11/13
//							 
//	d1.Init();				 
//	d2.Init();				 
//						
//	//验证d+100 
//	d3 = d2 + 2000;			 
//	d2.print();				 //1/1/1
//	d3.print();				 //6/6/24
//				
//	//验证前后置++
//	(++d1).print();			 //1/1/2
//	(d2++).print();			 //1/1/1
//	d2.print();				 //1/1/2
//			
//	d1.Init();				 
//	d2.Init();				 
//	
//	//验证 d -=	100			 				 
//	(d1-=1).print();		 //0/12/31
//	d1.print();				 //0/12/31		 
//	d3.Init(2023, 5, 24);	 
//	(d3 -= 2000).print();	 //2017/12/1
//
//	d1.Init();
//	d2.Init();
//
//	//验证 d - 100
//	d2 = d1 - 1;
//	d1.print();				 //1/1/1
//	d2.print();				 //0/12/31
//	
//	d2 = d1.Init(2023, 5, 25);
//	(d1 += -100).print();    //2023/2/14
//	(d2 -= -100).print();	 //2023/9/2
//
//	d1.Init();
//	d1--.print();			 //1/1/1
//	(--d1).print();			 //0/12/30
//
//	d1.Init(2023,5,25);
//	d2.Init(2023,9,2);
//	int ret = d1 - d2;
//	cout << ret << endl;	 //-100
//
//	d1.Init(2023, 5, 25);
//	d2.Init(2001, 3, 10);
//	cout << d1 - d2 << endl; 
//
//	//测试cout <<
//	cout << d1 << endl;
//
//	////测试cin >>
//	//cin >> d1;
//	//cout << d1 << endl;
//
//	//测试&
//	cout << &d1 << endl;
//
//	return 0;
//}


//赋值运算符重载
//int main()
//{
//	Date d1;
//	Date d2(1, 1, 2);
//	Date d3(3, 3, 3);
//	cout << d1.operator<(d2) << endl;
//	d1 = d2 = d3;
//	d1.print();
//	d2.print();
//	d3.print();
//	return 0;
//}


//运算符重载1
//bool operator==(const Date& d1, const Date& d2)
//{
//	return d1._day == d2._day &&
//		d1._month == d2._month &&
//		d1._year == d2._year;
//}
//
//int main()
//{
//	Date d1;
//	Date d2(1,1,1);
//	cout << operator==(d1, d2) << endl;
//	cout << (d1 == d2) << endl;
//	return 0;
//}



//int main()
//{
//
//	//调用构造函数
//	Stack st;		//不传参写法.和其他方法不一样,构造方法和其他方法不同之处
//	//Stack st();		//会警告,不能这么写
//	//Stack st1(4);	//传参写法
//
//	return 0;
//}

// inline void Swap(int& a, int& b)
//{
//	int tmp = a;
//	a = b;
//	b = tmp;
//}
//

//
// int main()
// {
//	 Date d1, d2;
//	 d1.Init(2022, 1, 11);
//	 d2.Init(2022, 1, 12);
//
//	 return 0;
// }

 //// 类中既有成员变量，又有成员函数
 //class A1 {
 //public:
	// void f1() {}
 //private:
	// int _a;
 //};
 //// 类中仅有成员函数
 //class A2 {
 //public:
	// void f2() {}
 //};
 //// 类中什么都没有---空类
 //class A3
 //{};
 //int main()
 //{
	// cout << sizeof(A1) << endl; //4
	// cout << sizeof(A2) << endl; //1
	// cout << sizeof(A3) << endl; //1
	// return 0;
 //}

 ////C语言定义结构体
//typedef struct ListNode 
//{
   // int val;
   // struct ListNode* Node;//类型为struct ListNode
//}ListNode;
////C语言中typedef在此处后才起作用

////C++将结构体升级成了类
//struct ListNode
//{
   // int val;
   // ListNode* Node;		//类型为ListNode
//};

 //nullptr
 //void f(int)
 //{
	// cout << "int" << endl; 
 //}

 //void f(int*)
 //{
	// cout << "int *" << endl;
 //}

 //int main()
 //{
	// f(0);
	// f(NULL);
	// return 0;
 //}

 //auto
//inline void Swap(int& a, int& b)
//{
//	int tmp = a;
//	a = b;
//	b = tmp;
//}

/*int main() //5
{
	//auto a = 1, b = 2;
	//auto c = 3, d = 4.0;

	//int array[] = { 1,2,3,4,5,6 };
	//for (auto& x : array) //如果要影响原数组,可以使用引用
	//{
	//	x *= 2;
	//	cout << x << " ";
	//}
	//cout << endl;

	//int* a = 0;
	//auto b = &a;	//自动推导b为a类型
	//auto* c = &a;	//限定c为指针类型,只要是指针，不论二级三级指针
	//auto** d = &a;	//限定d为二级指针起步
	//auto& e = a;	//限定e为别名


	//int a = 1, b = 2;
	//auto c = &a;
	//auto d = b;
	//Swap(a,b);
	//cout << typeid(b).name() << endl;
	//cout << typeid(c).name() << endl;
	//cout << typeid(d).name() << endl;
	return 0;
}*/








//ctrl是光标不动,往上插入一行
//ctrl+shift(shift) 是往下插入一行,光标跟随


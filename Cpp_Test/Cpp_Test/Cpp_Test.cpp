#define  _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"Cpp_Test.h"

#include"类.h"

using namespace std;


int main()
{
	//调用构造函数
	Stack st;		//不传参写法.和其他方法不一样,构造方法和其他方法不同之处
	//Stack st();		//会警告,不能这么写
	Stack st1(4);	//传参写法

	return 0;
}

// inline void Swap(int& a, int& b)
//{
//	int tmp = a;
//	a = b;
//	b = tmp;
//}
//
// class Date
// {
// public:
//	 void Init(int year, int month, int day)
//	 {
//		 _year = year;
//		 _month = month;
//		 _day = day;
//		 cout << this << endl;
//	 }
// private:
//	 int _year; // 年
//	 int _month; // 月
//	 int _day; // 日
// };
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


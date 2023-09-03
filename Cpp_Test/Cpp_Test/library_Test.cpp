
#pragma once

#include<vector>
#include"29C++11.h"
int main()
{
	//test1();
	test2();
	return 0;
}


//#include<iostream>
//#include<set>
//using std::cout;
//using std::endl;
//using std::cin;
//using std::set;
//#include"24AVLTree.h"
//int main()
//{
//	//test::test_AVL1();
//	test::test_AVL2();
//	return 0;
//}

//#include<iostream>
//using std::cout;
//using std::endl;
//using std::cin;
//using std::swap;
//using std::max;





//int main()
//{
//	double d = 1.1;
//	int& ri = d;
//	return 0;
//}

//#include"21polymorphism.h"
//int main()
//{
//	//test::test_polymorphism1();
//	//test1::test_polymorphism2();
//	//test2::test_VFTable1();
//	//test2::test_VFTable2();
//	//test3::test_VFTable1();
//	test3::test_VFTable2();
//	return 0;
//}

//#include"20inheritance.h"
//int main()
//{
//	test1::test_inheritance1();
//
//	return 0;
//}


//#include <string>
//#include<stdlib.h>
//#include<algorithm>

//using namespace std;

//using std::cout;
//using std::cin;
//using std::endl;
//using std::string;
//using std::swap;
//int main11()
//{
//	//system("chcp 65001");
//	//char* s =new char[1];
//	//s[0] = '1';
//	string s1;
//	//string s2 = "Hello";
//	s1.push_back('x');
//	cout << s1 << endl;
//	return 0;
//}

//class A
//{
//private:
//
//	int a;
//public:
//	static int count;
//	A()
//		:a(1)
//	{
//		cout << "A()" << endl;
//		++count;
//	}
//	A(int a)
//		:a(1)
//	{
//		cout << "A()" << endl;
//		++count;
//	} 
//	A(const A& aa)
//		:a(aa.a)
//	{
//		cout << "A()" << endl;
//		++count;
//	}
//	~A()
//	{
//		cout << "~A()" << endl;
//	}
//
//};
//
//
//#include<string.h>
//int main()
//{
//	const char* str = "";
//	//cout << sizeof() << endl;
//	return 0;
//}



//int main()
//{
//	string file("string.h.cpp");
//	size_t pos = file.rfind('.');
//	if (pos != string::npos)
//	{
//		cout << file.substr(pos) << endl;
//	}
//	else
//	{
//		cout << file << endl;
//	}
//	return 0;
//}

//int main()
//{
//	system("chcp 65001");
//	string filename("string.h");
//	FILE* fout = fopen(filename.c_str(), "r");
//	if (fout == nullptr)
//	{
//		perror("fopen fail");
//	}
//	char ch = fgetc(fout);
//	while (ch != EOF)
//	{
//		cout << ch;
//		ch = fgetc(fout);
//	}
//	fclose(fout);
//	return 0;
//}

//int main()
//{
//	string s = "hello world i love you!";
//	string newStr;
//	size_t num = 0;
//	for (auto ch : s)
//	{
//		if (ch == ' ')
//		{
//			++num;
//		}
//	}
//	newStr.reserve(s.size() + num * 2);
//	for (auto ch : s)
//	{
//		if (ch != ' ')
//		{
//			newStr += ch;
//		}
//		else
//		{
//			newStr += "%20";
//		}
//	}
//	cout << newStr << endl;
//	return 0;
//}

//方法一
//int main()
//{
//	//题目:将空格替换成%20
//	string s = "hello world i love you!";
//	size_t num = 0;
//	for (auto ch : s)
//	{
//		if (ch == ' ')
//		{
//			num++;
//		}
//	}
//	s.reserve(size(s) + 2 * num);
//	size_t pos = s.find(' ');
//	while (pos !=string::npos) {
//		s.replace(pos,1, "%20");
//		pos = s.find(' ',pos + 3);
//	}
//	cout << s << endl;
//	return 0;
//}

//void fun(const string& s)
//{
//	//迭代器和begin的const重载,只允许迭代器读,不允许写
//	//const_reverse -- 安全,保护数据不被破坏
//	//string::const_reverse_iterator rit = s.rbegin();
//	auto rit = s.rbegin(); //auto自动推导类型
//	while (rit != s.rend())
//	{
//		//rit+=1; //	不允许修改指针指向的对象的内容,
//		cout << *rit << " ";
//		++rit;
//	}
//
//}

////const迭代器
//int main()
//{
//	string s( "hello world!");
//
//	s.erase(s.begin()+5);
//	cout << s << endl;
//	return 0;
//}

//反向迭代器
//int main()
//{
//	string s1 = "hello world!";
//	string::reverse_iterator rit = s1.rbegin();
//	while (rit != s1.rend())
//	{
//		cout << *rit << " ";
//		++rit; //逻辑设计上对称：反向走，往前也是++
//	}
//	cout << endl;
//	return 0;
//}

//正向迭代器
//int main()
//{
//	string s1("hello world!");
//	string::iterator it = s1.begin();
//	while (it != s1.end())
//	{
//		cout << *it++ << " ";
//	}
//	int a = 1;
//	int b = 2;
//	swap(a, b);
//
//	cout << endl;
//	return 0;
//}

//#include<string>
//int main()
//{
//	string s1("hello world!");
//	for (size_t i = 0; i < s1.size(); ++i)
//	{
//		s1[i]++;
//	}
//	cout << s1 << endl;
//	return 0;
//}

//int A::count  = 0;
//
//template<class T> void Swap(T& x, T& y)
//{
//	T tmp = x;
//	x = y;
//	y = tmp;
//}
//
//int main()
//{
//	int x = 1;
//	int y = 2;
//	Swap(x, y);
//	cout << x<<" "<< y << endl;
//
//	double a = 1;
//	double b = 2;
//	Swap(a, b);
//	cout << a<<" "<< b  << endl;
//	//int* p1 = new int;
//	//int* p2 = new int[0];
//	return 0;
//}

//void fun(const A& aa)
//{
//
//}
//
// int main()
// {
//	 fun(2);
//	 //A a1;
//	 //A a2(1);
//	 //A a3 = 1;
//	 //cout << A::count << endl;
//	 //cout << A::a << endl;
//
//	 return 0;
// }

//class A {
//	int _a;
//
//public:
//	A() {
//		cout << "hello" << endl;
//	}
//	void fun() {};
//	void fun(int a) {_a= a;};
//};
//int main() {
//	A* ptr = nullptr;
//	ptr->fun();
//	//ptr->fun(1);
//	(*ptr).fun() ;
//	return 0;
//}


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


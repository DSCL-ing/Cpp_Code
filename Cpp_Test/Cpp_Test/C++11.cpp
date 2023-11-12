#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"2Date.h"
#include<vector>
#include<list>
#include<map>
#include"10myString.h"
#include"11myVector.h"
#include"12myList.h"

void test3()
{
    test::list<test::string> lt;    //建一个string链表       -- empty_init() -- 空结点也是将匿名对象移动构造
    test::string s1("hello world"); //建一个string对象-- 带参构造
    lt.push_back(s1);               //                       -- 深拷贝 - 测试;
    lt.push_back(test::string("hello world")); //匿名对象    -- 移动构造
    lt.push_back("hello world"); //                          -- 移动构造


    //move测试 -- move需要支持一些内置函数才行,库的可以move,我写的不能move无效,虽然走的是移动构造,但s没有释放掉
    test::list<test::string> lt1;
    test::string s2("hello");
    lt1.push_back(std::move(s2));
    lt1.push_back(std::move(s2));
}

void fun(int& x) { cout << "左值引用" << endl; }
void fun(const int& x) { cout << "const 左值引用" << endl; }
void fun(int&& x) { cout << "右值引用" << endl; }
void fun(const int&& x) { cout << "const 右值引用" << endl; }

template<typename T>
void perfectforward2(T&& t)
{
    fun(t);
}

template<typename T>
void perfectforward1(T&& t)
{
    fun(std::forward<T>(t));
    // std::forward<T>(t)在传参的过程中保持了t的原生类型属性。
}

int main()
{
    perfectforward1(10);
    int a = 1;
    perfectforward1(a);
    perfectforward1(std::move(a));
    const int b = 8;
    perfectforward1(b);
    perfectforward1(std::move(b));
    return 0;
     return 0;

}

//void test1()//移动构造,初识
//{
//    test::list<test::string> lt;    //建一个string链表       -- empty_init() -- 空结点也是将匿名对象移动构造
//    lt.push_back(test::string("hello"));
//    lt.push_back("world");
//}
//
//int main()
//{
//    test1();
//    return 0;
//}

//int main() //测试to_string语法和移动构造
//{
//    int a = -1;    
//    int b = 0-a;
//    std::cout<<b<<std::endl;
//
//    std::cout<<test::to_string(a)<<std::endl; //
//
//    return 0;
//}

//-------------------------------------------------------------------  左值和右值
//void func(const int& a)
//{
//   std::cout<<"左值引用"<<std::endl;
//}
//
//void func(int&& a)
//{
//    std::cout<<"右值引用"<<std::endl;
//}
//
//
//int main()
//{
//    test::string s1 = "hello";
//    test::string s2 = s1+"!";
//    return 0;
//}
//-------------------------------------------------------------------  左值和右值

//------------------------------------------------------------------- 初始化器
//struct Point
//{
//    int _x;
//    int _y;
//};

//void 列表初始化()
//{
//    int x1 = 1;
//    int x2 = { 2 };
//    int x3{ 3 };
//
//    int x4(1); //圆括号初始化可以认为是int的构造
//}
//------------------------------------------------------------------- 初始化器__End






















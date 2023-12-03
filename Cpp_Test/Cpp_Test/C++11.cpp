#define _CRT_SECURE_NO_WARNINGS 1
#include"9Date.h"
#include<vector>
#include<list>
#include<map>
#include"10myString.h"
#include"11myVector.h"
#include"12myList.h"
#include<string>
#include<iostream>
#include<thread>
#include<Windows.h>
#include<vector>
#include<mutex>
#include<time.h>
#include<atomic>
#include<functional>
/* C++11线程库 thread */

class Plus
{
public:
    static int plusi(int a, int b)
    {
        return a + b;
    }
    double plusd(double a, double b)
    {
        return a + b;
    }
};

int main()
{
// 静态成员函数 --- 访问类域去调用,和普通全局函数只是域不同,需要明确指出
    std::function<int(int a ,int b)> f1 = Plus::plusi; 
    
  //非静态成员函数,感觉意义不大了. --- 底层是调用对象来调用 
   std::function<double(Plus,double a, double b)> f2 = &Plus::plusd; //非静态成员函数必须要加&, 原理暂时未知
    f1(1,1);
    f2(Plus(),1,1); // 匿名对象
    Plus p;
    f2( p,1,1); //有名对象
   
    std::function<double(Plus p,double a, double b)> f3 = &Plus::plusd; // 有参数名
    f3(p,1,1);
    
    std::function<double( Plus* ,double a, double b)> f4 = &Plus::plusd; // 也可以是指针
    Plus p2;
    f4(&p2,1,1); //不能用匿名对象,因为匿名对象是右值,不能取地址

    return 0;
}


/*
std::mutex mtx;
int x = 0;
void func()
{
//串行 快很多
    //mtx.lock();
    //for (int i = 0; i < 1000000; i++)
    //{
    //    ++x;
    //}
    //mtx.unlock();


//并发/并发 -- 比串行慢很多
    for (int i = 0; i < 1000000; i++)
    {
        mtx.lock();
        ++x;
        mtx.unlock();
    }

//说明:

}

int main()
{
    size_t begin = clock();
    std::thread t1(func);
    std::thread t2(func);

    t1.join();
    t2.join();

    size_t end = clock();

    std::cout<<end-begin<<std::endl;
    std::cout<<x<<std::endl;
    return 0;
}
*/



/* lambda表达式 */

//struct Goods
//{
//    Goods(const char* str, double price, int evaluate)
//        :_name(str)
//        , _price(price)
//        , _evaluate(evaluate)
//    {}
//
//    std::string _name; //名字
//    double _price; // 价格
//    int _evaluate; // 评价
//};
//
//int main()
//{
//   int x = 1;
//   int y = 2;
//
//   auto obj = [&x,&y]()mutable
//   {
//       int tmp = y;
//       y = x;
//       x = tmp;
//   };
//   
//   obj();
//
//   cout<<y<<endl;
//
//    return 0;
//}






    /* emplace */
//int main()
//{
//    std::list<test::string> lt;
//    lt.push_back(std::move("3333"));
//    lt.emplace_back(std::move("3333"));
//    return 0;
//}


//void showList() //递归的终止条件,拆分到最后,会有一个无参的函数.定义一个无参的函数让递归停止.
//{
//	std::cout << std::endl;
//}
//template <class T, class ...Args>
//void showList(const T& val, Args... args) //每次都将可变参数包的最左1个拆分出来,直到分解完毕.
//{
//	//cout << __FUNCTION__ << "(" << sizeof...(args) << ")" << endl; //__FUNCTION__会替换成当前函数名的字符串
//    cout << typeid(val).name() << " " <<val << " ";
//	showList(args...);
//}
//
//
//
////template<typename ... Args>
////void showList(Args ... args)
////{
////    std::cout<<sizeof ... (args)<<std::endl;
////    for (int i = 0; i < sizeof ... (args); i++)
////    {
////    }
////}
////
//int main()
//{
//    showList();
//    showList('x','y');
//    showList('x',1);
//    showList(1);
//
//    return 0;
//}




         /* 完美转发, forward<T>(t);*/
//void fun(int& x) { cout << "左值引用" << endl; }
//void fun(const int& x) { cout << "const 左值引用" << endl; }
//void fun(int&& x) { cout << "右值引用" << endl; }
//void fun(const int&& x) { cout << "const 右值引用" << endl; }
//
//template<typename T>
//void perfectforward2(T&& t)
//{
//    fun(t);
//}
//
//template<typename T>
//void perfectforward1(T&& t)
//{
//    fun(std::forward<T>(t));
//    // std::forward<T>(t)在传参的过程中保持了t的原生类型属性。
//}
//
//int main()
//{
//    perfectforward1(10);
//    int a = 1;
//    perfectforward1(a);
//    perfectforward1(std::move(a));
//    const int b = 8;
//    perfectforward1(b);
//    perfectforward1(std::move(b));
//    return 0;
//     return 0;
//
//}

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






















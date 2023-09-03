﻿#pragma once

/** C++11
 * 
 * 默认成员函数
原来C++类中，有6个默认成员函数：
1. 构造函数
2. 析构函数
3. 拷贝构造函数
4. 拷贝赋值重载
5. 取地址重载
6. const 取地址重载
最后重要的是前4个，后两个用处不大。默认成员函数就是我们不写编译器会生成一个默认的。
 * 
 * C++11新增了两个构造函数,分别是
 * 1.移动构造
 * 2.赋值运算符重载
 * 
 * 但他们自动生成的条件非常苛刻:
 * 1. 如果你没有自己实现移动构造函数，且没有实现析构函数 、拷贝构造、拷贝赋值重载中的任意一个。那么编译器会自动生成一个默认移动构造。 
 * -- 实现任意一个都不行? 对,只要实现到其中1个或以上都不会自动生成
 * (原因:如果我们实现了析构,拷贝,赋值,说明这个类是深拷贝类,即这个类是由我们来决定资源如何转移,而不是由编译器控制)
 * 2. 默认生成的移动构造函数，对于内置类型成员会执行逐成员按字节拷贝，自定义类型成员，则需要看这个成员是否实现移动构造，
 *    如果实现了就调用移动构造，没有实现就调用拷贝构造。
 * -- 一样的,只要3个中出现一个都不生成
 * 
 * 
 * 强制生成默认的移动构造
 * A(A&& a) = default;
 * A& operator=(A&& a) = default;
 * 
 * 
 */

//类成员变量初始化
/**
 * C++11允许在类定义时给成员变量初始缺省值，默认生成构造函数会使用这些缺省值初始化 -- 缺省参数
 */


//关键字default -- 强制生成默认的构造函数
/**
 * 
 * C++11可以让你更好的控制要使用的默认函数。假设你要使用某个默认的函数，但是因为一些原因这个函数没有默认生成。
 * 比如：我们提供了拷贝构造，就不会生成移动构造了，那么我们可以使用default关键字显示指定移动构造生成。
 * 强制生成默认的移动构造
 * A(A&& a) = default;
 * A& operator=(A&& a) = default;
 * 
 */

/**禁止生成默认函数的关键字delete:
 * 
 * 如果能想要限制某些默认函数的生成，在C++98中，是该函数设置成private，并且只声明补丁
 * 已，这样只要其他人想要调用就会报错。在C++11中更简单，只需在该函数声明加上 = delete即
 * 可，该语法指示编译器不生成对应函数的默认版本，称 = delete修饰的函数为删除函数。
 * 
 * 
 */

//继承和多态中的final与override关键字
/**
 * //...
 */

//委托构造 -- 可读性下降,不提倡
/**
 * 委托构造函数也是一种构造函数，这种构造函数可以委托其他构造函数来帮它完成一些对象成员的初始化操作。
 * 一个构造函数可以调用其他构造函数
 */
/*class Person
{
public:
	Person(const char* name, int age)
		:_name(name)
		, _age(age)
	{}
	Person(const char* name)  //委托构造
		:Person(name, 18)  
	{}
private:
	string _name;
	int _age;
};*/







//可变参数模板
/**
 * 起源:C语言的printf()
 * int printf ( const char * format, ... ); //这三个点...就是可变参数
 * C语言底层是编译器开了一个参数数组,三个参数就存三个空间,四个参数就存4个...
 * 
 * C++11的新特性可变参数模板能够让您创建可以接受可变参数的函数模板和类模板，相比
 * C++98 / 03，类模版和函数模版中只能含固定数量的模版参数，可变模版参数无疑是一个巨大的改
 * 进。然而由于可变模版参数比较抽象，使用起来需要一定的技巧，所以这块还是比较晦涩的。现
 * 阶段呢，掌握一些基础的可变参数模板特性就够用了，所以这里点到为止，以后如果有需要再深入学习。
 * 
 * 
 * Args是一个模板参数包，args是一个函数形参参数包  
 * 声明一个参数包Args...args，这个参数包中可以包含0到任意个模板参数,代表的就是0到任意个参数。
 * 
 * -----  (注:args是个名称,可以任意取,习惯写成args)  
 * -----  (参数包写法为Args... 命名) (类似类型写法T t)
 * 
 * 可变参数模板使用场景:线程  -- 线程库:<thread> --C++11
 * 
 */


 // 如何解析出可变参数包呢？
 // 递归推导思维
void ShowList()
{
	cout << endl;
	//cout << sizeof...(args) << endl; //规定这么写
}
template <class T, class ...Args>
void ShowList(const T& val, Args... args)
{
	cout << __FUNCTION__ << "(" << sizeof...(args) << ")" << endl; //__FUNCTION__会替换成当前函数名的字符串

	//cout << val << " ";
	ShowList(args...);
}


void fun1()
{
	//ShowList();  //不限制类型,传任何类型,多少个都可以
	//ShowList('x');
	//ShowList('x','y');
	//ShowList('x',1);
	ShowList(1, 'A', std::string("sort"));
}





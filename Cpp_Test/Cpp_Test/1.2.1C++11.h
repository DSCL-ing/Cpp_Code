﻿#pragma once

#include<iostream>
#include<vector> 
#include<list>
#include"10myString.h"
#include"11myVector.h"
#include"12myList.h"
#include"9Date.h"
#include <map>

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
 * 2.移动赋值
 * 
 * 但他们自动生成的条件非常苛刻:
 * 1. 如果你没有自己实现移动构造函数，且没有实现析构函数 、拷贝构造、拷贝赋值。那么编译器会自动生成一个默认移动构造。 
 * -- 实现一个都不行? 对,只要实现到其中1个或以上都不会自动生成
 *   原因:
 *		如果我们重载了析构,拷贝,赋值,就说明这个类是需要深拷贝的,那这个类最好是由我来决定资源如何转移,而不是由编译器控制,以免出现意想不到的结果       
 *      
 * 2. 默认生成的移动构造函数，对于内置类型成员会逐字节拷贝(值拷贝)，
 *      对于自定义类型成员，如果该自定义类型内实现了移动构造,就调用他的移动构造,没有实现就调用他的拷贝构造。
 *      --- 默认生成的移动构造,需要自定义类型实现了移动构造才能发生移动,其他都是值拷贝或深拷贝...
 * 
 *
 * 
 * 
 * 
 *  
 * 强制生成默认的移动构造
 * A(A&& a) = default;
 * A& operator=(A&& a) = default;
 * 
 * 
 */

//类成员变量初始化 -- 缺省值
/**
 * C++11允许在类定义时给成员变量初始缺省值，默认生成构造函数会使用这些缺省值初始化 -- 缺省参数
 *  补足对内置类型默认不处理的缺陷
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
 * 1.如果能想要限制某些默认函数的生成，在C++98中，使该函数设置成private，并且只声明 ，这样只要其他人想要调用就会报错。 --- 不够明确/清晰
 * 2.在C++11中更简单，只需在该函数声明加上 = delete即可，该语法指示编译器不生成对应函数的默认版本，
 *    称 = delete修饰的函数为删除函数。 -- 更清晰明确
 * 哪些对象不希望被拷贝,被移动? -- 1.I/O流 2.单例模式...
 * 
 */

//继承和多态中的final与override关键字
/**
 * final: -- 修饰基类,父类
 * 1.final可以修饰一个类,使其不能被继承.
 * 2.final还可以修饰成员函数,使其不能被重写.
 * 
 * override: --- 修饰派生类
 * 1.override用于修饰派生类的虚函数.检查是否完成重写.
 * 
 * 
 * 什么情况下子类必须重写虚函数 --- 规定:纯虚函数的子孙类必须至少有一个重写纯虚函数.
 * 
 * 
 */

//委托构造 -- 可读性差点,意义不大,只提高了复用性.但可以不使用,可有可无
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
		:Person(name, 18)   // ---- 借用已有的构造函数来帮助构造,初始化
	{}
private:
	string _name;
	int _age;
};*/



//C++ 11是如何封装Thread库的？ - 知乎
//https ://www.zhihu.com/question/30553807



//可变参数模板 --- 记忆:声明时:三个点,在中间. 单独使用时,三个点,在后边. --- 特例,sizeof是宏,所以三个点,在中间
/**
 * 起源:C语言的printf()
 * int printf ( const char * format, ... ); //这三个点...就是可变参数
 *  
 * C++11的新特性可变参数模板能够让您创建可以接受可变参数的函数模板和类模板，相比
 * C++98 / 03，类模版和函数模版中只能含固定数量的模版参数，可变模版参数无疑是一个巨大的改
 * 进。然而由于可变模版参数比较抽象，使用起来需要一定的技巧，所以这块还是比较晦涩的。 
 *   
 * Args是一个模板参数包，args是一个函数形参参数包  
 * 声明一个参数包Args ... args，这个参数包中可以包含0到任意个模板参数,代表的就是0到任意个参数。
 * 
 * -----  (注:args是个名称,可以任意取,习惯写成args)  
 * -----  (参数包写法为Args ... 命名) (类似类型写法T t)
 * 
 * 可变参数模板使用场景:线程  -- 线程库:<thread> --C++11
 * (线程:我们需要分配不同任务给不同线程去执行.不同任务有不用需求和情况---> 因此需要支持多种类型)	
 * 1.C语言通过使用 void*传参,然后强转成需要的类型, 来解决不同类型的问题. 无参数传null,1个参数直接传void*,多个参数就放在一个结构体内再传void*
 * 2.C++11使用了一个类去封装线程.(C++不限于函数,还可以是可执行对象,如仿函数等...) , 
 *	   这个类使用了可变参数包,可以传任意个类型.用的时候再解析出来.
 *  
 * 可变参数模板主要是为库准备的 -- 我们目前先了解了解
 * 
 * 容器中都有一个emplace系列
 * 特点:
 * 1.可以传多个参数,传一个参数时和其他同样参数的函数功能一样,如push_back和emplace_back 效率基本一样  但底层实现不一样
 * 2.emplace有直接构造情况... 只要传构造函数的参数,可变参数包就会自动推导到相应构造函数-->直接构造
 * 
 * emplace确实有优化,可以多使用
 * 
 * 一些工具使用:
 * 1.支持sizeof ... (函数形参参数包)   
 * 2.不支持typeid().name().
 * 
 * 需要将可变参数解析出来才能使用可变参数 ,有几种拆解方法
 * 1.   ---> 递归拆解... ,套壳递归拆解等 
 * 2.
 * 
 * 
 *   
 */

/* 打印刻板参数包中 参数(类型) 个数 */
template<typename ... Args> //三个点中间
void showList(Args ... args)
{
	std::cout << sizeof ... (args) << std::endl; //打印有多少个类型
}

int man()
{
	showList();
	showList('x', 'y');
	showList('x', '1');
	showList(1);

	return 0;
}

// ---------------------------------------------------------------

 /* 解析出可变参数包  */
 // 递归,将可变参数包拆解.分而治之
void showList() //递归的终止条件,拆分到最后,会有一个无参的函数.定义一个无参的函数让递归停止. --- 递归出口
{
	std::cout << std::endl;
}
template <class T, class ...Args>
void showList(const T& val, Args... args) //每次都将可变参数包的最左1个拆分出来,直到分解完毕.
{
	//cout << __FUNCTION__ << "(" << sizeof...(args) << ")" << endl; //__FUNCTION__会替换成当前函数名的字符串

	cout << typeid(val).name()<<" " <<val << " "; // 打印出 类型 和 值 
	ShowList(args...);
}

 /* 解析出可变参数包 ,法二 */
 /**
  * 解析参数包法是常用的方法,通过多层调用可以依次将参数分离出来
  */
 template<typename T>
 int PrintArg(T&& t)  //由于编译器会生成很多份函数.如果使用直接传参(拷贝),则开销会非常大.所以一般会使用引用,引用折叠等...
 {
	 cout<<t<<" ";
	 return 0; //用于数组初始化为0
 }
 template<typename ... Args>
 void ShowList(Args ... args)
 {
     int arr[] = { PrintArg(args) ... };//此处只写args,意义类似拆解,拆一个参数出来.剩下的就在 三个点 ... 中. --- 编译器自动解析
										//函数可以是任意的.看需求使用
	// 编译器实际生成类似于 int arr[] = { func(args1),func(args2),func(args3), ...);
 }

/* //逗号表达式写法,两种写法一样
 template<typename T>
 void PrintArg(T t) //直接传参.开销很大... 不推荐
 {
	 cout << t << " ";
 }
 template<typename ... Args>
 void ShowList(Args ... args)
 {
    int arr[] = { (PrintArg(args),0) ... }; //如果函数不带返回值,可以用逗号表达式,取最后一个为返回值,也是用于初始化数组为0
 }
*/




// emplace
/** 
 * C++11 给STL容器都增加了emplace操作
 * 如果是push_back/push_front,则对应增加emplace_bask /emplace_front
 * 如果是insert , 则对应增加emplace
 * 
 * emplace系列支持了可变参数包和引用折叠.如insert和push支持的emplace基本也支持
 *   --> 可以同时使用inset/push和emplace. //插入相同对象时,功能基本没有区别
 * 
 * 区别点:
 * 1.一定情况下,可以实现直接构造,直接使用参数在自己的对象内构造 -- 跳过如(先构造匿名对象,再移动构造)  --- 高效体现,深拷贝差不多,快一丢丢
 * 2.浅拷贝的类效率高会明显 
 */

 /* 测试emplace区别 */
 int man()
 {
	 std::list<test::string> lt;
	 lt.push_back(std::move("3333"));
	 lt.emplace_back(std::move("3333"));
	 return 0;
 }
/*
 结果:
 string(const char* s) --左值, 默认构造
 string(string&& s) --移动拷贝

 string(const char* s) --左值, 默认构造 --- emplace直接构造
 //深拷贝只快一点点,因为构造+移动构造 和直接构造差不多
 //原因分析: 
 1.push_back是隐式类型转换,模板推导出来类型是string,所以由char*构造成string再push.
 2.emplace_back是由可变参数包直接推导成char*,然后直接构造 -- 直接拿参数包去构造参数 -- emplace是传什么就是什么,直接干,
	通过拆分法依次拆分,直至解析,最后通过定位new调用对象的构造函数::new((void*)_Ptr) _Objty(forword((_Args)...) 实现构造

* emplace从实例化的参数类型(模板类型),能直接接收参数在emplace内构造.
 //浅拷贝,直接传参数给emplace能够少一次构造
	
*/






// lambda表达式
/**

引入: 
1.C++98中,要定义排序的比较规则时,使用函数指针或函数对象(模板中)
 
2. 随着C++语法的发展，人们开始觉得上面的写法太复杂了，每次为了实现一个algorithm算法，
    都要重新去写一个类，如果每次比较的逻辑不一样，还要去实现多个类，特别是相同类的命名，
    这些都给编程者带来了极大的不便。因此，在C++11语法中出现了Lambda表达式。 
  
 
lambda表达式语法
lambda表达式书写格式：[capture-list] (parameters) mutable -> return-type { statement
}
1. lambda表达式各部分说明

a. [capture-list] : 捕捉列表，该列表总是出现在lambda函数的开始位置，编译器根据[]来
	判断接下来的代码是否为lambda函数，捕捉列表能够捕捉上下文中的变量供lambda函数使用。
\语法1 -- 传值捕获: 
	int x;
	int y;
	auto obj = [x,y] () mutable -> int { return x + y ;} ; // ---- 捕捉多个值时使用逗号分割
注意:
1. 传值捕获内的参数是外界的拷贝,不会影响到外界的
2. mutable用法
	a. 不使用mutable时(默认是不使用),传值捕获列表的参数是无法被修改的.如果有修改行为,则编译器会报错 --- 相当于const形参
		-- 目的是防止我们误用
	b. 使用 mutable后,捕捉列表的参数就可以修改了 -- 相当于去掉const的形参
		注:传值捕捉列表的参数是不能影响到外界的,因为他只是拷贝,使用mutable也不行	
// 很少使用传值捕获

\语法2 -- 引用捕获列表:
	int x;
	int y;
	auto obj = [&x,&y]()mutable  //mutable对引用捕捉中捕捉到的对象无效了,加不加都能修改引用的对象
	{
		int tmp = x;
		x = y;
		y = tmp;
	};
注意:
	此处的&不是取地址,而是引用.在传统C++中, "&名字" 是取地址,只有 "类型&名字" 才是引用. 而在lambda中 "&名字" 就是引用
// 最常用

\语法3 -- 混合捕捉:
	int x;
	int y;
	auto obj = [x,&y](){};

\语法4 -- 全部传值捕捉
	int x,y;
	int m,n;
	auto obj = [=](){};

\语法5 -- 全部引用捕捉
	int x,y,m,n;
	auto obj = [&](){};

\语法5 -- 部分引用捕捉,其他全部传值捕捉
	int x,y,m,n;
	auto obj = [=,&x]();

\语法6 -- 部分传值捕捉,其他全部传引用捕捉
	int x,y,m,n;
	auto obj = [&,y]();

注1: 不允许全部捕捉后,再捕捉相同类型的对象,如:
	int x,y,m,n;
	auto obj = [=,x]();  // 错误,不允许
	auto obj = [&,&x](); // 错误,不允许
注2: 不允许全部传值捕捉和全部传引用捕捉同时存在,如:
	auto objj = [=,&]();
	// 原因, 前后矛盾,编译器无法识别 --- 不允许有矛盾的语法存在

\语法7 -- [this]：表示值传递方式捕捉当前的this指针 (成员函数中自动隐式捕获this)

lambda表达是在成员函数的作用域内定义时，它隐式地拥有一个指向当前对象的this指针。因此，即使在lambda表达式中没有显式地捕获任何变量，它仍然能够访问当前对象的成员变量，包括私有和公有成员。这是因为this指针被隐式地传递给了lambda表达式，使得它可以访问当前对象的状态。
这种能力是C++ lambda表达式设计的一部分，旨在方便在类的成员函数中使用lambda表达式。然而，这种便利也带来了一定的风险，因为在没有显式捕获的情况下，lambda表达式对成员变量的修改可能会影响到对象的状态。


b. (parameters)：参数列表。与普通函数的参数列表一致，如果不需要参数传递，则可以连同()一起省略

c. mutable：默认情况下，lambda函数总是一个const函数，mutable可以取消其常量性。使用该修饰符时，参数列表不可省略(即使参数为空)。

d. ->returntype：返回值类型。用追踪返回类型形式声明函数的返回值类型，没有返回值时此部分可省略。
	返回值类型明确情况下，也可省略，由编译器对返回类型进行推导。

e. {statement}：函数体。在该函数体内，除了可以使用其参数外，还可以使用所有捕获到的变量。


注意：
1.在lambda函数定义中，参数列表和返回值类型都是可选部分，而捕捉列表和函数体可以为
空。因此C++11中最简单的lambda函数为：[]{}; 该lambda函数不能做任何事情。
2.lambda表达式虽然能定义在函数(main)内,但是lambda表达式函数体内并不能"直接"访问/使用外部的变量,不像if(){}这样可以使用
    ---> lambda函数体是独立的作用域
3.如果lambda需要访问外部的变量,则需要使用捕捉列表[] --- capture-list	
\语法:
	int x;
	int y;
	auto obj = [x,y]{ return x + y ;} ; // ---- 捕捉多个值时使用逗号分割

4.如果捕获列表的参数和lambda参数列表同名,会优先使用lambda自己的
	优先级:  lambda-parameter > capture-list



 功能:
 lambda表达式一般用于替代仿函数

 好处:
 1.代码简洁明了,能够一眼看清代码的目的和功能(仿函数代码和示例分离太远,找起来很烦).
 2.引用捕获后传给线程,bind等对象时,可以不使用std::ref直接传递
  
 
认识lambda;
lambda表达式能够快速定义一个具有函数功能的对象,很方便

lambda的原理:
lambda是一个没有成员,只有函数的空类 ---> sizeof(lambda对象):1 //lambda大小为1 ---> 没有成员的空类大小就是1

底层原理:运行以下代码 -- 反汇编调试观察函数对象部分和lambda调用部分,可以发现几乎一样 ---- 说明lambda底层实现和函数对象,一样,
class Rate //率
{
public:
	Rate(double rate) : _rate(rate)
	{}
	double operator()(double money, int year)
	{
		return money * _rate * year;
	}
private:
	double _rate;
};


int main()
{
	Rate r1(0.1);
	r1(10000,1);

	auto AAAA = [](int money,double rate,int year)
	{
		return money * rate * year;
	};
	AAAA(10000,0.1,1);


	return 0 ;
}

lambda之间不能相互赋值,就算是完全相同的代码生成的lanbda对象也不行;
原因:大致是每次生成的lambda对象都是唯一的,属于不同的类...,具体需要研究编译器  ----  UUID: <lambda_8ce8db8d48129b9a466073125411eb2b>


 */



/* C++11 线程库 */
/*
1. linux中pthread是POSIX标准(可移植线程库). windows是winAPI...
2. 如果一份代码想同时在linux和windows下运行,C++11以前的处理方法是"条件编译"
#ifdef _WIN32
	CreateThread();
#else
	phread_create();
#endif

3. C++封装了一个linux和window下都可以支持的多线程库 --- thread库
	-- 只要支持C++11都必须要支持thread库
	-- 内部实现也是条件编译,由库去替我们维护条件编译.提高开发效率
	-- 这个库封装成类 --- 面向对象

构造函数:
1. thread() noexcept;
无参构造,用于创建多线程,如容器创建多个对象,默认会调用无参的构造函数

2.常规创建
template <class Fn, class... Args>
explicit thread (Fn&& fn, Args&&... args);
注:Fn是可调用对象,不限于仿函数对象,函数指针,lambda

3.不允许拷贝构造 -- 没意义,不如重新构造一个新的
thread (const thread&) = delete;

4.移动构造 -- 允许资源转移
thread (thread&& x) noexcept;

赋值重载:
a.允许移动赋值 -- 资源转移
thread& operator= (thread&& rhs) noexcept;
b.禁止拷贝赋值
thread& operator= (const thread&) = delete;

//!定义成员线程的方法
a.使用指针在堆上定义,
b.使用数据结构定义多个空线程,需要时再移动构造

// !thread为了跨平台,把一些成员对象如id给封装成类,其他和POXIS用法差不多,多练习熟练
// thd.get_id(); //thread == thd


C++将线程封装成类后,使用线程前必须要构造出线程类. 
--- 但是如果在构造过程中需要使用线程的方法,如thread([](){get_id();}; ,直接使用会报错
原因: 此时类还在构造中,提供不了get_id()方法
解决: C++另外提供了一个类this_thread,它位于命名空间std中,这个类提供了get_id()方法.
	通过调用std::this_thread.get_id();即可


#include <chrono>
std::this_thread::sleep_for (std::chrono::seconds(1));// chronometer 精密计时器

Yield;让步
std::this_thread::yield(); // 主动让出时间片
应用场景: 无锁编程(尽可能少使用锁) ---- 无锁编程 ,因为加锁效率太低,而搞出来的无锁编程思想


扩展知识: --- 没有系统学习,比较混乱 
//操作系统CAS ... --- 原子操作的本质
//https://coolshell.cn/articles/8239.html //无锁队列的实现
//https://coolshell.cn/articles/9703.html //无锁hashMap
/*
结构举例:
int old,i;
//while (__sync_bool_compare_and_swap(type *ptr, type oldval type newval)) //要修改的值,旧值,改成多少 
	--- 原理:要修改的值和旧值进行比较,如果相等就可以修改(说明没有被别的线程修改).如果不等就不能修改,返回false
while (__sync_bool_compare_and_swap(&i, old, old + 1))
{
	old = i; //更新旧值 --- 如果不相等,就不能修改,说明值已经改变了.然后更新旧值,进入下一轮循环去判断
}

  常见有1.资源数量,使用原子操作 2.队列,先判断tail->next为不为空,再新增.保证原子插入...j

而当某一线程长时间做想做某事而无法成功时,就需要主动让出CPU资源,不浪费资源,此时就需要使用到yield
举例:如一个线程刚好在对hash表扩容,而另一个线程刚好在这个hash值处插入而插不进去.此时执行插入操作的线程就应该让出CPU资源而不是一直循环尝试
		--- 预测到有这种行为时,就可以使用yield接口

*/

//!线程传引用
/*
thread不可以直接传引用,直接传会替换成拷贝或者报错
需要使用<functional>中的 std::ref(引用的对象) 辅助传递
*/

//多线程失效
/*
1.srand()仅在当前线程生效,如果在主线程(如main)使用就仅在主线程生效,对其他线程无效,多线程独立,其他线程默认会重srand(1)开始

*/

//线程安全 
/*

*/

/**
 * 1.thread提供的模板参数能接收函数
 * 2.thread提供的模板参数能接收lambda表达式
 */
 //void func(int num)
 //{
 //    while (1)
 //    {
 //        std::cout<<"我是子线程"<< num <<std::endl;
 //        Sleep(1000);
 //    }
 // }
 //
 //int main()
 //{
 //    //std::thread t1(func,1);
 //    //std::thread t2(func,2);
 //
 //    std::thread t1([](int num)
 //        {
 //            while (1)
 //            {
 //                std::cout << "我是子线程" << num << std::endl;
 //                Sleep(1000);
 //            }
 //        },1);
 //    std::thread t2([](int num)
 //        {
 //            while (1)
 //            {
 //                std::cout << "我是子线程" << num << std::endl;
 //                Sleep(1000);
 //            }
 //        }, 2);
 //
 //
 //    t1.join();
 //    t2.join();
 //
 //    return 0;
 //}

/**
 *---------------------------------------------------------------- 1.使用容器管理线程,并配合使用lambda表达式
int main()
{
    size_t m; //定义管理线程的vector的大小.
    cin >> m;
    std::vector<std::thread> vthds(m);  // vector threads

    for (size_t i = 0; i < m; ++i)
    {
        size_t n; //每个线程执行的次数
        cin >> n;
        vthds[i] = std::thread([i,n]() {
            for (size_t j = 0; j < n; j++)
            {
                cout<<"thread: "<<i << "," << j << std::endl;
            }
            cout<<endl;
            });
    }

    for (auto& v : vthds)
    {
        v.join();
    }
    
    return 0;
}
 ---------------------------------------------------------------- 1.使用容器管理线程, 并配合使用lambda表达式 */

//bug
/*

*/



 //C++11 <mutex>
/**

C++11提供了4种锁
 Mutexes Classes
1. mutex                   Mutex class (class ) //常规锁
2. recursive_mutex 	    Recursive mutex class (class ) //递归锁
	递归锁用于在递归的下一个栈帧时,能够判断出是当前线程加的锁,允许当前进程越过锁继续访问临界资源
场景:
void func(int n)
{
	if (n == 0)
	{
		return ;
	}
	mtx.lock();
	x++;
	mtx.unlock();
	func(n-1);
}

3. timed_mutex             Timed mutex class (class )
// !提供加锁一定时间后自动解锁的功能
// $lock		     Lock timed mutex (public member function )
// $try_lock         Lock timed mutex if not locked (public member function )
// $try_lock_for     Try to lock for time span (public member function ) //%经过一段时间
// $try_lock_until   Try to lock until time point (public member function ) //%定时到某一时刻

4. recursive_timed_mutex   Recursive timed mutex (class )


 * C++11 也提供锁,也封装成了类 mutex
 * 成员函数:
 * 1.构造
  
  2.lock
  
  3.unlock
  
  4.tryLock
   ...

// C++提供的所有锁没有移动构造和拷贝构造   1.不允许赋值,因为拷贝后都不是同一把锁了,没有意义. 2.不允许移动,因为移动后,类销毁锁就没了,没有意义
default (1)            constexpr mutex() noexcept;
copy [deleted] (2)     mutex (const mutex&) = delete;


C++线程不能直接传引用 --- 与底层实现和封装,右值引用和完美转发等..有关系
	解决:要使用库提供std::ref函数传递引用
std::mutex mtx;
std::thread t1(Func, std::ref(mtx));
 
  
 * * 注意1:并行/并发 不一定 比串行快. 要看消耗和产出比. 
 
验证:
--------------------------------------------------------------------- 验证串行比加锁并行快的场景
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


//并发/并发 -- 比串行慢很多  \\原因: ++x执行太快,切换太频繁 
	//for (int i = 0; i < 1000000; i++)
	//{
	//	mtx.lock();
	//	++x;
	//	mtx.unlock();
	//}

//说明:
加锁解锁和上下文切换 很占用资源.


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

--------------------------------------------------------------------- 验证串行比加锁并行快的场景____End



//!守护锁

C++11提供了守护锁类
lock_guard        //class templace
unique_lock       //class templace
//区别,lock_guard只有自动上锁解锁; unique_lock不只有自动上锁解锁,还提供了手动上锁和解锁 ---- 有些场景需要...


场景1 : 如果使用了一般的加锁解锁方式,在封锁的区域内发生了异常,则会跳到catch中,没有经过unlock,导致下次访问临界区就会死锁
解决方法之一就是使用守护锁.
--------------------------------------------------------------- 模拟实现守护锁
std::mutex mtx;
int x = 0;
template<typename Lock>
class LockGuard
{
public:
    LockGuard(Lock& lk) :_lk(lk)
    {
        _lk.lock();
    }
    ~LockGuard()
    {
        _lk.unlock();
    }
private:
    Lock& _lk;
};

void func(int n)
{
    for (int i = 0; i < n; i++)
    {
        try {
            //LockGuard<std::mutex> lockGuard(mtx); //!RAII风格的锁
            mtx.lock();
            x++;
            if (rand() % 3 == 0)
            {
                throw std::exception("抛异常");
            }
            mtx.unlock();
        }
        catch (const std::exception& e)
        {
            std::cout<<e.what()<<std::endl;
        }
    }
}
--------------------------------------------------------------- 模拟实现守护锁__End;


  

 *  
 */



//C++11 还提供了 atomic 原子操作 ...(了解,目前主要使用常用部分)
/*

底层都是CAS

atomic      // Atomic (class template ) ---  常用
//https://legacy.cplusplus.com/reference/atomic/atomic/

----------------------------------------------------------------  atomic用法
std::mutex mtx;
//int x = 0;
//std::atomic<int> x = 0;
//std::atomic<int> x(0);
std::atomic<int> x{0};     //无需加锁,operater操作都重载了原子

void func(int n)
{
	for (int i = 0; i < n; i++)
	{
			x++;
	}
}

int main()
{
	std::thread t1(func, 10000);
	std::thread t2(func, 10000);

	t1.join();
	t2.join();

	std::cout << x << std::endl;

	//return 0;
}
----------------------------------------------------------------  atomic用法__End

成员方法:
1.load()
	用于加载出原类型. // std::atomic<int> x{0};  printf("%d",x.load());
2.store();
	原子替换原来的值...
...

*/



//C++11 condition_variable
/*

wait(unique_lock lock) :休眠自己,且休眠前解锁(unique提供的解锁操作) 

notify_one() :随机唤醒一个休眠的线程,如果没有休眠的线程,那什么都不做

notify_all :唤醒所有


// 两个线程,一个打印奇数,一个打印偶数,按顺序依次打印,到n结束
// 目的: 使用条件变量控制线程分别执行任务.  单纯这道题,也可以使用if+while等待搞定.
std::mutex mtx;
std::condition_variable cv;

int main()
{
	int x = 1;
	int n = 100;
	std::thread t1([&,n]() {
		while(x<n)
		{
			std::unique_lock<std::mutex> lock(mtx); //
			if (x % 2 != 1) //1.拦住奇数
			{
				cv.wait(lock); // 让自己休眠,在休眠前释放锁.
			}
			std::cout << std::this_thread::get_id() << ":" << x++ << std::endl;
			cv.notify_one(); //2.如果自己成功执行到了任务,则唤醒别的线程.下次自己必定会休眠.出了作用域后会释放锁,
			//a.如果是自己先运行,说明另一线程必定在等待锁释放.因此唤醒功能没用.解锁才有用(让另一线程跑起来)
			//b.如果是线程2先运行,说明线程2一定是休眠状态 : 线程2先运行,先加锁,判断是奇数后,释放锁,并进入休眠状态,
			//  此时线程1唤醒功能就其效果了,唤醒线程2,执行完任务,直到进入休眠
		}
		});

	std::thread t2([&,n]() {
		while(x<n)
		{
			{
				std::unique_lock<std::mutex> lock(mtx);
				//if (x % 2 != 0)
				//{
				//    cv.wait(lock);
				// }
				cv.wait(lock,[&x]()->bool{return x%2 == 0;}); //false就会阻塞,直到条件为真才能继续向下
				std::cout << std::this_thread::get_id() << ":" << x++ << std::endl;
			} //加不加都无所谓的代码块.因为是临界资源使用结束后再进行别的操作. --- 主要是保护临界资源
				cv.notify_one();
		}
		});

	t1.join();
	t2.join();

	std::cout << x << std::endl;

	//return 0;
}

*/


//包装器 --- 对可调用对象类型进行再封装适配
/*
bind和function都是包装器


function包装器 也叫作适配器。
C++中的function是一个类模板，底层是函数对象。

//!为什么需要function?      
 例子  ret = func(x);
 上面func可能是函数名,函数指针,函数对象(仿函数对象),也有可能 是lamber表达式对象.
所以这些都是可调用的类型！如此丰富的类型，可能会导致模板的效率低下！
为什么呢？我们继续往下看
-------------------------------------------------------------------- 一般的可调用对象.
template<class F, class T>                //函数模板
T useF(F f, T x) 
{
 static int count = 0;
 cout << "count:" << ++count << endl;
 cout << "count:" << &count << endl;
 return f(x);
}

double f(double i)                        //函数
{
 return i / 2;
 }

struct Functor                            //函数对象
{
 double operator()(double d)
 {
 return d / 3;
 }
};

int main()
{
 cout << useF(f, 11.11) << endl;//  函数名
 
 cout << useF(Functor(), 11.11) << endl;// 函数对象
 
 cout << useF([](double d)->double{ return d/4; }, 11.11) << endl;//lamber表达式
 
 return 0; 
 }

-------------------------------------------------------------------- 一般的可调用对象.




std::function在头文件<functional>
// 类模板原型如下
template <class Ret, class... Args>
class function<Ret(Args...)>;
模板参数说明：
Ret: 被调用函数的返回类型
Args…：被调用函数的形参

---------------------------------------------------------------------------  function的常规使用
int func(int x,int y)
{
    std::cout<<"func(int x,int y) " <<  "  ";
    return x+y;
}

struct Functor
{
    int operator()(int x, int y)
    {
    std::cout<<" operator()(int x, int y) " << "  ";
        return x+y;
    }
};

int main() //
{
    std::function<int(int,int)> f1 = func;
    std::function<int(int,int)> f2 = Functor();
    std::function<int(int, int)> f3 = [](int x, int y) {
    std::cout<<"  [](int x, int y) " << "  ";
        return x+y;
    };

    cout<<f1(1,1)<<std::endl;
    cout<<f2(1,1)<<std::endl;
    cout<<f3(1,1)<<std::endl;


    return 0;
}

int main()
{
	//常用于 指令 <==> 函数  (指令对应函数) 时的写法
	//如switch, if()_do();  映射
	std::map<std::string,std::function<int(int,int)>> opFuncMap; //算子函数Map
	opFuncMap["函数指针"] = func;
	opFuncMap["Functor"]  = Functor();
	opFuncMap["lambda"] = [](int x, int y) {
		std::cout<<" [](int x, int y)  ";
		return x+y;
	};

	std::cout<<opFuncMap["函数指针"](1,1)<<std::endl;
	std::cout<<opFuncMap["Functor"](1,1)<<std::endl;
	std::cout<<opFuncMap["lambda"](1,1)<<std::endl;
	return 0;
}

---------------------------------------------------------------------------  function的使用__End


包装之后类型一样,但调用的还是各自的原型 ---> 统一类型,能够接收各种类型的函数对象


-----------------------------------------------------------------------------  包装成员函数
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
// !静态成员函数 --- 访问类域去调用,和普通全局函数只是域不同,需要明确指出
    std::function<int(int a ,int b)> f1 = Plus::plusi; 
    
  //!非静态成员函数 --- 底层是调用对象来调用 
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
-----------------------------------------------------------------------------  包装成员函数__End



*/


//bind
/*
<functional>
绑定bind    //容易出现ambiguous,建议用别的替代

//将某个参数绑定,固定,可以隐藏 和 减少参数个数.
//用法1. 调整参数位置
//用法2. 固定1个或多个参数,返回一个参数更少的包装器(函数)对象.

//使用:如果要将某个函数作为参数,并且需要把该函数的所有参数传递进去,使用bind会非常方便
// Task t(sock,clientip,clientport,std::bind(&TCPServer::service,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));

1.
template <class Fn, class... Args> 
   bind(Fn&& fn, Args&&... args);
2.	
template <class Ret, class Fn, class... Args> 
   bind <Ret> (Fn && fn, Args&&... args);


// 原型auto opFunc = std::bind(Fn,需要固定的参数1,需要固定参数2,..., 固定后剩余参数1号, 固定后剩余参数2号);
//     auto opFunc = std::bind(Fn,Paramet1,Paramet2, ... ,placeholders::_1,placeholders::_2 ...)
// 注: 固定后剩余参数1号 == std::placeholders::_1 .

// 剩余参数所在的位置就是剩余参数传递的位置
// 如: void fun(int a, string b,char c);
// auto rfun = std::bind(fun,1,std::placeholders::_2,std::placeholders::_1)
// rfun('c',"b"); 

// auto opFunc = std::bind<int>(Fn,Raramet...) //指定返回值类型


//返回值:std::function<T1(T2)> func = std::bind(fun_name,parameter...)
//!返回值由调用对象决定

//!如果Fn是成员函数,则和function一样.需要加&
例:std::bind(&Class::func,this,parameter...);

//如果需要替换参数位置,则
   实例auto opFunc = std::bind(Fn,Paramet1,Paramet2, ... ,placeholders::_2,placeholders::_1 ...)

// 从Fn之后开始,每个参数都会对应Fn需要的参数.非placeholders的,代表固定的参数(需要绑定的,隐藏的参数)
   placeholders::_1代表传入的第一个参数._2代表传入的第二个参数,... ,依次往后
   placeholders的位置代表传入的参数放在Fn的相同对应位置


bind
std::bind函数定义在头文件中，是一个函数模板，它就像一个函数包装器(适配器)，接受一个可
调用对象（callable object），生成一个新的可调用对象来“适应”原对象的参数列表。一般而
言，我们用它可以把一个原本接收N个参数的函数fn，通过绑定一些参数，返回一个接收M个（M
可以大于N，但这么做没什么意义）参数的新函数。同时，使用std::bind函数还可以实现参数顺
序调整等操作。

可以将bind函数看作是一个通用的函数适配器，它接受一个可调用对象，生成一个新的可调用对
象来“适应”原对象的参数列表。

调用bind的一般形式：auto newCallable = bind(callable,arg_list);
其中，newCallable本身是一个可调用对象，arg_list是一个逗号分隔的参数列表，对应给定的
callable的参数。当我们调用newCallable时，newCallable会调用callable,并传给它arg_list中
的参数。

arg_list中的参数可能包含形如_n的名字，其中n是一个整数，这些参数是“占位符”，表示
newCallable的参数，它们占据了传递给newCallable的参数的“位置”。数值n表示生成的可调用对
象中参数的位置：_1为newCallable的第一个参数，_2为第二个参数，以此类推。

//占位符位于std中的placeholders命名空间

//功能1:实现参数顺序调整
void Print(int x, int y)
{
    std::cout<< x << " ";
    std::cout<< y <<std::endl;
}

int main()
{
    Print(10,20);
    auto RPrint = std::bind(Print,std::placeholders::_2,std::placeholders::_1);
    RPrint(10,20);

	//还能这么写,因为返回的就是函数对象,包装器底层生成的函数对象的类型是匹配的
    std::function<void(int,int)> RPrint1 = std::bind(Print,std::placeholders::_2,std::placeholders::_1);
    RPrint1(10,20);
    return 0;
}

// bind底层也是仿函数,通过套一层编译器生成的仿函数,把参数顺序调了,再传给需要调用的仿函数....


功能2:把多参数调整成少参数,以符合某些传参需求... 比较有用,某些时候可以把一些固定的参数隐藏起来.就如成员函数的隐藏参数this



*/







#pragma once

//异常的概念
/*
抛出异常后必须要捕获,否则终止程序(到最外层后会交给main管理,main的行为就是终止)

try{}内写可能会抛出异常的代码.catch(类型){处理} 写异常类型和异常处理

抛出的异常对象是自动遍历所有栈帧,直到main的

多层栈帧中,try跳转从上到下最近的catch

跳转的过程会连续关闭跳过的栈帧

异常被捕获后,会正常执行往后的流程.没有异常就不会再进入catch

异常捕获后,只会进入,catch(类型)内类型最匹配的catch --- 例外,子类和父类同时存在时,依旧服从就近原则

抛出异常的对象,以拷贝方式传给其他调用链的catch.原先抛出的对象,出了作用域就销毁,不矛盾
    即catch捕获的是一个拷贝,catch结束后也会自动销毁

执行catch只有跳转进去 ,其他情况不会进去.
    如,执行完一条catch,不会再执行后面的catch,而是执行try-catch语句块之后的正常代码

抛出异常/throw后,后面的代码不会再执行,而是到捕获异常/catch内的地方继续执行


C语言处理错误的方式简单粗暴，直接终止进程难免“伤及无辜”，就拿音乐播放器来说，难道因为某个歌词显示错误就直接中断程序吗？
  这显然是不合理的，C++的异常机制就好像把错误交给一个中间者，如果在某个模块中出现了错误，那么就把这个错误暂时塞给它，
  它会执行我们事先规定好的处理流程，同时它也会给上层一些事先规定要提示的内容，此时进程是不会被系统终止的，其他模块也能正常运作。
  这就保证了程序的稳定性。

*/



//异常安全
/*

异常安全是指在函数报告错误条件后，对程序状态的额外保证。有以下四种级别的异常保证，它们是严格的超集关系：

.不抛出异常保证（no-fail guarantee）：这是最强的保证，它意味着一个函数不会抛出任何异常，也不会改变程序的状态。
    比如析构函数或者移动构造函数。
.强异常保证（strong guarantee）：这是次强的保证，它意味着一个函数如果抛出了异常，那么程序的状态会回滚到调用该函数之前的状态。
    比如std::vector::push_back或者std::swap。
.基本异常保证（basic guarantee）：这是最弱的保证，它意味着一个函数如果抛出了异常，那么程序的状态仍然是有效和一致的，但可能不是预期的。
    比如std::vector::reserve或者std::list::splice。


*/



//异常规范
/*
引入;

.构造函数完成对象的构造和初始化，最好不要在构造函数中抛出异常，否则可能导致对象不完整或没有完全初始化
.析构函数主要完成资源的清理，最好不要在析构函数内抛出异常，否则可能导致资源泄漏(内存泄漏、句柄未关闭等)
.C++中异常经常会导致资源泄漏的问题，比如在new和delete中抛出了异常，导致内存泄漏，在lock和unlock之间抛出了异常导致死锁，C++经常使用RAII来解决以上问题

C++异常可能会导致以下安全问题：
.资源泄漏：如果一个函数在分配资源后抛出异常，而没有正确地释放资源，那么就会造成内存泄漏或者文件句柄泄漏等问题。
   为了避免这种情况，可以使用RAII的技术，比如智能指针或者标准库容器。
.数据破坏：如果一个函数在修改数据结构后抛出异常，而没有正确地恢复数据结构的状态，那么就会造成数据不一致或者不变量被破坏等问题。
   为了避免这种情况，可以使用拷贝和交换（copy and swap）的技术，比如std::swap或者std::vector::swap。
.异常嵌套：如果一个函数在处理异常时又抛出新的异常，而没有正确地捕获和处理新的异常，那么就会造成程序终止或者未定义行为等问题。
   为了避免这种情况，可以使用noexcept关键字来指定不会抛出异常的函数，比如析构函数或者移动构造函数。

  RAII，Resource Acquisition Is Initialization，资源获取即初始化。
  一种将资源的生命周期绑定到对象的生命周期的 C++ 编程技术。它有助于避免资源泄漏并简化错误处理。这是设计智能指针核心。



C++有两种类型的异常规范：

动态异常规范使用throw关键字来列出函数可以抛出的特定异常。
静态异常规范使用noexcept关键字来指示函数是否可以抛出任何异常。

动态异常规范在C++11中被弃用，在C++17中被移除，除了throw()，它相当于noexcept(true)。这种异常规范的设计目的是提供关于函数可以抛出什么异常的概要信息，但实践中发现它有很多问题。例如：

.动态异常规范不是函数类型的一部分，所以不能用于函数指针或引用。
.动态异常规范只能检查直接抛出的异常，而不能检查间接抛出的异常。
.动态异常规范会增加运行时开销和编译时间开销。
.动态异常规范会限制代码的可移植性和可维护性。
因此，建议不要使用动态异常规范，而使用静态异常规范或者不使用任何异常规范。

C++98: //---- 坑 -----  不是强制的,只是声明.
1. 异常规格说明的目的是为了让函数使用者知道该函数可能抛出的异常的类型有哪些。 可以在函数的后面接throw(类型A,B,C,...)，列出这个函数可能抛掷的所有异常类型。
     //可能会抛其他类型的异常,且不会警告,可能会造成误导 -- 坑
2. 函数的后面接throw()，表示函数不抛异常。
3. 若无异常接口声明，则此函数可以抛掷任何类型的异常。

C++98规定抛出指定的异常，但是到底是否抛出异常还是取决于程序员，因为这个规范不是强制的，所以出不出问题主要看人。
C++11简化了这一规则，只问抛出不抛出（TRUE or FALSE），即noexcept表示不抛异常。

C++11:
新增 noexcept 违反异常声明
thread() noexcept;
thread (thread&& x) noexcept;

使用:
1.一个函数明确不抛异常,加noexcept;  //如果加了noexcept,还是抛异常的话,则会报错!!!!  --- 很实用
2.可能会抛异常,什么都不加


异常说明的实参
noexcept说明符接受一个可选的实参，该实参必须能转换为bool类型：如果实参是true，则函数不会抛出异常；如果实参是false，则函数可能抛出异常：
void recoup(int) noexcept(true);    //recoup 不会抛出异常
void alloc(int) noexcept(false);    //alloc 可能抛出异常

*/

//异常的处理
/*

1.分辨不同类型的异常,有不同的应对措施 --- 结合用户感受,反馈不同体验

2.一个程序的其中一个模块不能用,应不影响其他模块,用户体验好.若一个模块出问题而程序直接终止,用户体验不够好,健壮性不够

class Exception
{
public:
    Exception(int errid, std::string errmsg):_errid(errid),_errmsg(errmsg)
    {}
    int getErrid() const
    {
        return _errid;
    }
    const std::string& getMsg() const
    {
        return _errmsg;
    }

private:
    int _errid;           //错误码
    std::string _errmsg;  //错误描述
};

double Division(int a, int b)
{
    if (b == 0)
    {
        //方式1 //以常规对象方式抛出
        //Exception e(1,"除零错误");
        //throw e;

        //方式2
        throw Exception(1,"除零错误"); //以临时对象方式抛出
    }
    return a/b;
}

void fun()
{
    int a,b;
    std::cin>> a>>b;
    try
    {
        Division(a,b);
    }
    catch (const std::string s)
    {
        cout<<s<<std::endl;
    }
    catch (...) //捕获任意类型 ,防止有一些异常没有捕获,导致程序终止
    {
        cout<<"未知异常 Unkown Exception"<<std::endl;
    }

}

int main()
{
    try
    {
        fun();
    }
    catch ( const Exception& e)
    {
        std::cout<< e.getMsg()<<std::endl;
        std::cout<<e.getErrid()<<std::endl;
    }
    return 0;
}




3.规范:抛子类,用父类捕获 --- 例外,可以不是严格匹配






*/

//C++标准库的异常体系
/*
C++ 提供了一系列标准的异常，定义在std中，我们可以在程序中使用这些标准的异常。它们是以父子类层次结构组织起来的，如下所示：

详细博客
https://www.xjx100.cn/news/125313.html?action=onClick

std::exception	该异常是所有标准C++异常的父类。
std::bad_alloc	该异常可以通过new抛出。
std::bad_cast	该异常可以通过dynamic_cast抛出。
std::bad_exception	这在处理C++程序中无法预期的异常时非常有用。
std::bad_typeid	该异常可以通过typeid抛出。
std::logic_error	理论上可以通过读取代码来检测到的异常。
std::domain_error	当使用了一个无效的数学域时，会抛出该异常。
std::invalid_argument	当使用了无效的参数时，会抛出该异常。
std::length_error	当创建了太长的std::string时，会抛出该异常。
std::out_of_range	该异常可以通过方法抛出，例如std::vector和std::bitset<…>::operator。
std::runtime_error	理论上不可以通过读取代码来检测到的异常。
std::overflow_error	当发生数学上溢时，会抛出该异常。
std::range_error	当尝试存储超出范围的值时，会抛出该异常。
std::underflow_error	当发生数学下溢时，会抛出该异常。
具有继承体系的异常类，能方便地从上往下管理各种异常类，所有由标准库组件抛出的对象都派生自此类。因此，所有标准异常都可以通过引用捕获此类型来捕获。

部分注解:
类型exception仅仅定义了拷贝构造函数、拷贝赋值运算符、一个虚析构函数和一个名为what的虚成员函数。其中what函数返回一个const char＊类型的空字符，该指针，并且确保不会抛出任何异常。

类exception、bad_cast和bad_alloc定义了默认构造函数。

类runtime_error和logic_error没有默认构造函数，但是有一个可以接受C风格字符串或者标准库string类型实参的构造函数，这些实参负责提供关于错误的更多信息。

在这些类中，what负责返回用于初始化异常对象的信息。
  因为what是虚函数，所以当我们捕获基类的引用时，对what函数的调用将执行与异常对象动态类型对应的重写版本。

*/

//异常的缺点
/*
缺点
1.异常会导致程序执行流乱跳的问题，而且非常混乱，并且是运行时出错抛异常就会乱跳，这导致我们跟踪调试时以及分析程序时，造成很大困难。
2.异常需要保证代码异常安全，这对开发者的挑战很大。引入异常，也就引入了一个隐含的执行路径。很多时候，你根本不知道一个函数会不会抛出异常，可能抛出哪些异常。
3.C++标准库的异常定义得很不好，导致都定义自己的异常体系，非常混乱。
4.C++异常不带调用栈信息，当在外层捕获到下层自动传播来的异常时，现场已经没了。这时候反而可能是手动向上层层传播的错误码+错误日志更有利于定位到真正的问题。
5.异常会有一些性能的开销。当然在现代硬件速度很快的情况下，这个影响基本忽略不计。但是如果bad-path的频率较高，性能开销则不可能忽略不计。

6.混乱的执行流：实际上，使用goto这个早已被抛弃的关键字也能实现异常处理机制，而异常机制混乱的执行流就像goto语句一样有很多不确定性。
例如在一个函数调用链中某个函数捕获了异常，并跳转到对应catch语句，这虽然符合异常的处理机制，但是一旦我们想在跳转的语句块中调试，就显得异常困难。

7.通过对代码在某个地方打断点调试，如果这个地方恰好发生了执行跳转，断点就失效了。实际上，异常机制其他缺点都可以弥补，唯有执行流混乱难以解决。

只要程序走到断点位置，那么程序一定能停下来。跳来跳去停不下来，说明没有执行到断点位置，如果逻辑复杂，调试非常麻烦。

*/


//自定义异常类体系
/*
实际使用中很多公司都会自定义自己的异常体系进行规范的异常管理，因为一个项目中如果大家
随意抛异常，那么外层的调用者基本就没办法玩了，所以实际中都会定义一套继承的规范体系。
这样大家抛出的都是继承的派生类对象，捕获一个基类就可以了

我们使用自定义异常类的方式与使用标准异常类的方式完全一样。程序在某处抛出异常类型的对象，在另外的地方捕获并处理这些出现的问题。
可以根据小组分为不同的子类，这些子类都继承自同一个父类。
最基础的异常类至少需要包含错误编号和错误描述两个成员变量，甚至还可以包含当前函数栈帧的调用链等信息。该异常类中一般还会提供两个成员函数，分别用来获取错误编号和错误描述。例如：

class Exception
{
public:
Exception(int errid, const char* errmsg):_errid(errid), _errmsg(errmsg)
{}
int GetErrid()        const {return _errid;}
virtual string what() const {return _errmsg;}
protected:int _errid;     // 错误编号
string _errmsg; // 错误信息//...
};

//----------------------------------------------------------------------------  实际项目中,较为标准的一种自定义写法
#include<thread>
#include<chrono>

class Exception
{
public:
    Exception(int errid, const std::string& errmsg) :_errid(errid), _errmsg(errmsg)
        //加引用必须要const,使成为接收右值构造.不加const的引用就是绑定,必须要类型相同,这时string就不能用""构造 ,
    {}
    int getErrid() const
    {
        return _errid;
    }
    //const std::string getMsg() const
    //{
    //    return _errmsg;
    //}

    //C++标准库中提供what()方法,等价于getMsg()
    virtual std::string what() const //返回拷贝,不能返回引用
    {
        return _errmsg;
    };

protected: //protected子类能访问 ,private子类不能访问
    int _errid;           //错误码
    std::string _errmsg;  //错误描述
};

class SqlException : public Exception
{
public:
    SqlException(const std::string& errmsg, int errid, const std::string& sql)
        :Exception(errid, errmsg), _sql(sql)
    {}

    virtual std::string what() const //重写,构造自己的what()
    {
        std::string msg;
        msg += "SqlException: ";
        msg += _errmsg;
        msg += "->";
        msg += _sql;
        return msg;
    };

protected:
    std::string _sql;
};

class CacheException : public Exception
{
public:
    CacheException(const std::string& errmsg, int id)
        :Exception(id, errmsg)
    {}
    virtual std::string what() const   //重写,构造自己的what()
    {
        std::string str = "CacheException:";
        str += _errmsg;
        return str;
    }
};
class HttpServerException : public Exception
{
public:
    HttpServerException(const std::string& errmsg, int id, const std::string& type)
        :Exception(id, errmsg)
        , _type(type)
    {}
    virtual std::string what() const   //重写,构造自己的what()
    {
        std::string str = "HttpServerException:";
        str += _errmsg;
        str += "->";
        str += _type;
        return str;
    }
private:
    const std::string _type;
};
void SQLMgr()
{
    srand((size_t)time(0));
    if (rand() % 7== 0)
    {
        std::cout<<"11111111111";
        throw SqlException("权限不足", 100, "select * from name = '张三'");
    }
    std::cout << "调用成功" << std::endl;
}
void CacheMgr()
{
    srand((size_t)time(0));
    if (rand() % 5 == 0)
    {
        throw CacheException("权限不足", 100);
    }
    else if (rand() % 6 == 0)
    {
        throw CacheException("数据不存在", 101);
    }
    SQLMgr();
}
void HttpServer()
{
    // ...
    srand((size_t)time(0));
    if (rand() % 3 == 0)
    {
        throw HttpServerException("请求资源不存在", 100, "get");
    }
    else if (rand() % 4 == 0)
    {
        throw HttpServerException("权限不足", 101, "post");
    }
    CacheMgr();
}
int main()
{
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        try {
            HttpServer();
        }
        //catch(const std::exception& e)  //库的exception
        catch (const Exception& e) // 这里捕获父类对象就可以,实际中很少会使用子类捕获
        {
            // 多态 -- 能够通过父类对象的指针或引用 去调用子类对象的成员 ---> 父类捕获子类后能够调用子类的成员
            std::cout << e.what() << std::endl;
        }
        catch (...)  //捕获未知异常,不遵守规则的异常等,最后防线
        {
            std::cout << "Unkown Exception" << std::endl;
        }
    }
    return 0;
}
//----------------------------------------------------------------------------  实际项目中,较为标准的一种自定义写法__End



*/


//重新抛出
/*


double Division(int a, int b)
{
    if (b == 0)
    {
        //方式1 //以常规对象方式抛出
        //Exception e(1,"除零错误");
        //throw e;

        //方式2
        throw std::string("Division by zero condition"); //以临时对象方式抛出
    }
    return a/b;
}

void fun()
{
    int *array = new int[10];
    int a,b;
    std::cin>> a>>b;
    try
    {
        std::cout<<Division(a,b)<<std::endl;
    }
    catch (const std::string s)
    {
        std::cout << "delete[]" << std::endl;
        delete[] array;
        //实际情况一般会要求统一在main中处理异常.这时可以把捕获到的异常重新抛出
        // 捕获到异常后,根据业务需求,需要做其他特殊处理,如网络传输失败后,需要尝试重新链接多几次,用户体验才会好
       throw s; //抛特定类型
    }
    catch (...) //接收任意类型
    {
        std::cout << "delete[]" << std::endl;
        delete[] array;
        //业务...
        throw; //捕获到什么,就抛什么,由编译器识别 --- 实际中常用的方法,因为异常很多
    }
    std::cout<<"delete[]"<<std::endl;
    delete[] array;

}

int main()
{
    try
    {
        fun();
    }
    catch (const std::string s)
    {
        std::cout<<s<<std::endl;
    }
    catch (...)
    {

    }
    return 0;
}


//对于这种动态内存问题, 实际上不推荐这种方式,代码可读性也不够好 --- 智能指针

*/






#pragma once


// 1. 设计一个不能被拷贝的类
/*
 解析:拷贝只会放生在两个场景中：拷贝构造函数以及赋值运算符重载，因此想要让一个类禁止拷贝，
     只需让该类不能调用拷贝构造函数以及赋值运算符重载即可。

C++98;
    将拷贝构造函数与赋值运算符重载只声明不定义，并且将其访问权限设置为私有即可。
原因：
1. 设置成私有：如果只声明没有设置成private，用户自己如果在类外定义了，就可以不能禁止拷贝了
2. 只声明不定义：防止编译器自动生成,且没必要定义,原本就是不想使用

C++11:
    C++11扩展delete的用法，delete除了释放new申请的资源外，如果在默认成员函数后跟上 =delete，表示让编译器删除掉该默认成员函数。
class CopyBan //ban 禁止 , 禁止拷贝
{
    // ...
    CopyBan(const CopyBan&)=delete;
    CopyBan& operator=(const CopyBan&)=delete;
    //...
};

h*/


//2.设计一个只能在堆上创建对象的类
//------------------------------------------------------------ 只能在堆上创建对象的类
/*
//思路1:隐藏析构函数
class HeapOnly
{
public:

    void Destory()
    {
        delete this;
    }

private:
    ~HeapOnly()
    {
        std::cout << "~HeapOnly()" << std::endl;
    }
    //public:
    int _x;
};

int main()
{

    //HeapOnly ho1; //报错,没有可访问的析构函数类不能在栈上定义对象,因为栈上的对象是由编译器负责析构的,但类外不能访问私有,即编译器调不到析构,释放不了,所以会有问题
    //HeapOnly ho2(); //未知,编译器自动生成的行为不可控制

    //static HeapOnly ho4; //静态区的对象也受编译器控制析构,所以也不能正常定义

    HeapOnly *ho3 = new HeapOnly; //没有可访问的析构函数类只能在堆上定义对象,因为堆上的资源由用户自己释放,所以可以正常定义
   //delete ho3; //必须是公开的析构函数,才能在栈上使用delete(在栈域访问类域私有成员)
   ho3->Destory(); //进到类域内部的函数能够访问私有成员,可以析构
    return 0;
}
*/

//思路2:隐藏构造函数(常用,通用)
//封构造函数能够把在栈上 定义或new 封掉
/* class HeapOnly
{
public:
    static HeapOnly* createObj(int x = 0) // static函数在类域内,不受访问修饰符约束,能够看得见成员函数
    {
        HeapOnly* p = new HeapOnly(x); //在类域内new一个对象,就是在类域内调用构造,定义的空间位于堆区
        return p;
    }
private:
    HeapOnly(int x = 0) :_x(0)
    {}
    HeapOnly(const HeapOnly& ho) = delete;
    HeapOnly& operator=(const HeapOnly& ho) = delete;
    int _x;
};

int main()
{
    HeapOnly* ho = HeapOnly::createObj(0); //在栈上定义一个指针,调用类域内的静态函数createObj去new一个对象,得到对象的指针
        //HeapOnly ho1(*ho); //还需要禁掉拷贝构造
    return 0;
}
*/

//------------------------------------------------------------ 只能在堆上创建对象的类__End;




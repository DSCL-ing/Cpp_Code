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



// 设计只能在栈上定义类(不能完全做到,最多只能禁止堆,不能禁止static区)
/*
class StackOnly
{
public:
    static StackOnly createObj(int x = 0) 
    {
        return StackOnly(x);  //传值返回
    }
    static StackOnly create_move_Obj(int x = 0)
    {
        return std::move(StackOnly(x)); //画蛇添足
    }
    StackOnly(const StackOnly& ho):_x(ho._x)
    {}
    StackOnly(StackOnly&& ho):_x(ho._x)
    {}

private:
    StackOnly(int x = 0):_x(0)
    {}
    int _x;
};

int main()
{
    StackOnly ho =  StackOnly::createObj(0);  //传值返回 -- 需要拷贝构造
    static StackOnly sho = ho; // 有拷贝构造就能创建static对象

    StackOnly ho1 =  StackOnly::create_move_Obj(1);  //如果禁止掉拷贝构造而使用移动构造
    static StackOnly sho1 = std::move(ho1); // 有移动构造也能创建static对象
    return 0;
}
*/


//设计一个不能被继承的类
/*
C++98:构造函数私有化
 // 原因: 派生类在初始化时必须要显式调用父类构造函数帮助父类私有化, 父类构造函数私有后,子类就无法完成初始化了

C++11:使用final关键字,final修饰类,表示该类不能被继承

class A  final //最终
{
    // ....
};
*/

//设计模式
/*

设计模式：
设计模式（Design Pattern）是一套被反复使用、多数人知晓的、经过分类的、代码设计经验的
总结。为什么会产生设计模式这样的东西呢？就像人类历史发展会产生兵法。最开始部落之间打
仗时都是人拼人的对砍。后来春秋战国时期，七国之间经常打仗，就发现打仗也是有套路的，后
来孙子就总结出了《孙子兵法》。孙子兵法也是类似。
使用设计模式的目的：为了代码可重用性、让代码更容易被他人理解、保证代码可靠性。 设计模
式使代码编写真正工程化；设计模式是软件工程的基石脉络，如同大厦的结构一样。

//C++不太关注设计模式,Java比较关注

C++常见设计模式:
适配器
迭代器
单例 (最广泛)
工厂
观察者



*/

//单例模式
/*




*/

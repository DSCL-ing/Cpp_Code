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
设计模式(Design Pattern)是一套被反复使用、多数人知晓、经过分类的、代码设计经验的总结。
为什么会产生设计模式这样的东西呢？ 
 就像人类历史发展会产生兵法。最开始部落之间打仗时都是人拼人的对砍。后来春秋战国时期，七国之间经常打仗,就发现打仗也是有套路的,
 后来孙子就总结出了《孙子兵法》. -- 类似

使用设计模式的目的：为了代码可重用性、让代码更容易被他人理解、保证代码可靠性。设计模式使代码编写真正工程化；
    设计模式是软件工程的基石脉络，如同大厦的结构一样.

//C++不太关注设计模式,Java比较关注

C++常见设计模式:
适配器
迭代器
单例 (最广泛)
工厂
观察者



*/

//单例模式 singleton pattern
/*
一个类只能创建一个对象,即单例模式,该模式可以保证系统中该类只有一个实例，并提供一个访问它的全局访问点(getInstance),该实例被所有程序模块共享。
   比如在某个服务器程序中，该服务器的配置信息存放在一个文件中，这些配置数据由一个单例对象统一读取，
   然后服务进程中的其他对象再通过这个单例对象获取这些配置信息，这种方式简化了在复杂环境下的配置管理
 
单例模式有两种实现模式： 1.饿汉模式 2. 懒汉模式

使用场景：只要某个类的对象在全局只有一份,就可以使用单例模式


*/


//饿汉模式:
/*
进程一启动就会创建一个唯一的实例对象,在main函数执行前就创建了.

// 优点：简单,没有线程安全问题(因为main函数之前没有多线程,而饿汉在main之前就new了)
// 缺点：可能会导致进程启动慢(如果单例对象很大)，且会占用资源(没用也创建), 且如果有多个单例类对象实例启动顺序不确定(main内的代码执行流是确定的,其他的不确定。 

如果这个单例对象在多线程高并发环境下频繁使用，性能要求较高，那么显然使用饿汉模式来避 免资源竞争，提高响应速度更好。
   --- 怎么体现


class Singleton
{
public:
    static Singleton* getInstance()
    {
        return _ins;
    }
    void Add(const std::string& s)
    {
        _mtx.lock();
        _v.push_back(s);
        _mtx.unlock();
    }
    void Print()
    {
        _mtx.lock();
        for (auto& v : _v)
        {
            std::cout << v << std::endl;
        }
        _mtx.unlock();
    }
private:
    Singleton()
    {}
    std::vector<std::string> _v; // 不用给大小,对象实例化后会自动定义一个空的,后面push_back即可
    static Singleton* _ins;
    std::mutex _mtx;
};
Singleton* Singleton::_ins = new Singleton; //在堆上实例化

int main()
{
    //Singleton::getInstance()->Add("张三");
    //Singleton::getInstance()->Add("李四");
    //Singleton::getInstance()->Add("王五");
    //Singleton::getInstance()->Print();

    int n = 10;

    std::thread t1([n]() {
        for (int i = 0; i < n; i++)
        {
           srand((size_t)time(0)); //srand只在当前进程有效
            Singleton::getInstance()->Add(std::string("线程1: ") + std::to_string(rand()));
        }
        });
    std::thread t2([n]() {
        for (int i = 0; i < n; i++)
        {
           srand((size_t)time(0));
            Singleton::getInstance()->Add(std::string("线程2: ") + std::to_string(rand()));
        }
        });


    t1.join();
    t2.join();

    Singleton::getInstance()->Print();

    return 0;
}


*/








//懒汉模式：
/*
    如果单例对象构造十分耗时或者占用很多资源，比如加载插件，初始化网络连接欸，读取文件等等，而且有可能该对象在程序运行时不会用到,
 如果在程序一开始就进行初识化，就会导致程序启动时非常缓慢。这种情况使用懒汉模式（延迟加载）更好. 

 优点：只在初次使用实例对象时，创建对象。进程启动无负载。多个单例实例启动顺序能够自由控制.
 缺点：复杂


class Singleton
{
public:
    static Singleton* getInstance()
    {
        //双检查加锁
        //设计模式专业术语:双重检查锁定模式一种软件设计模式,用来减少并发系统中竞争和同步的开销。
        //双重检查锁定模式首先验证锁定条件(第一次检查)，只有通过锁定条件验证才真正的进行加锁逻辑并再次验证条件(第二次检查)。
        if (!_ins) //提高效率,减少加锁解锁
        {
            _imtx.lock();
            if (!_ins)  //用于保证线程安全和 只new一次
            {
                _ins = new Singleton;
            }
            _imtx.unlock();
        }
        return _ins;
    }
    
    //手动释放_ins对象,手动调用del并不会影响到_gc,因为静态类型不受对象控制
    static void delInstance() //为什么是静态? 因为没有对象,只有类型,通过类域展开来调用
    {
        //不需要双检查加锁了,因为销毁对象极少调用.开销不大
        _imtx.lock();
        if (_ins)
        {
            delete _ins; //之后会自动调用_ins的析构
            _ins = nullptr;
        }
        _imtx.unlock();
    }

    //资源自动回收对象GC
    struct GC
    {
        ~GC()
        {
            std::cout<<"~GC"<<std::endl;
            delInstance();
        }
    };
    static struct GC _gc; //声明一个静态GC成员,静态成员不受_ins对象控制,只在生命周期到了(结束结束)后自动释放
    // 因为定义在堆的对象在程序结束时不会自动释放/delete,所以设计GC辅助
    // 1.当程序快结束前(main return之后),静态变量的生命周期结束,OS会自动delete静态变量,即~GC且释放_gc,然后delInstance,~Singleton且释放_ins
    // 因此GC能够保证单例对象能在程序结束时自动完成析构和释放工作

    void Add(const std::string& s)
    {
        _vmtx.lock();
        _v.push_back(s);
        _vmtx.unlock();
    }
    void Print()
    {
        _vmtx.lock();
        for (auto& v : _v)
        {
            std::cout << v << std::endl;
        }
        _vmtx.unlock();
    }
    ~Singleton()  //对象要没的时候(delete this)才会调用 
    {
        //持久化操作... (持久化就是变成长久保存,一般就是写到文件,文件在磁盘中,就是持久化的一种实现)
        // 要求在析构时,将数据保存在文件中.
    }

private:
    Singleton()
    {}
    std::vector<std::string> _v;                      // 不用给大小,对象实例化后会自动定义一个空的,后面push_back即可
    std::mutex _vmtx;

    static Singleton* _ins;
    static std::mutex _imtx;                        //目前不太清楚为什么用的是静态锁
};
Singleton* Singleton::_ins = new Singleton; //在堆上实例化
std::mutex Singleton::_imtx;
Singleton::GC Singleton::_gc;

int main()
{
    //Singleton::getInstance()->Add("张三");
    //Singleton::getInstance()->Add("李四");
    //Singleton::getInstance()->Add("王五");
    //Singleton::getInstance()->Print();

    int n = 10;
    //srand((size_t)time(0)); 影响不到两个线程,定不定义无所谓
    std::thread t1([n]() {
        for (int i = 0; i < n; i++)
        {
            //srand((size_t)time(0)); //srand只在当前进程有效,但这里定义变化不大了,需要寻求新的随机数方法
            Singleton::getInstance()->Add(std::string("线程1: ") + std::to_string(rand()));
        }
        });
    std::thread t2([n]() {
        for (int i = 0; i < n; i++)
        {
            //srand((size_t)time(0));
            Singleton::getInstance()->Add(std::string("线程2: ") + std::to_string(rand()));
        }
        });


    t1.join();
    t2.join();

    Singleton::getInstance()->Print();
    //Singleton::delInstance();  //手动释放,
    return 0;
    //程序结束才会释放静态,因为静态不受对象控制,只随生命周期(整个程序运行期间)
}


*/





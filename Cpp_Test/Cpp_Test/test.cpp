#define _CRT_SECURE_NO_WARNINGS 1

#include <ctime>
#include <random>
#include <iostream>
#include<string.h>
#include<algorithm>
#include<string>
#include<map>
#include<memory>
#include<mutex>
#include<thread>
#include<functional>
#include<vector>

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











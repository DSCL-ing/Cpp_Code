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

//shared_ptr简易模拟实现和使用测试
template<class T>
class shared_ptr
{
public:
    shared_ptr(T* ptr) :_ptr(ptr), _pcount(new int(1)), _pmtx(new std::mutex()) //第一次定义
    {}
    shared_ptr(const shared_ptr<T>& sp) :_ptr(sp._ptr), _pcount(sp._pcount), _pmtx(sp._pmtx) //拷贝
    {
        AddCount();
    }
    ~shared_ptr()
    {
        Release();
    }
    void Release()
    {
        _pmtx->lock();

        bool deleteFlag = false;

        if (--(*_pcount) == 0)//每次执行都会--, 如果--后为0,就析构
        {
            delete _ptr;
            delete _pcount;
            //锁也要释放

            //{ //解决方案一
            //_pmtx->unlock();
            //delelte _pmtx;
            //return;
            //}

            //解决方案二 : 使用标志位
            deleteFlag = true;

        }
        _pmtx->unlock(); //释放锁后,不能有解锁操作

        if (deleteFlag)
        {
            delete _pmtx;
        }

    }
    void AddCount()
    {
        _pmtx->lock();
        ++(*_pcount);
        _pmtx->unlock();
    }
    shared_ptr& operator=(const shared_ptr<T>& sp)
    {
        //先析构掉自己的资源
        if (sp._ptr != _ptr)
        {
            Release();
            _ptr = sp._ptr;
            _pcount = sp._pcount;
            _pmtx = sp._pmtx;  //拷贝时也要把锁烤过来
            AddCount();
        }
        return *this;
    }
    T& operator*()
    {
        return *_ptr;
    }
    T* operator->()
    {
        return _ptr; //返回地址
    }
    T* get() const //getPtr
    {
        return _ptr;
    }
    int use_count()  //返回引用的对象个数
    {
        return *_pcount;
    }
private:
    T* _ptr;    //管理资源的指针
    int* _pcount; //动态开辟的计数器,用于引用计数
    std::mutex* _pmtx; //多线程时,保障临界资源的安全
};


struct Date
{
    int _year = 0;
    int _month = 0;
    int _day = 0;
};
void SharePtrFunc(shared_ptr<Date>& sp, size_t n, std::mutex& mtx) {
    std::cout << sp.get() << std::endl;
    for (size_t i = 0; i < n; ++i)
    {
        //验证1:验证智能指针本身是否安全,
        shared_ptr<Date> copy(sp);
        
        {
            std::unique_lock<std::mutex> lk(mtx);//守护锁
            copy->_year++;
            copy->_month++;
            copy->_day++;
        //验证二: 智能指针 管理的资源不一定是线程安全的,两个线程++了2n 次是最终结果，正常情况下加了2n次,通过加锁和不加锁来验证
        }
    }
}


int main()
{
    shared_ptr<Date> p(new Date);
    std::cout << p.get() << std::endl;
    const size_t n = 10000;
    std::mutex mtx;
    std::thread t1(SharePtrFunc, std::ref(p), n, std::ref(mtx));
    std::thread t2(SharePtrFunc, std::ref(p), n, std::ref(mtx));
    t1.join();
    t2.join();
    std::cout << p.use_count() << std::endl; //如果结果是1,说明线程安全. 否则说明不安全
    std::cout<<p->_year<<std::endl;
    std::cout<<p->_month<<std::endl;
    std::cout<<p->_day<<std::endl;
    return 0;
}















//int div()
//{
//    int a, b;
//    std::cin >> a >> b;
//    if (b == 0)
//        throw std::invalid_argument("除0错误");
//    return a / b;
//}
//
//void func()
//{
//    std::shared_ptr<int> sp1(new int(1));
//    std::shared_ptr<int> sp2(sp1);
//    *sp1 = 10;
//    std::cout << *sp2 << std::endl;
//    std::shared_ptr<int> sp3(new int(3));
//    sp3 = sp1;
//    sp1 = sp1;
//    sp1 = sp3;
//    std::cout << div() << std::endl;
//}
//
//int main()
//{
//    try {
//        func();
//    }
//    catch (const std::exception& e)
//    {
//        std::cout << e.what() << std::endl;
//    }
//    return 0;
//}



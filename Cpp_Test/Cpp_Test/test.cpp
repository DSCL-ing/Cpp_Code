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

template<class T>
class shared_ptr
{
public:
    //template <class U> explicit shared_ptr(U* p);
    explicit shared_ptr(T* ptr = nullptr) :_ptr(ptr), _pcount(new int(1)), _pmtx(new std::mutex()) //第一次定义
    {}

    //with deleter(4) .接收定制删除器版本
    //template <class U, class D> shared_ptr(U* p, D del);
    template <class T, class D>
    shared_ptr(T* ptr, D del)
        : _ptr(ptr), _pcount(new int(1)), _pmtx(new std::mutex()), _del(del)
    {}

    shared_ptr(const shared_ptr<T>& sp) :_ptr(sp._ptr), _pcount(sp._pcount), _pmtx(sp._pmtx) //拷贝
    {
        AddCount();
    }

    ~shared_ptr()
    {
        Release();
    }
private:
    void Release()
    {
        _pmtx->lock();

        bool deleteFlag = false;

        if (--(*_pcount) == 0)//每次执行都会--, 如果--后为0,就析构
        {
            if (_ptr)
            {
                //delete _ptr;
                _del(_ptr);//把_ptr传给 通过包装器接收的 来自外界或缺省的 定制删除器
            }


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
public:
    shared_ptr<T>& operator=(const shared_ptr<T>& sp)
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
    std::function<void(T*)> _del = [](T*ptr) {       //D是可调用对象类型,具体类型有多种,functional类型能够一个定义全部接收
        std::cout << "default function<void(T*)>" << std::endl;
        delete ptr;                         //缺省值
    };
};

/*
不同类型的资源有不同的析构方式, shared_ptr通过可调用对象:定制删除器 来实现不同方式的资源释放
定制删除器:就是可调用对象,实现一个定制的,具有删除功能的可调用对象,传给shared_ptr
*/
template<class T>
struct DeleteArray
{
    void operator()(T* ptr) //shared_ptr会把资源的指针传进来
    {
        std::cout << " void operator()(T* ptr)" << std::endl;
        delete[] ptr;
    }
};

struct Date
{
    int _year = 0;
    int _month = 0;
    int _day = 0;
};


int main()
{
    shared_ptr<Date> sp0{ new Date };
    shared_ptr<Date> spa1{ new Date[4],DeleteArray<Date>() }; // 仿函数方式 释放资源
    shared_ptr<Date> spa2{ new Date[10],[](Date* ptr) {delete[] ptr; } }; //lambda表达式方式 释放资源
    shared_ptr<FILE> spF3{ fopen("test.cpp","r"),[](FILE* ptr) {fclose(ptr); } }; //不只是堆空间,还可以是文件
    return 0;
}


















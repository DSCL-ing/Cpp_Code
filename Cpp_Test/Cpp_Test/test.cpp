#define _CRT_SECURE_NO_WARNINGS 1

#include <ctime>
#include <random>
#include <iostream>
#include<string.h>
#include<algorithm>
#include<string>
#include<map>
#include<memory>

template<class T>
class shared_ptr
{
public:
    shared_ptr(T* ptr) :_ptr(ptr), _pcount(new int(1))
    {}
    shared_ptr(const shared_ptr<T>& sp) :_ptr(sp._ptr), _pcount(sp._pcount)
    {
        AddCount();
    }
    ~shared_ptr()
    {
        Release();
    }
    void Release()
    {
        if (--(*_pcount) == 0)//每次执行都会--, 如果--后为0,就析构
        {
            delete _ptr;
            delete _pcount;
        }
    }
    void AddCount()
    {
        ++(*_pcount);
    }
    shared_ptr& operator=(const shared_ptr<T>& sp)
    {
        //先析构掉自己的资源
        if (sp._ptr != _ptr)
        {
            Release();
            _ptr = sp._ptr;
            _pcount = sp._pcount;
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
private:
    T* _ptr;
    int* _pcount;
};

int div()
{
    int a, b;
    std::cin >> a >> b;
    if (b == 0)
        throw std::invalid_argument("除0错误");
    return a / b;
}

void func()
{
    std::shared_ptr<int> sp1(new int(1));
    std::shared_ptr<int> sp2(sp1);
    *sp1 = 10;
    std::cout << *sp2 << std::endl;
    std::shared_ptr<int> sp3(new int(3));
    sp3 = sp1;
    sp1 = sp1;
    sp1 = sp3;
    std::cout << div() << std::endl;
}

int main()
{
    try {
        func();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}



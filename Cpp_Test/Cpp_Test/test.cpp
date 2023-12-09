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
           srand((size_t)time(0));
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











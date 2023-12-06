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

template<class T>
class shared_ptr
{
public:
    shared_ptr(T* ptr = nullptr) :_ptr(ptr), _pcount(new int(1)), _pmtx(new std::mutex()) //第一次定义
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
};

struct ListNode
{
    /*
    //ListNode* prev;
    //ListNode* next;
    n1->next = n2; //没有异常的正常情况下,是没有问题的
    n2->prev = n1; //使用shared_ptr管理ListNode后,类型不匹配,无法转换
    //需要重新封装next和prev,使用shared_ptr封装next和prev
    */

    shared_ptr<ListNode> _prev; //智能指针封装的list
    shared_ptr<ListNode> _next;

    int _val;
    ~ListNode()
    {
        std::cout << "~ListNode()" << std::endl;  //调试用 -- 看是否执行析构
    }
};

void test_shared_cycle() //测试共享指针的循环问题
{
    //{//一:常规写法,没有异常的正常情况下没有问题,但是异常出来以后,就不推荐这种写法
    //    ListNode* n1 = new ListNode;
    //    ListNode* n2 = new ListNode;  //因为,从这里开始,如果抛异常,则n1的资源可能没有释放,--> 导致内存泄露

    //    n1->next = n2;
    //    n2->prev = n1;

    //    delete n1;
    //    delete n2;
    //}

    {//二:
        shared_ptr<ListNode> n1(new ListNode);
        shared_ptr<ListNode> n2 = new ListNode; //隐式类型转换方式构造,调用了默认构造
        //shared_ptr<ListNode> n3{ new ListNode }; //花括号初始化,编译器提供的支持,等价于=
       
        //现象1,只有n1->_obj = n2或 n2->obj = n1;时,可以正常析构
        //现象2,当n1,n2循环引用时,无法正常析构了
       n1->_next = n2;
        n2->_prev = n1;
        //对现象2的解决方案:
    }

}


int main()
{
    test_shared_cycle();
    return 0;
}












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


//template <class U> explicit shared_ptr(U* p);
template<class T>
class shared_ptr
{
public:
    explicit shared_ptr(T* ptr = nullptr) :_ptr(ptr), _pcount(new int(1)), _pmtx(new std::mutex()) //第一次定义
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

//weak_ptr 简易实现,仅仅能符合简单场景,用于理解weak_ptr ---- 非常简易,库中实现很困难
template<class T>
class weak_ptr
{
public:
    weak_ptr()
        :_ptr(nullptr) //默认生成的不管理资源
    {}
    weak_ptr(const shared_ptr<T>& sp)
        :_ptr(sp.get()) //帮助shared_ptr管理资源
    {}
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
private:
    T* _ptr;
};

struct ListNode
{
    /* 1.有智能指针类型不匹配问题
    //ListNode* prev;
    //ListNode* next;
    n1->next = n2; //没有异常的正常情况下,是没有问题的
    n2->prev = n1; //使用shared_ptr管理ListNode后,类型不匹配,无法转换
    //需要重新封装next和prev,使用shared_ptr封装next和prev
    */

    /* 2.有循环引用问题
    //shared_ptr<ListNode> _prev; //智能指针封装的list
    //shared_ptr<ListNode> _next;
    */

    weak_ptr<ListNode> _next;
    weak_ptr<ListNode> _prev;

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
        //shared_ptr<ListNode> n2 = new ListNode; //隐式类型转换方式构造,调用了默认构造,使用explicit后不支持
        shared_ptr<ListNode> n2{ new ListNode }; // 花括号初始化,等价于直接调用默认构造 ,注意,并不是=使用explicit后用=会报错
        //shared_ptr<ListNode> n3{ new ListNode }; //花括号初始化,编译器提供的支持,

        //现象1,只有n1->_obj = n2或 n2->obj = n1;时,可以正常析构
        //现象2,当n1,n2循环引用时,无法正常析构了 --- shared_ptr的缺陷
        n1->_next = n2;
        n2->_prev = n1;

        //对现象2的分析;
        /*
        核心原因,两个对象相互引用:属于同一个对象的的内部资源,引用了第二个对象.而另外一个对象的内部资源,也反向引用第一个对象,
              两对象互相引用,在析构时两边都在等待对方先析构,形成闭环,导致类似死锁的现象
             两个对象相互引用后,引用计数都为2,析构时两个对象都为1,无法减到0.导致无法真正析构资源. --- 属于shared_ptr的缺陷
        */

        //对现象2的解决方案:
        /*
        使用C++提供的weak_ptr(弱指针),用于解决shared_ptr循环引用的问题.
        weak_prt是专门用于解决shared_ptr的循环引用问题的类,特殊的智能指针,不符合RAII
        weak_ptr的三个构造函数:
 //1.无参构造
constexpr weak_ptr() noexcept;
//2.拷贝构造
1.weak_ptr (const weak_ptr& x) noexcept;
2.template <class U> weak_ptr (const weak_ptr<U>& x) noexcept;
//3.根据shared_ptr构造
template <class U> weak_ptr (const shared_ptr<U>& x) noexcept;
        //从三个拷贝构造来看,weak_ptr没有支持使用资源来构造,说明weak_ptr不是RAII指针,不是常规的智能指针
//特点
//1.他不是常规的智能指针,不支持RAII
//2.一样像指针一样(是特殊的智能指针)
//3.专门设计出来,辅助解决shared_ptr的循环引用问题

      */
    }

}


int main()
{
    test_shared_cycle();
    return 0;
}












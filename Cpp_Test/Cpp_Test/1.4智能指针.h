#pragma once

/*
Smart pointer

智能指针;灵巧指针

智能指针三大件
//1.RAII
//2.像指针一样使用
//3.拷贝问题 ,指针指针需要的是浅拷贝,并且需要处理资源释放问题 ---> 引用计数


RAII
Resource Acquisition Is Initialization 资源获取即初始化
一种利用对象的生命周期来控制资源的技术 ,是一种思想
在对象构造时获取资源，接着控制对资源的访问使之在对象的生命周期内始终保持有效，最后在对象析构的时候释放资源


SmartPrt是RAII的一种产物

在linux下内存泄漏检测：linux下几款内存泄漏检测工具 https://blog.csdn.net/gatieme/article/details/51959654
在windows下使用第三方工具：VLD工具说明 https://blog.csdn.net/GZrhaunt/article/details/56839765
其他工具：内存泄漏工具比较 https://www.cnblogs.com/liangxiaofeng/p/4318499.html



C++11和boost中智能指针的关系
1. C++ 98 中产生了第一个智能指针auto_ptr.
2. C++ boost给出了更实用的scoped_ptr和shared_ptr和weak_ptr.
3. C++ TR1(Technical Report 1,技术引入1:草稿)，引入了shared_ptr等。不过注意的是TR1并不是标准版。
4. C++ 11，引入了unique_ptr和shared_ptr和weak_ptr。需要注意的是unique_ptr对应boost
的scoped_ptr。并且这些智能指针的实现原理是参考boost中的实现的。

*/



//智能指针常规实现1
/*

//1.RAII
//2.像指针一样使用
//3.拷贝问题 ,指针指针需要的是浅拷贝,并且需要处理资源释放问题 ---> 引用计数
template<class T>
class SmartPtr
{
public:
    SmartPtr(T* ptr) :_ptr(ptr)
    {}
    ~SmartPtr()
    {
        if (_ptr)
            delete _ptr;
    }
    T& operator*()
    {
        return *_ptr;
    }
    T* operator->()
    {
        return _ptr; //返回地址,会优化->-> ... .当T为自定义类型时起效
    }
private:
    T* _ptr;
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
   SmartPtr<int> sp1(new int(1));
   SmartPtr<int> sp2(new int(10));
   *sp1 = 10;
    std::cout<< *sp1<<std::endl;

   std::cout<<div()<<std::endl;
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


*/



//智能指针的发展历史
/*
C++98:auto_ptr(自动指针)
    解决拷贝问题的方式:使用管理权转移方式(把资源转移给新指针,原来的指针置空)
    存在的问题:资源转移后,原来的指针就成了垂悬指针.使用的人因不熟悉特性或疏忽遗漏,到导致野指针引用
    //在C++11标准中已明确废弃,很多公司规范明确不能使用auto_ptr,基本上没什么价值了

#include<memory> //头文件
void func()
{
   std::auto_ptr<int> sp1(new int(1)); //nullptr
   std::auto_ptr<int> sp2(sp1);        //sp1
   *sp1 = 10;   //奔溃
}

boost时期:
boost库是C++标准库的体验服,https://baike.baidu.com/item/Boost%E5%BA%93/10671694?fr=ge_ala
较为好用的智能指针
scoped_ptr
shard_ptr/weak_ptr


(
防拷贝:
C++98:
1.对拷贝构造和拷贝赋值 只声明,不实现.--- 什么都不做
2.设置为私有  --- 防止外部获取并在外部实现

C++11:
copy = delete
operator = delete
)

C++11:
unique_ptr (scoped_ptr发展) 
    原理:简单粗暴,防拷贝(防止拷贝) --- 解决了auto_ptr资源转移后产生的垂悬指针问题,但无法解决需要拷贝的场景
    使用:不需要使用拷贝的场景就可以使用
shard_ptr/weak_ptr(boost:shard_ptr/weak_ptr发展)
    原理:引用计数
    线程安全: shared_ptr本身是线程安全的,但是shared_ptr管理的对象不一定是安全的


//shared_ptr简易模拟实现和使用测试
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

*/



//shared_prt 循环引用 问题

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

解决循环引用问题的核心原理是不增加引用计数
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
    /.* 1.有智能指针类型不匹配问题
    //ListNode* prev;
    //ListNode* next;
    n1->next = n2; //没有异常的正常情况下,是没有问题的
    n2->prev = n1; //使用shared_ptr管理ListNode后,类型不匹配,无法转换
    //需要重新封装next和prev,使用shared_ptr封装next和prev
    *./

    /.* 2.有循环引用问题
    //shared_ptr<ListNode> _prev; //智能指针封装的list
    //shared_ptr<ListNode> _next;
    *./

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
        /.*
        核心原因,两个对象相互引用:属于同一个对象的的内部资源,引用了第二个对象.而另外一个对象的内部资源,也反向引用第一个对象,
              两对象互相引用,在析构时两边都在等待对方先析构,形成闭环,导致类似死锁的现象
             两个对象相互引用后,引用计数都为2,析构时两个对象都为1,无法减到0.导致无法真正析构资源. --- 属于shared_ptr的缺陷
        *./

        //C++11对现象2的解决方案:使用weak_ptr
    }

}

int main()
{
    test_shared_cycle();
    return 0;
}

*/


//定制删除器
/*
不同类型的资源有不同的析构方式, shared_ptr通过可调用对象:定制删除器 来实现不同方式的资源释放
定制删除器:就是可调用对象,实现一个定制的,具有删除功能的可调用对象,传给shared_ptr

template<class T>
struct DeleteArray //函数对象式定制删除器
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
    shared_ptr<Date> spa1{ new Date[4],DeleteArray<Date>() }; // 函数对象式定制删除器 释放资源
    shared_ptr<Date> spa2{ new Date[10],[](Date* ptr) {delete[] ptr; } }; //lambda表达式式定制删除器 释放资源
    shared_ptr<FILE> spF3{ fopen("test.cpp","r"),[](FILE* ptr) {fclose(ptr); } }; //不只是堆空间,还可以是文件
    return 0;
}

*/






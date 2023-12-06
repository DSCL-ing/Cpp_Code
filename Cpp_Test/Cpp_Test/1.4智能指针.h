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


*/

//shared_prt 循环引用 问题
/*



*/






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


*/



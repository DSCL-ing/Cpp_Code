﻿#pragma once

//C类型转换
/*
C语言:显式和隐式类型转换
1. 隐式类型转化：编译器在编译阶段自动进行，能转就转，不能转就编译失败
2. 显式类型转化：需要用户自己处理.

隐式类型:界定:相关类型,相近类型,意义相似的类型 可以发生类型转换 ,
   如整型和浮点可以发生类型转换,因为他们都表示数据的大小. 指针和整型不能发生,因为指针表示地址,和整型的意义不一样.

缺陷：
转换的可视性比较差，所有的转换形式都是以一种相同形式书写，难以跟踪错误的转换

C语言的隐式类型转换的坑;
size_t 和 int (无符号和有符号）:在vector 的 insert中体现 . 如size_t与int的变量有比较操作时会发生类型提升。当其中一个将要<0就会难以控制



*/


//C++为什么需要强制类型转换
/*
C++认为隐私类型转换不够好,最好就是不让隐私类型转换发生,于是引入了强制类型转换

C风格的转换格式很简单，但是有不少缺点的：
1. 隐式类型转化有些情况下可能会出问题：比如数据精度丢失
2. 显式类型转换将所有情况混合在一起，代码不够清晰
因此C++提出了自己的类型转化风格，注意因为C++要兼容C语言，所以C++中还可以使用C语言的
转化风格

*/

//C++强制类型转换
/*
标准C++为了加强类型转换的可视性，引入了四种命名的强制类型转换操作符：
static_cast、reinterpret_cast、const_cast、dynamic_cast

1.static_cast
    static_cast 对应 C语言的隐式类型转换(能当C语言的隐式类型转换使用)
 用于非多态类型的转换(静态转换).编译器隐式执行的任何类型都可用. 但是不能用于两个不相关的类型进行转换
int main()
{
    double d = 12.34;
    int a = static_cast<int>(d); // 意义相似,可以静态转换 ,仅丢失精度
    std::cout << a << std::endl;
    return 0;
}

2.reinterpret_cast -- 重新解释的转换 , 对应C语言的显式强制类型转换
    reinterpret_cast 是重新解释的意思,进行一些不相关类型的转换
 通常为操作数的位模式提供较低层次的重新解释,用于将一种类型转换为另一种不同的类型.
 相关或相近类型不能使用reinterpret_cast.(会报错)
int main()
{
    double d = 12.34;
    int a = static_cast<int>(d);
    std::cout << a << std::endl;
    // 这里使用static_cast会报错，应该使用reinterpret_cast
    //int *p = static_cast<int*>(a);
    int* p = reinterpret_cast<int*>(a);  //如C语言的强制类型转换,把int转化成int*
    return 0;
}

3.const_cast --- 去掉const的转换
    const_cast最常用的用途就是删除变量的const属性,方便赋值. 
    通常要搭配volatile使用,因为编译器可能会把const变量当作宏来直接替换 或当作不再修改的变量放到寄存器.



*/
















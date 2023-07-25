#pragma once


//非类型模板参数
/**
 * 模板参数分为类型形参和非类型形参 
 * $类型模板参数用于解决typedef type reType_name;
 * 
 * $非类型模板参数用于解决宏常量,#define N 10 ;
 * 演示:template<class T ,size_t N> class A
 *		--- class_A<int,10>;
 * 特点:
 * 1.只能是整型常量,有符号无符号long,char,bool(true为1,false为0)等都可以,double,float等不行
 * 
 * 
 * .
 */


//类<array>
/**
 * C++11,老编译器可能不支持
 * 
 * 和静态数组一样,没有初始化
 * 
 * 优势是越界检查更加严格:
 * 传统数组是抽查越界写,只查一小部分,有些地方越界可能不会报错
 * Array数组是读写全面检查
 * 
 * 使用:
 * array<int,10> a1;
 * 
 * 差别:
 * 但实际上用处不够强,vector更强,一般也更喜欢用vector,vector还能直接初始化:vector<int> v(10,0); 
 * 主要差别是array是在栈上,vector是在堆里
 * 
 */

//模板特化 ---某些类型进行特殊化处理 --范围限定
/**
 * 解释:
 * 重载了类模板的一个特定类型的模板类,当使用模板时,如果有对应的特化模板,则调用特化模板,否则调用原模板
 * 
 * 注意:模板特化必须要有一个原始模板,然后在原始模板之上特化
 * 
 * 使用:
 * template<class T>
 * bool Less(T left , T right){
 *		return left<right;
 * }
 * 
 * 然后才能有特化模板 -- 全特化
 * template<>
 * bool Less<Date*>(Date* left,Date* right){
 *      return *left < * right;
 * }
 * 
 * 优点:
 * 支持对某类型的特殊处理 -- 类模板,类模板使用更频繁
 * 
 * 各种用法:
 * a.类模板特化  ---- 模板特化主要使用的是类模板
 * b.函数模板特化 -- 1.函数模板使用重载更多 2.不支持显式传模板参数 --非必要,也可以实现一个模板类重载(匹配)
 * 1.全特化
 * 2.半特化/偏特化-- 1.部分限制(给具体类型)  2.进一步限制(限制是指针,引用等)
 * 
 *  template<> --  类模板全特化
 *  struct Less<Date*>{ // --只接收Date*类型
 *      bool ooperator()(const Date* left , const Date* right){
 * 		     return left<right;
 *      }
 * }
 * 
 * template <class T> -- 类模板偏特化 
 * struct Less<T*>{ //--接收任意指针类型
 *		  bool operator()(const T* l, const T* r)
 *             reutrn *l<*r;
 *		 }
 * }
 * 
 * 类型:自定义,指针,引用都可以,引用的话注意要初始化(缺省参数),引用比较少 -- const迭代器有使用引用
 * 
 */


//模板的分离编译
/**
 * 
 * 模板不支持不同文件定义和声明,只支持在同一个文件声明和定义分离
 * 定位C++NO.21 2023_3_20
 * 
 * 如果非要分离,需要显式实例化(指定类型) -> 丧失模板优势,直接回到C语言
 * 
 * 所以:
 * 如果比较短小的的函数直接在类里面定义(无声明) -- 类内函数都是内联函数
 * 
 * 体积大的函数在类内声明,在类外定义 ,不使用内联,减小可执行程序体积
 * 
 */






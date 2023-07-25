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

//模板特化 ---某些类型进行特殊化处理 --非必要,也可以实现一个模板类重载(匹配)
/**
 * 解释:
 * 重载了类模板的一个特定类型的模板类,当使用模板时,如果有对应的特化模板,则调用特化模板,否则调用原模板
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
 * b.函数模板特化 -- 1.函数模板使用重载更多 2.不支持显式传模板参数
 * 1.全特化
 * 2.半特化
 * 3.偏特化
 * 
 *  template<> --  类模板全特化
 *  struct Less<Date*>{ // --只接收Date*类型
 *      bool ooperator()(const Date* left , const Date* right){
 * 		     return left<right;
 *      }
 * }
 * 
 * template <class T> -- 类模板偏特化 -- 进一步的限制
 * struct Less<T*>{ //--接收任意指针类型
 *		  bool operator()(const T* l, const T* r)
 *             reutrn *l<*r;
 *		 }
 * }
 * 
 */






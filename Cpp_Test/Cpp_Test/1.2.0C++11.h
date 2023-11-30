﻿#pragma once

#include<iostream>
#include<vector> 
#include<list>
#include"10myString.h"
#include"11myVector.h"
#include"12myList.h"
#include"9Date.h"
#include <map>



   //c++11
   /**
    *
    * c++目前最期待的是网络库
    *
    * c++官方网站
    * https://en.cppreference.com/w/cpp/11
    *
    * dev编译器是一个套着壳的gcc
    * dev不支持范围for --> 没有支持c++11
    * 没有公司会用dev,但学校可能会用dev,---原因是dev成本比较低 -- 适合入门
    *
    * .
    */



    //｛｝初始化 -- 花括号初始化 -- 列表初始化 -- 
    /**
     *  目的:让一切都可以用花括号去初始化
     *  在c++98中，标准允许使用花括号{}对数组或者结构体元素进行统一的列表初始值设定
     *
     * c++11扩大了用大括号括起的列表(初始化列表)的使用范围，使其可用于所有的内置类型和用户自定义的类型，使用初始化列表时，可添加等号(=)，也可不添加。
     * .创建对象时也可以使用列表初始化方式调用构造函数初始化
     */
struct point //结构体可以定义在函数体内部
{
    int _x;
    int _y;
};
void test1()
{
    {
        int x1 = 1;
        int x2 = { 2 };
        int x3{ 3 }; //省略赋值符号
        int x4(4);//     int x4(1); //圆括号初始化可以认为是int的构造; 
            //个写法是模板引进(c++11)的,调了int的构造 -- 与列表初始化无关

        point p{ 1,2 }; //自动识别,匹配,类成员,进行赋值构造 
       // 1. 兼容c语言,像c语言的结构体赋值
       // 2. 支持调用最匹配的构造函数

        Date d1(2023, 1, 1); //构造

        Date d2 = { 2023, 1, 1 };// 构造+拷贝构造 == 构造
        Date d3{ 2023,1,1 };//列表初始化,自动匹配最优的构造函数
        //如果不想优化,即不想使用=号初始化,则可以在构造函数使用explicit关键字,表示只能显示调用构造函数
    }









    /* vector和list的列表初始化 */
    {
        std::vector<int> v1 = { 1,23,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }; //
        std::list<int> l1 = { 1,1,1,1,1,1,1,11,1,1,1 }; //花括号里是一个常量数组

        auto i1 = { 1,1,1,1,1,1,1,1,1,1,1 };
        //查看i1的类型
        std::cout << typeid(i1).name() << std::endl;// class std::initializer_list<int>  -- 是一个类
    /**
     * C++11给vector和list增加了支持initializer_list的构造函数,使其支持花括号初始化
     * //我们可以给自己的vector和list添加initializer_list构造,原理很简单,遍历+push_back就好了 -- 已添加在mylist和myVector
     * 只有容器才适配了initializer_list
     * 
     * C++容器还支持使用initializer_list赋值(operator=)
     * 
     */


     /* initializer_list */
          /**
           * 类:class template<T>  std::initializer_list{};
           *
           * 成员:begin指向常量数组头.end指向常量数组尾的下一个位置,size为end-begin,
           *
           */

           //验证begin是地址:
        std::initializer_list<int>::iterator it = i1.begin();
        std::cout << it << std::endl;//00AFF9C4,是一个地址, --> begin指向的是常量数组的地址

        //c++11 std::initializer_list<t> -- 接收常量数组 --该数组在常量区 -- 不允许修改
        //++(*it); -- 报错,不允许 --- 因为是常量,不允许修改

        /**
         * 中文名 :初始化器表
         *
         * 是c++标准程序库中的一个头文件，定义了c++标准中一个非常轻量级的表示初始化器列表的类模板initializer_list及有关函数。
         * 为了编写能够处理不同数量实参（但是类型相同），c++11新标准提供了initializer_list的方法。
         * 与vector不同的是，initializer_list对象中的元素永远是常量值，我们无法改变initializer_list对象中元素的值。在进行函数调用的时候需要使用花括号将所有的参数括起来。
         *
         * 支持:vector,list,map
         *
         * std::initializer_list一般是作为构造函数的参数，c++11对stl中的不少容器就增加std::initializer_list作为参数的构造函数，
         * 这样初始化容器对象就更方便了。也可以作为operator=的参数，这样就可以用大括号赋值。
         *
         */
    }
    {
        int i = 1;
        int array1[] = { 1,2,3,4,5 };
        int array2[]{ 1,2,3,4,5 };//省略赋值符号
        int array3[5] = { 0 }; //只初始化1个还是全部初始化了?
        int array4[5]{ 0 };//省略赋值符号

        // c++11中列表初始化也可以适用于new表达式中
        int* pa = new int[4]{ 0 };

        //日期类也可以支持花括号,不带赋值是拷贝构造
        //但日期类带赋值是构造+拷贝...优化而成
        //如果不想自定义类型显式调用拷贝构造可以加explicit(意思:明确),即使自定义不能通过赋值符号初始化 -- 把构造干掉,也拷贝不了了

        //自定义类型初始化时可以把圆括号换成花括号
        //花括号和圆括号的区别是,花括号可以用 = 号,或者省略等号(省略时和圆括号一样). 而圆括号只能跟/贴着对象或类型

    }

    {

        Date d1(1, 1, 1);
        Date  d2(2, 2, 2);

        //initializer_list<Date>
        std::vector<Date> v1 = { d1,d2 };
        std::vector<Date> v2 = { Date(1,1,1),Date(2,2,2) };
        std::vector<Date> v3 = { {1,1,1},{2,2,2} };
        //typename std::vector<int>::iterator it = v2.begin(); // ------ 不知道为什么迭代器不对
    }


    {
        //map 可以使用初始化器表
        std::map<std::string, std::string> dict = { {"1","1"},{"2","2"} };

        //pair支持花括号 -- 和圆括号一样
        std::pair<int, int> kv = { 2,2 };

    }
    
   
}
  
  //auto
    /**
     * 在C++98中auto是一个存储类型的说明符，表明变量是局部自动存储类型，但是局部域中定义局
     * 部的变量默认就是自动存储类型，所以auto就没什么价值了。C++11中废弃auto原来的用法，将
     * 其用于实现自动类型推断。这样要求必须进行显示初始化，让编译器将定义对象的类型设置为初
     * 始化值的类型。.
     *
     * auto主要用于自动推导 接收到的对象的类型,方便用于接收对象
     * 
     * 
     */


 //decltype 也是推导类型 和auto类似
 /**
 * decltype可以提取表达式的类型,作为新变量/函数的类型
 * decltype主要是提取 ,方便用于声明类型
 * 
 * 使用方法:
 * decltype(表达式) 对象;
 *
 * .
 */

 //nullptr
 /**
  * 由于C++中NULL被定义成字面量0，这样就可能回带来一些问题，因为0既能指针常量，又能表示整形常量。
  * 所以出于清晰和安全的角度考虑，C++11中新增了nullptr，用于表示空指针。 
#ifndef NULL
#ifdef __cplusplus
#define NULL   0
#else
#define NULL   ((void *)0)
#endif
#endif 
  * 
  */

 //范围for循环
 /**
  * 底层是迭代器
  */

  //智能指针
  /**
   * 
   * 
   */

  //c++11新增容器相关
  /**
   * 一,新增容器
   * 1.array --- 区别不大 -- vector可以替代
   * 2.forward_list -- 还行 -- 如果只需要单链表头插,则效率会比list好一点 -- 比list节省空间,每个节点节省一个指针的空间
   * 3.unordered_set -- 牛
   * 4.unordered_map -- 牛
   *
   * 二.新增容器特性
   * 1.部分容器新增构造函数支持initlizer_list
   * 2.新增迭代器cbegin和cend()
   * 3.新增 移动构造和移动赋值  -- 标志 type&& val
   * 4.新增 右值引用
   *	3.4.价值非常大,提高了拷贝效率;
   *
   *
   *
   */


/** 左值和右值
 *
 * $.什么是左值?
 * -- 能取地址的值就是左值
 * 左值：可以进行取地址的称为左值。
 * 问:语句const int c = 10;中,c是左值吗? 是.// 就算不能够再次修改,只要能取地址,都是左值
 *	https://www.cnblogs.com/myxjil/p/17290124.html
 *
 *   
 * 左值特点:
 * 1.能取地址就是左值
 * 2.左值可以在赋值的左边或右边 --  只要是能取地址的值
 * 
 * 
 * $.什么是右值?
 * 右值：不能进行取地址的称为右值。右值包括：临时对象、匿名对象、临时变量、匿名变量、字面值常量literal
 * 常见的右值;
    10; //常量
    x+y;//表达式
    fmin(x,y); //函数的返回值 
     
 * 传统的c++语法中就有引用的语法，而c++11中新增了的右值引用语法特性，所以从现在开始我们之前学习的引用就叫做左值引用。
 *    无论左值引用还是右值引用，都是给对象取别名。
    1.C++11在所有容器的构造函数中加了移动构造版本
    2.C++11在所有容器的插入函数中加了右值引用版本
  
 * 右值特点:
 * 1.是一个数据表达式
 * 2.字面常量,表达式返回值,函数返回值(返回的那个临时变量,不能是引用)
 * 3.右值可以出现在赋值符号的右边，但是绝对不能出现在赋值符号的左边 --- 右值不能取地址
   
 *  
 */

 /** 左值引用 和右值引用 都能引用什么对象?
  *
  *  左值引用:给左值起别名
  *  int a = 1;
  *  int& ref = a;//给左值起别名
  
  *  左值能不能给右值起别名? 一般情况不能 
  *  1.不能的情况
     int& ref = (x+y)  //报错 -- 理由是:权限放大      
        ---> 说明: 右值是const修饰的常性值
  *  2.但是const修饰的能   
     const int &ref = (x+y); //正常,加了const就可以
   
   
  *  右值引用能不能引用左值? 一般情况下不能 
  *  1.不能的情况
     int &&ref = a; //错误
  *  2.但是可以引用move以后的左值起别名
     int &&ref = move(a); //正常
   
  */



/**左值引用的短板：
 * 但是当函数返回对象是一个局部变量，出了函数作用域就不存在了，就不能使用左值引用返回，
 * 只能传值返回。例如：bit::string to_string(int value)函数中可以看到，这里只能使用传值返回，
 * 传值返回会导致至少1次拷贝构造(如果是一些旧一点的编译器可能是两次拷贝构造)。.
 */



 //右值引用
 /*
  
  * 右值引用:右值引用就是对右值的引用，给右值取别名。
        右值引用一般是建立在左值之上的, 目的是优化左值,实现左值一些达不到的要求 
 
  * // 以下几个都是常见的右值
  10; //字面常量
  x + y; //表达式
  min(x, y); //返回值(临时变量)
  
  * // 以下几个都是对右值的右值引用
 int&& rr1 = 10;
 double&& rr2 = x + y;
 double&& rr3 = fmin(x, y);
  
  //右值引用有什么用
  

 $ .编译报错：error c2106: “=”: 左操作数必须为左 
 例子;
 10 = 1;
 x + y = 1;
 fmin(x, y) = 1;


  
  //左值引用+const后也可以引用右值 --> 说明: 右值有常性
 const int& ref = x+y;
   
  * $ const 左值引用既可以给左值起别名,也可以给右值起别名 -- 和右值引用基本没有区别,目前没有遇到 ??????????????
  * 但是const 左值引用 有时会区分不了引用的是左值还是右值 --> 一般都是直接用右值引用
如:
void func(const int&a)
{
    std::cout<<"左值引用"<<std::endl;
}
void func(int&& a)
{
    std::cout<<"右值引用"<<std::endl;
}
int main()
{
    int a = 1;
    int b = 2;
    func(a); //左值
    func(a+b);//右值

}
结果:
1.如果屏蔽右值func,则编译器认为两个都是左值,调用左值func -- 编译器区分不了
2.如果没有屏蔽,则编译器就能区分左右值了,输出左值和右值 ----> 说明:引入右值引用能让编译器更好的去区分左值和右值,能更好的匹配函数


 

 
 
$$$$$.  右值不能取地址，但是给右值取别名后，会让右值转移存储到特定位置，使可以取到该位置的地址，
也就是说,例如：不能取字面量10的地址，但是对rr1进行右值引用后，就可以取rr1地址了，也可以修改rr1。
  
  相当于右值引用后,右值变成左值? ???????,右值引用后的右值还是右值吗?
      > 答案: 右值引用后,右值就会变成左值
      > 为什么? 因为:
      . 这样设计才是符合语法要求,因为我们要将右值,将亡值转移给新的对象使用.而要给新的对象使用,则必须是左值才可以
      . 如果转移后还是右值,而修改右值是不合理,原因是右值没地址,且属性不允许修改,临时对象,要消亡的,因此,不应该是右值
      . 所以:转移后,就是左值
 
  * 如果不想rr1被修改，可以用const int&& 引用rr1
   
  * 这个了解一下,实际中右值引用的使用场景并不在于此，这个特性也不重要
 int main()
 {
  double x = 1.1, y = 2.2;
  int&& rr1 = 10;
  const double&& rr2 = x + y;
  rr1 = 20;   //资源转移后变左值了,可以修改
  rr2 = 5.5;  // 报错 --- const右值引用,资源转移后依旧不可修改
  return 0;
  }

  * 右值引用一般不带const ,带const会怎样?
         : const && 引用的是 const右值对象  -- 结果是资源转移后依然不可修改  -- 很少使用
  



  
  
$$.右值又分为
  * 1.纯右值 -- 一般是内置类型 -- 一些临时对象
  * 2.将亡值 -- 一般是自定义类型  -- 右值引用可以让资源转移,减少拷贝花销 --> 移动拷贝/移动构造

    
$$. 将亡值:顾名思义,就是就要消亡的值. 既然是要消亡的值,那我们可以利用起来.
            将亡值在本身是必须要消亡的,但我们可以转移他的生命到别处,让别人所用,成为别人的一部分.而自己本身不能再使用,这就等价于本身已经消亡 .
       --> 引入:移动构造/移动拷贝 
 
 //move作用:将普通值变成将亡值 ,转移到接收的对象上. --- 由于转移后原对象的值就没有了,所以使用时需要注意
       注意:move必须是有对象接收时,才可以转移资源. 直接使用move,没有接收的对象时,不做任何处理.


 
  * 左值引用能做的:直接减少拷贝:
    1.左值引用传参 
    2.传引用返回 -- 注意:函数内局部对象不能传引用返回,正常返回则需要拷贝,代价大	-> 优化:使用右值引用,直接转移对象,减少拷贝
 

 
$$. 编译器在处理返回值时,在可以优化的情况下,会在返回值销毁前,
    1.走移动构造,作资源转移, ----- 直接转移到接收返回值的对象 ,如int a = func(1,2); 返回值会直接移动构造到a,然后再析构add
    2.然后再析构,然后销毁栈帧(包括返回值) -- 此处编译器做得更复杂,右值可能没有经过返回值这一步就直接转移到新对象上.因此返回值类型只要与接收的对象匹配即可,不能改成右值
     即:编译器在对要返回的值做处理时,会右值优化(复杂),如自动加move(隐式)等 ---- 也可以手动return+move(显式) -- 画蛇添足
  
  
  * c++11对容器构造和插入函数都增加右值引用版本
  *
  * 匿名对象是右值,用匿名对象初始化时,匿名对象会被识别成右值 -- 又如字符串"xxxx"这些没有使用变量而直接拿到括号内初始化,也如匿名对象
  * 但如果是c++98,则只会调深拷贝
   
  */


/** 左值引用和右值引用的优点体现:
 * 总结: 
左值引用和右值引用都是减少拷贝,提高效率.但角度不同,
左值引用是直接减少拷贝,如传参需要拷贝,传引用能类似传指针,能直接访问到原对象,不需要拷贝
右值引用是间接减少拷贝,识别出是左值还是右值,如果是右值就直接移动资源,不再拷贝,提高效率
 */




 //move:移动语义 :将左值改为右值,使其能够资源转移
 /**
  * move中文名:移动语义
  * 按照语法，右值引用只能引用右值，但右值引用一定不能引用左值吗？因为：有些场景下，可能
  * 真的需要用右值去引用左值实现移动语义。当需要用右值引用引用一个左值时，可以通过move
  * 函数将左值转化为右值。c++11中，std::move()函数位于     头文件中，该函数名字具有迷惑性，
  * 它并不搬移任何东西，唯一的功能就是将一个左值强制转化为右值引用，然后实现移动语义。
  *
  * move是std中的一个函数 ,使用时需要展开std
  *
  * $ 某些情况或不符合条件,可能不会资源转移,而是恢复成拷贝  -- 待学 --
  *  -- 补充:move符合以下两点之一才能资源转移
  * 1.能生成默认的移动构造  --- 1.怎样才支持自动生成默认的移动构造?,2.默认的移动构造是怎么样的?
  * 2.实现了移动构造
  
 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
  * $ move有时是把两个资源直接交换 -- 资源交换 ------------------------------------->不确定,可能有可能没有,但不要使用move过的对象 
         举例: 在移动赋值operator=(T&&t)中,move会使=号左右两值交换
         string s1("hello");
         string s2;
         s2 = move(s1); // 移动赋值,且资源交换
        

 move以后的对象的状态是无法确定的,不能再对原始对象进行操作,无论发生什么现象
       
  补充:
  1.如果是swap,则可能资源交换
  2.一定情况下,可以重新赋值,就可以再使用.

       
    xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
  */














  //完美转发/万能引用/引用折叠 std::forward<t> -- 既可以引用左值,也可以引用右值
  /**
   * perfect:完美的
   * forward:单向,向前
   * 
   *  万能引用是C++11提供的一种新的引用类型  ,主要与模板和类型推断一起使用
   *     
   * 使用模板时,模板会根据传惨的类型来自动推导类型
   *    万能引用/引用折叠就是在模板参数中使用&&右值引用符号,当参数是右值保持&&右值引用,当参数是左值时,&&就会编译器折叠成&,所以叫引用折叠
   * ---> 使形参既可以接收左值,也可以接收右值 
   */ 

   void fun(int &x){ cout << "左值引用" << endl; }
   void fun(const int &x){ cout << "const 左值引用" << endl; }
   void fun(int &&x){ cout << "右值引用" << endl; }
   void fun(const int &&x){ cout << "const 右值引用" << endl; }

     template<typename T>
     void perfectforward2(T&& t)
     {
         fun(t);
     }
   int man2()
   {
    perfectforward2(10);
    int a = 1;
    perfectforward2(a);
    perfectforward2(std::move(a)); 
    const int b = 8;
    perfectforward2(b);
    perfectforward2(std::move(b));
    return 0;
   }
   //结果:
   /*
左值引用
左值引用
左值引用
const 左值引用
const 左值引用
   
   */

/**
 * 前置知识:
 * 1.当右值引用接收右值后,该右值就会变成左值 ---> 右值属性丢失
 */

   template<typename t>
   void perfectforward1(t&& t)
   {
       fun(std::forward<t>(t));
   // std::forward<t>(t)在传参的过程中使t的类型属性得到保持。
   // 原理可能是,有记录了 是右值转移成的左值 的标记
   }

   int man()
   {
       perfectforward1(10);
       int a = 1;
       perfectforward1(a);
       perfectforward1(std::move(a));
       const int b = 8;
       perfectforward1(b);
       perfectforward1(std::move(b));
       return 0;
   }
/* 结果 */
/*
右值引用
.左值引用
右值引用
.const 左值引用
const 右值引用
*/


  /* 
   * 
   * $ 模板中的&&不代表右值引用，而是万能引用，其既能接收左值又能接收右值。
   *   模板的万能引用只是提供了能够接收同时接收左值引用和右值引用的能力
   *   但是引用类型的唯一作用就是限制了接收的类型，后续使用中都退化成了左值，
   *   我们希望能够在传递过程中保持它的左值或者右值的属性, 就需要用我们下面学习的完美转发
   *
   * 模板中&& 会自动推导,如果是左值 -- 会折叠&&的其中一个& ->变成只有1个& -- 即折叠引用.如果是右值,就不折叠
   *  -- 所以传左值就是左值引用,传右值就是右值引用 -- 万能引用
   *
   * 右值引用在作资源转移变成左值后,会丢失常性 -- 即变成左值
   * 右值引用引用后属性是左值,这样才能实现资源转移 --- 因为资源转移后,能修改才有意义 ,所以会丢失常性
   *
   * std::forward 完美转发在传参的过程中保留对象原生类型属性 -- 只保留一层,哪里需要加哪里,全部需要则都加上
   * string& s1 = string("hello"); //报错 -- 临时变量具有常性 引用不支持引用常量
   * string s1 = string("hello"); //正确 -- 编译器优化,资源转移到s1上,原临时变量丢失常性,可以正常修改
   *
   * forward是std的一个模板类
   *
   * 使用方法:
   * 		void push_back(t&& x) //右值 -- 资源转移到这层栈帧
          {
              insert(end(), forward<t>(x)); --如果不使用forward,则下一层就是左值,
          }
   *
   */





    /**
     *
     * 移动构造对深拷贝的类才有意义 -- 其他的开销太小了,意义不大
     *
     * 移动语义就是移动构造和移动赋值
     * .
     */

     /** 
      *  移动赋值 operator=
      *  移动构造
      *
      *
      */


    void test3()
    {
        test::string s;

        s = test::to_string(1234);
        //移动拷贝+深拷贝1+深拷贝2
        /**
         * 移动拷贝是to_string返回前将返回值转移出来
         * 深拷贝1是拷贝2的子过程 == 深拷贝
         * 即移动拷贝+深拷贝
         */


    }


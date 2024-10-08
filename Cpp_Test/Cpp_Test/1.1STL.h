﻿#pragma once

//打印变量的类型：cout<< typeid(变量).name();

//STL standard template library 标准模板库
/**
 * STL是C++标准库的一部分
 * 1.微软用的是P.J.版本
 * 2.RW版本已被微软干翻
 * 3.linux是SGI,继承自HP原始版本 -- 开源 -- 可读性好
 *
 *
 * STL六大组件:
 * 1.容器(数据结构) --containers
 * 2.算法 -- <algorithm>
 * 3.迭代器(C++11)
 * 4.适配器/配接器(栈,队列,优先级队列,包装器)
 * 5.仿函数
 * 6.空间配置器(内存池)
 *
 */

/*
标准模板库是一个C++软件库，大量影响了C++标准程序库但并非是其的一部分。其中包含4个组件，分别为算法、容器、函数、迭代器。
模板是C++程序设计语言中的一个重要特征，而标准模板库正是基于此特征。标准模板库使得C++编程语言在有了同Java一样强大的类库的同时，保有了更大的可扩展性。
在C++标准中，STL被组织为下面的13个头文件：
<algorithm>、
<functional>、
<utility>。
<numeric>、
<memory>、

<iterator>、
<vector>、 <list>、
<map>、<set>、
<deque>、<queue>、<stack>和
*/



//单词
/**
 * constructor  构造函数
 * destructor   析构函数
 * member  成员
 * copy constructor 拷贝构造函数
 * 
 */

//成员
/**
<Containers>
using std::vector
using std::list
using std::set
using std::map
using std::pair
using std::make_pair

<iostream>
using std::cout;
using std::endl;
using std::cin;

<algorithm>
using std::swap;
using std::max;


 */

 //容器-双端队列 Double ended queue (deque) (据说适合头插头删尾插尾删,所以取名双端队列)
 /**
  * <deque>
  * 优点
  * 1.扩容代价低
  * 2.头插头删尾插尾删的效率高
  * 3.支持随机访问
  *
  * 缺点
  * 1.中间插入删除难处理
  * 2.没有vector和list优点极致
  *
  * 实现
  * SGI以buff数组固定为实现,随机访问效率高,中间插入效率低
  *
  * 适合场景:头插头删尾插尾删频繁时->在适配器中使用比较合适
  * 所以库中将其作为栈和队列的底层容器
  *
  *
  */

//容器特点总结
/**
 * 对于vector list deque
 * vector排序最快,一般list或deque排序是将数据拷贝到vecotr排序完再拷贝回去

 * 序列式顺序表,序列式容器, -- 线性
 * vector(向量)
 * list(链表)
 * forward_list(单链表)
 * priority_queue(优先级队列)
 * 序列式容器适配器
 * stack(栈)
 * queue（队列）
 * deque(双端队列)
 * 
 * 关联式容器, -- 非线性 --存<key,value>结构的键值对,数据检索效率比序列式容器高
 * stl实现了两种关联式容器--树形结构和哈希结构
 * 树形结构关联式容器 -- 底层:平衡搜索二叉树(红黑树)
 * map 
 * set(集合)
 * multimap
 * multiset
 * 
 * 哈希结构关联式容器
 * 
 * 序列式和关联式容器区别
 * $ 序列式主要使用push 插入 , 而关联式只能使用insert插入
 * 
 *
 * .
 */

//容器的一些通用语法
/**
 * 显式析构函数(C++11支持):
 * vector<> v;
 * v.~vector();
 * 
 * 
 * .
 */




 //适配器
 /**
  * //设计模式:写代码的一些套路,模板
  * 适配器是一种设计模式(设计模式是一套被反复使用的、多数人知晓的、经过分类编目的、
  * 代码设计经验的总结)，该种模式是将一个类的接口转换成客户希望的另外一个接口。
  * 
  * 容器适配器
  * stack
  * queue
  * priority_queue 优先级队列(类似堆)
  * 
  * 迭代器适配器
  * reverse_iterator 反向迭代器
  * .
  */

//迭代器
/**
 * 迭代器失效
 * 1.野指针:缩容/扩容后开辟新空间,指向旧空间的迭代器未更新,成为野指针
 * 2.异位失效:没有缩容/扩容,但是因为增加或删除数据而导致pos指向其他位置
 * 
 * 数组/原生指针是天然的迭代器
 * 
 * 迭代器定义:
 * 1.迭代器是原生指针
 * 2.迭代器是自定义类型,是对原生指针的封装,在模拟指针的行为
 * 
 * 
 */


//仿函数(看起来像函数)  -- 实际是个结构体
/**
 * 仿函数(Functor)又称为函数对象(Function Object)
 * 仿函数是一个类,因为重载了operator(),具有类似函数的功能,所以叫仿函数
 * 
 * 为什么要使用一个类作为仿函数? 因为在类模板中,模板只能接收类型,所以必须使用一个实现了控制的功能类(自定义类型作为参数)作为参数传进去 -- 即 仿函数
 * 
 * 
 * greator:意思是更大的,逐渐变大,传参后变小堆.
 * less:意思是更小的,逐渐变小,传参后变大堆,默认是大堆,可以不用传
 * 模拟实现一个less
struct less{ //针对int
	bool operator()(int x,int y){ return x<y; }
}
模板实现
template<class T>
struct less{
	bool operator()(const T& x , const T& y){ return x>y; }

使用:
int main(){
	less<int> func;//对象
	cout<<func(1,2) <<endl; //	打印1 --->实际上就是重载了operator
}
 * 
 * 
 * 仿函数(functor)，就是使一个类的使用看上去像一个函数。其实现就是类中实现一个operator()，这个类就有了类似函数的行为，就是一个仿函数类了。
 *  有点像函数重载,接收不同参数返回不同对象 -- 跨域重载
 * 
 * 
 * 结合模板灵活使用,使用特化特性等..
 * 
 */


//什么是仿函数
/**
   
仿函数是早起命名，C++标准规格定案后采用新名称函数对象，意即具体函数性质的对象。
	STL的各种算法里经常用到仿函数，比如sort的第一个版本以operator < 为元素排序时的调整依据，第二个版本允许用户指定操作，使得排序后的两两相邻元素都满足该操作为true。
	要将某种操作当做算法的参数，唯一的办法是将该操作(可能拥有数条以上的指令)设计为一个函数，再将函数指针作为算法的参数；
	或者将该操作设计为一个仿函数，再以仿函数产生一个对象，以此对象作为算法的参数。

*** 那么，既然函数指针可以达到将这组操作当做算法的参数，那又何必用仿函数呢？
	原因在于函数指针毕竟不能满足STL对抽象性的要求，也不能满足软件积木的要求 --- 仿函数更灵活,抽象性更高
	——函数指针无法与STL其它组件搭配，产生更灵活的变化。

就实现观点而言，仿函数其实就是一个行为类似函数的对象。
	为了能够行为类似函数，其类别定义中必须自定义function call运算子(即operator())，拥有这样的运算子后，
	我们就可以在仿函数的对象后面加一个小括号，以此来调用仿函数所定义的operator()。

 */

/**
 * 
Compare: 比较器的类型，map中的元素是按照key来比较的，缺省情况下按照小于来比
较，一般情况下(内置类型元素)该参数不需要传递，如果无法比较时(自定义类型)，需要用户
自己显式传递比较规则(一般情况下按照函数指针或者仿函数来传递)
 * 
 */


//补充<array>
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
 * 但实际上vector用得会更多,vector也能越界检查,vector还能直接初始化:vector<int> v(10,0);
 * 主要差别是array是在栈上,vector是在堆里

array是栈上的，把C数组给“标准化”，有大小信息，不会弱化为指针，不可以动态扩大。vector管理堆内存，可以动态扩容。
array可以使用C的memset,memcpy等. vector不可以

 */


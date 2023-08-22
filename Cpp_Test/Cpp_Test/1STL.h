#pragma once

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
 * 2.算法
 * 3.迭代器(C++11)
 * 4.适配器/配接器(栈,队列)
 * 5.仿函数
 * 6.空间配置器(内存池)
 *
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


//仿函数(看起来像函数)  
/**
 * 仿函数(Functor)又称为函数对象(Function Object)
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
 */









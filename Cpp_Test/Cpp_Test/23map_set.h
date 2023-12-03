#pragma once
//
/**
 * C++98
 * 
 * 
 * map 和 set 底层是搜索二叉树 -- 平衡搜索二叉树
 * 基本功能:排序
 * 
 * set -对应- key模型
 * map -对应- key_value模型
 * 
 * map和set的迭代器函数实现都是一样的,begin和const begin一样,都是不可修改...
 * 
 * map和set逻辑是基本一样的,只是map多了一个value,但value不会对结构有影响,只在应用层面有差别
 * 
 */

//set
/**
 * 库:<set>
 * template < class T,class Compare = less<T>,class Alloc = allocator<T> > 
 * class set;
 * 
 * 基本功能:排序加去重
 * 
 * set的特点:
 * a.不允许重复:顾名思义,集合,集合有互异性,所以set的key不允许重复
 * b.不允许修改.底层是BST,修改会破坏BST的结构
 * 
 * Operators:
 * $. find
 * iterator find (const value_type& val) const;
 * 能找到则返回元素的迭代器,找不到则返回end()
 * $. count
 * size_t count (const value_type& val) const;
 * set中能找到则返回1,找不到则返回0
 * 
 * 
 */

/** multiset --multi_key_set
 * 头文件<set> -- 和set一样
 * 与set的结构区别:允许键值冗余 -- 允许重复键值 
 * 
 * 与set共性:排序,
 * 
 * 特点:
 * $ 可以使用set的迭代器(严格来说需要使用自己的迭代器..)
 * 
 * 与set的运用区别
 * $ 规定:find有重复值时,找的是中序遍历到的第一个key
 * $ multiset中的count价值大
 * 
 */

//map
/**
 * 认识map
 * 1.认识pair
 //pair的定义(键值对) --- 结构体 
template <class T1, class T2>
struct pair
{
	typedef T1 first_type;
	typedef T2 second_type;
	T1 first; //一般情况下,first是key , second是value
	T2 second;
	pair(): first(T1()), second(T2())
	{}
	pair(const T1& a, const T2& b): first(a), second(b)
	{}
};

//make_pair -- Other<utility> -- 实用类 -- pair的封装,方便实用pair
template <class T1,class T2>
  pair<T1,T2> make_pair (T1 x, T2 y) //函数模板,自动识别类型
  {
	return ( pair<T1,T2>(x,y) );
  }

 * 头文件<map>
 * 
 * map在逻辑结构中和set一样,key不能修改,但value可以修改.因为value与结构无关,只是附带值
 * 
 * 成员函数:
 * insert
 * $ pair<iterator,bool> insert (const pair<key_type,value_type>& p); 
 * //返回插入位置和插入信息的键值对pair
 * $ 如果插入失败,则返回已存在的key的位置的pair(iterator,false)
 * $ 如果插入成功,则返回新插入的key的位置的pair(iterator,true)
 * $ 插入与value无关,成功和失败只看key是否存在
 * 
 * erase
 * $ size_type erase (const key_type& k); // 返回已删除的个数
 * 
 * at
 * $ value_type& at(const key_type& k);  //返回key对应的value的引用
 * 
 * operator[] -- 强力函数
 * 1.查找 -- []  -- 已存在是查找  cout<<map[key]<<endl;
 * 2.插入 -- []  -- 不存在是插入 -- key是不存在的值则插入
 * 3.查找+修改   -- [] + =赋值 已有数据赋值
 * 4.查找+插入   -- [] + =赋值 未有数据
 * $ 等价于以下代码 (*((this->insert(make_pair(k,value_type()))).first)).second
 * ||代码分解
 * (*((this->insert(make_pair(k,value_type()))).first)).second //得到value的引用
 * *((this->insert(make_pair(k,value_type()))).first) //*it -- 得到相应结点pair(key,value)的引用
 * (this->insert(make_pair(k,value_type()))).first    //pair.first == iterator --> it
 * this->insert(make_pair(k,value_type()))            //返回pair(iterator,bool)
 * make_pair(k,value_type())
 * 
$ 模拟实现operator[]
template<class T1, class T2>
T2& operator[](const T1& key)
{
	std::pair<iterator,bool> ret = insert(make_pair(key, T2());
	return ret.first->second;
}
 * 
 * map的迭代器:
 * $ map的迭代器是双向迭代器
 *  -- 快排需要随机迭代器支持,所以map不能直接通过迭代器使用sort
 * 
 */

//multimap
/**
 * 和map区别，没有了operator[] -- 因为key和value没有一一映射关系了
 * .
 */








#pragma once
//
/**
 * 
 * map 和 set 底层是搜索二叉树 -- 平衡搜索二叉树
 * 基本功能:排序
 * 
 * set -对应- key模型
 * map -对应- key_value模型
 * 
 * map和set的迭代器函数实现都是一样的,begin和const begin一样,都是不可修改...
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
 //pair的定义(键值对)
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
 */






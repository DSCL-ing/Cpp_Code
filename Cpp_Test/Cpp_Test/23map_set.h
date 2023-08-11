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
 * 
 * 
 * 
 * 
 * a
 * 
 * 
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
 * 特点:允许键值冗余 -- 允许重复键值 
 * 
 * .
 */






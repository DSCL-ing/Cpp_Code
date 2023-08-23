#pragma once


#include<unordered_set>
#include<unordered_map>
#include<iostream>
using std::cout;
using std::endl;
using std::cin;
//unordered_set和unordered_map -- 还有multi共4中
/**
 * 
 * 
 * 和RBT的区别是
 * 1.unordered遍历是无序的
 * 2.unordered系列的底层是哈希表
 * 3.unordered是C++11更新的,RBT是C++98
 * 4.unordered是单向迭代器,RBT是双向迭代器
 * 
 * 优势:
 * $ 在不关注顺序,冗余比较大的情况下,hash更快,快很多,删除基本都比较快,插入可能有时慢一点.但大部分还是快.
 * $ 查找最快,,快了数量级,一骑绝尘
 * 劣势:有序情况下,删除和插入RBT快
 * 
 * 总结:综合情况下,hash更胜一筹,极端有序情况再使用RBT
 * 
 */

//哈希/散列
/**
 * hash是散列的意思,哈希表也可以叫散列表
 * 
 * .
 */

//哈希函数
/**
 * 1. 直接定址法--(常用) --直接映射,适合数据范围比较集中,直观
 * 优点：简单、均匀
 * 缺点：需要事先知道关键字的分布情况
 * 使用场景：适合查找比较小且连续的情况 ,如数组
 * 特点:每个元素都有唯一的key
 * 
 * 2. 除留余数法--(常用) --适合数据范围较为分散,空间零碎等
 * 设散列表中允许的地址数为m，取一个不大于m，但最接近或者等于m的质数p作为除数，
 * 按照哈希函数：Hash(key) = key% p(p<=m),将关键码转换成哈希地址
 * 
 * 
 */






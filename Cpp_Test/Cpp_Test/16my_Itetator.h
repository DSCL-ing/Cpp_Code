#pragma once


//迭代器适配器 -- 通用反向迭代器 ,任何容器的迭代器都可以适配出反向迭代器
/**
 * 原理:
 * 成员为正向迭代器,接收正向迭代器初始化
 * 通过调用正向迭代器的运算符重载,
 * 控制正向迭代器进行反向操作
 * 
 * 
 * .
 */
#include<iostream>
using std::cout;
using std::endl;
using std::cin;
namespace test
{
	template<class Iterator, class Ref, class Ptr>
	struct ReverseIterator
	{
		typedef ReverseIterator<Iterator, Ref, Ptr> Self;
		Iterator _cur;
		ReverseIterator(Iterator it)//不能加引用,因为end()是一个正向迭代器的匿名对象,匿名对象传引用接收需要加const,否则不支持.
			:_cur(it)				//但是迭代器对象不允许加const,所以使用了传值传参
		{}

		Ref operator*()
		{
			Iterator tmp = _cur;
			--tmp;
			return *tmp;
		}
		Ptr operator->()
		{
			Iterator tmp = _cur;
			--tmp;
			return &(*tmp);
		}
		Self& operator++()
		{
			--_cur;
			return *this;
		}
		Self operator++(int)
		{
			Self tmp = *this;
			--_cur;
			return tmp;
		}
		Self& operator--()
		{
			++_cur;
			return *this;
		}
		Self operator--(int)
		{
			Self tmp = *this;
			++_cur;
			return tmp;
		}
		bool operator!=(const Self& s) //库中传的也是Self ,引文rend是反向迭代器,所以参数类型也是Self
		{
			return _cur != s._cur;
		}

	};
}



#pragma once


//迭代器适配器 -- 通用反向迭代器 ,任何容器的迭代器都可以适配出反向迭代器
/**
 * 
 * 
 * .
 */
#include<iostream>
using std::cout;
using std::endl;
using std::cin;
template<class Iterator, class Ref , class Ptr>
class ReverseIterator
{
private:
	Iterator _cur;
public:
	typedef ReverseIterator<Iterator> Self;
	ReverseIterator(Iterator& it)
		:_cur(it)
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
	bool operator!=(const Slef& s) //库中传的也是Self
	{
		return _cur != s._cur;
	}

};



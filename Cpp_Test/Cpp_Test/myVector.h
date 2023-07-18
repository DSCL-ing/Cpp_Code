﻿
//note
//参照string

//C++二维vector (和二维数组不一样,与数组类似,用法超越了二维数组)
/**
 * 二维vector逻辑结构
 * ----------行-------------
 * 列列列列列列列列列列列列
 *
 * vector<vector<int>> vv ;
 * vector<int>() //匿名对象,用于二维vector初始化
 * 访问二维vector,vv[]是范围二维vector的元素,vv[][]是访问二维vector的元素的元素
 * resize(i,vector<int>()) //开辟i个,类型为vector<int>的空间 //一般用于开辟二维vector的行和列
 *
 * //vector训练
 * https://leetcode.cn/problems/pascals-triangle/submissions/
 *
 */

 //iterator
 /**
  * 迭代器失效问题 - 原数据修改后需要重新初始化迭代器
  *
  * .
  */

  //capacity
  /**
   * resize()
   * vector的resize使用得更频繁, 支持开空间加初始化
   * .
   */

   //Modifiers
   /**
	* vector也不推荐使用insert和erase
	* .
	*/

	//operator
	/**
	 * vector不提供find,推荐使用std::find(),string中有find是因为string的需求
	 * 使用#include<algorithm>中的find
	template<class InputIterator, class T>
	  InputIterator find (InputIterator first, InputIterator last, const T& val)
	{
	  while (first!=last) {
		if (*first==val) return first;
		++first;
	  }
	  return last;
	}
	 *
	 *
	 *
	 */

#pragma once
#include<assert.h>
//模板参数省略:1.作为时  2.作为类型名
template <typename T> //数组名:类型名:xx数组
class vector
{
public:
	//成员类型 //也可以用内部类,但C++都是typedef居多,不喜欢内部类
	typedef T* iterator; 
	typedef const T* const_iterator;
private:
	//构造函数太多,初始化列表重复太多麻烦,直接给缺省参数方便//C++11
	iterator _start = nullptr; //数组头
	iterator _finish = nullptr;//数组有效数据尾的下一个(类似\0位置)
	iterator _end_of_storage = nullptr;//数组容量尾的下一个位置

public:
	//无参构造
	vector()
	{}
	//有参构造:开辟n个空间,1.数量 2开辟对象空间
	vector(size_t n , const T& val= T()) //缺省值为显式匿名构造,基本类型也支持
		//:_start(nullptr)
		//,_finish(nullptr)
		//,_end_of_strorage(nullptr)
	{
		_start =  new T[n];
		_finish = _start + n;
		_end_of_storage = _start + n;
		for (size_t i = 0; i < n; ++i)
		{
			_start[i] = val;
		}
	}
	//整型重载构造
	vector(int n, const T& val = T())
		//:_start(nullptr)
		//,_finish(nullptr)
		//,_end_of_storage(nullptr)
	{
		_start =  new T[n];
		_end_of_storage = _start + n; 
		_finish = _start + n;
		for (int i = 0; i < n; ++i)
		{
			_start[i] = val;	
		}
	}
	//迭代器构造
	template <typename InputIterator>
	vector(InputIterator first , InputIterator last)
		//:_start(nullptr)
		//,_finish(nullptr)
		//,_end_of_storage(nullptr)
	{
		size_t sz = last - first;
		_start = _finish = new T[sz];
		_finish = _start + sz;
		_end_of_storage = _start + sz; 
		while (first!=last)
		{
			*_finish = *first;
			++first;
		}
	}

	//拷贝构造
	vector(const vector<T>& v)
		//:_start(nullptr)
		//, _finish(nullptr)
		//, _end_of_storage(nullptr)
	{

		_start = _finish = new T[v.capacity()];
		_finish = _start + v.size();
		_end_of_storage = _start + v.capacity();
		for (size_t i = 0; i < v.size(); ++i)
		{
			_start[i] = v._start[i];
		}
	}

	vector<T>& operator=(const vector<T>& v) //深拷贝的核心
	{
		//_start =  new T[v.capacity()];
		reserver(v.capacity());
		for (int i = 0; i < v.size(); ++i)
		{
			_start[i] = v._start[i];
		}
		_finish = _start + v.size();
		_end_of_storage = _start + v.capacity();
		return *this;
	}

	~vector()
	{
		delete[] _start;
		_start = _finish = nullptr;
	}

	iterator begin()
	{
		return _start;
	}

	iterator end() 
	{
		return _finish;
	}
	const_iterator begin() const
	{
		return _start;
	}
	const_iterator end() const
	{
		return _finish;
	}

	//Capacity
	size_t capacity() const
	{
		return _end_of_storage - _start;
	}
	size_t size() const
	{
		return _finish - _start;
	}
	bool empty() const
	{
		return _start == _finish;
	}
	iterator& operator[](size_t pos) //_start的类型是迭代器,所以返回迭代器
	{
		assert(pos < size());
		return _start[pos];
	}
	const const_iterator& operator[](size_t pos)const
	{
		assert(pos < size());
		return _start[pos];
	}

	void resize(size_t n ,const T& val = T())
	{
		if (n < size())
		{
			_finish = _start + n;
		}
		else
		{
			if (n > capacity())
			{
				reserve(n);
			}
			for (size_t i = size()  ; i <= n; ++i)
			{
				_start[i] = val;
				++_finish;
			}
				//while (_finish != _start + n)
			//{
			//	*finish = val;
			//	++_finish;
			//}
		}
	}

	void reserve(size_t n) //扩容
	{
		if (n > capacity())
		{
			size_t sz = size();
			T* tmp = new T[n];
			//memcpy()//可能会有浅拷贝
			for (size_t i = 0; i < sz; ++i)
			{
				tmp[i] = _start[i];
			}
			delete[] _start;
			_start = tmp;
			_finish = _start + sz; //必须放在后面,因为size与_finish有关
			_end_of_storage = _start + n;
		}
	}

	void push_back(const T& x)//尾插
	{
		if (_finish == _end_of_storage)
		{
			reserve(capacity() == 0 ? 4 : capacity());
		}
		*_finish = x;
		++_finish;
	}
	
	void pop_back() //尾删
	{
		//if (empty())
		//{
		//	return;
		//}
		assert(!empty());
		--_finish;
	}

	iterator insert(iterator pos ,const T& val)//插入//返回原来插入的位置
	{
		assert(pos >= _start);
		assert(pos<=_finish);
		if (_finish == _end_of_storage)//reserve后迭代器失效
		{
			size_t sz = _finish - _start;
			reserve(capacity() == 0 ? 4 : capacity() * 2);
			pos = _start + sz;
		}
		iterator end = _finish; //减少用end
		while (pos != end)
		{
			*(end) = *(end-1);
			--end;
		}
		*pos = val;
		++_finish;
		return pos; //防止迭代器可能因为扩容而失效,因此将迭代器作为返回值

	}
	iterator erase(iterator pos)//删除 //返回删除的下一个位置
	{
		assert(!empty());
		iterator begin = pos+1; //增加用begin
		while (begin != _finish)
		{
			*(begin - 1) = *begin;
			++begin;
		}
		
		--_finish;
		return pos;
	 }

	




};

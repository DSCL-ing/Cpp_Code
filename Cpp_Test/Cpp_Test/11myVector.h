﻿
//note
//参照string


//vector的使用
/**
 * $顺序表的插入和二维vector
 * 原则:遵循尾插(自动扩容),其他情况容易越界
 *   无论几维vector,只要是一步一步尾插的,都不会越界
 *
 * 对于二维vector的使用案例
方法1:
	vv.push_back(vector<int>()); //先尾插入一行
	vv[i].push_back(int_value); //再尾插入列
方法2:
	v.push_back(int_value);   //先把一维数组插满
	vv.push_back(v);		  //再插入一维数组v
 *
 *
 * $vector有顺序表的特性
 * vector 和顺序表一样,必须从到尾依次插入,不能访问有效数据之后的位置(size后面的空位置不能访问)
 * 即size到capacity之间的空间是不允许访问的,只能访问size之内的数据
 *
 *
 * $ vector的建立和扩容
 * vector的实例方法:通过类型实例化,通过resize扩容空间 -- C++少使用new
 *
 *
 * $ vector的swap,交换两个数组内容 -- 需要交换vector时使用
 * 交换vector内的三个指针 == 3个std::swap
 *
 *
 */

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

  //构造函数
  /**
   *  explicit vector (const allocator_type& alloc = allocator_type());
   * // vector<> v; //nullptr
   *
   *  explicit vector (size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type());
   * // vector<> v(n,val); //init n identical  value  n个相同的值
   *
   *  template <class InputIterator>
   *       vector (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type());
   *  //vector<> v(begin,end);
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
	 * $resize()
	 * vector的resize使用得更频繁, 支持开空间加初始化 -- 能满足扩容后的空间随机访问
	 *
	 *
	 * $reserve只能扩容,不初始化,不能访问未初始化的空间
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
#include<iostream>
using std::cout;
using std::endl;
using std::cin;

namespace test
{



	//#include<algorithm>
	//模板参数省略:1.作为时  2.作为类型名
	template <class T> //数组名:类型名:xx数组
	class vector
	{
	public:
		//成员类型 //也可以用内部类,但C++都是typedef居多,不喜欢内部类
		//typedef T* iterator;
		//typedef const T* const_iterator;
		using iterator = T*;
		using const_iterator = const T*;
	private:
		//构造函数太多,初始化列表重复太多麻烦,直接给缺省参数方便//C++11
		iterator _start = nullptr; //数组头
		iterator _finish = nullptr;//数组有效数据尾的下一个(类似\0位置)
		iterator _end_of_storage = nullptr;//数组容量尾的下一个位置,有效空间的下一个位置

	public:
		//无参构造
		vector()
		{}
		//有参构造:开辟n个空间,1.数量 2开辟对象空间
		vector(size_t n, const T& val = T()) //缺省值为显式匿名构造,基本类型也支持
		{
			//_start = new T[n];
			//_finish = _start + n;
			//_end_of_storage = _start + n;
			//for (size_t i = 0; i < n; ++i)
			//{
			//	_start[i] = val;
			//}
			reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				push_back(val);
			}
		}
		//有参构造整型重载
		vector(int n, const T& val = T())

		{
			reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				push_back(val);
			}
		}
		//迭代器构造
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)

		{
			//size_t sz = last - first;
			//_start = _finish = new T[sz];
			//while (first != last)
			//{
			//	*_finish = *first;
			//	++first;
			//	++_finish;
			//}
			//_end_of_storage = _start + sz;
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		//C++11 initializer_list 构造
		vector(std::initializer_list<T> il) //常量不能引用
		{
			//两种写法
			//typename std::initializer_list<T>::iterator it = il.begin();
			//while (it != il.end())
			//{
			//	push_back(*it);
			//	++it;
			//}

			for (auto e : il)
			{
				push_back(e);
			}
		}

		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}

		//拷贝构造
		vector(const vector<T>& v)
		{
			//_start = new T[v.capacity()];
			//for (size_t i = 0; i < v.size(); ++i)
			//{
			//	_start[i] = v._start[i];//这里可能用到重载=,从而实现深拷贝
			//}
			//_finish = _start + v.size();
			//_end_of_storage = _start + v.capacity();
			vector<T> tmp(v.begin(), v.end());
			swap(tmp);

		}

		void swap(vector<T>& v)
		{
			//不能使用赋值,死循环
			//_start = v._start;
			//_finish = v._finish;
			//_end_of_storage = v._end_of_storage;

			//由于是拷贝的空间,且不能使用赋值,故交换掉,原先的会释放掉,
			//旧空间已经交换给v了,v会在出了作用域后回收,所以不用手动释放
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}

		vector<T>& operator=(vector<T> v) //深拷贝
			//赋值运算符重载：操作数是vector<vector<>>,在非初始化时走这里，初始化时时拷贝构造
			//传值传参，v是拷贝，所以是再次调了拷贝构造,新空间了,所以相当于深拷贝
		{
			swap(v);
			return *this;
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
		T& operator[](size_t pos) //_start的类型是对象,所以返回迭代器
		{
			assert(pos < size());
			return _start[pos];
		}
		const T& operator[](size_t pos)const
		{
			assert(pos < size());
			return _start[pos];
		}

		void resize(size_t n, const T& val = T())
		{
			if (n > capacity())
			{
				reserve(n);
			}

			if (n > size())
			{
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
			else
			{
				_finish = _start + n;
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
				_finish = tmp + sz; //必须放在后面,因为size与_finish有关
				_end_of_storage = tmp + n;
			}
		}

		void push_back(const T& x)//尾插
		{
			if (_finish == _end_of_storage)
			{
				size_t newCapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newCapacity);
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

		iterator insert(iterator pos, const T& val)//插入//返回原来插入的位置
		{
			assert(pos >= _start);
			assert(pos <= _finish);
			if (_finish == _end_of_storage)//reserve后迭代器失效
			{
				size_t len = _end_of_storage - _start;
				size_t newCapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newCapacity);

				pos = _start + len;				// 扩容会导致pos迭代器失效，需要更新处理一下
			}
			iterator end = _finish; //减少用end
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = val;
			++_finish;
			return pos; //防止迭代器可能因为扩容而失效,因此将迭代器作为返回值

		}
		iterator erase(iterator pos)//删除 //返回删除的下一个位置
		{
			assert(pos >= _start);
			assert(pos < _finish);
			iterator begin = pos + 1; //增加用begin
			while (begin != _finish)
			{
				*(begin - 1) = *begin;
				++begin;
			}

			--_finish;
			return pos;
		}
	};

	//测试用例
	class Solution {
	public:
		vector<vector<int>> generate(int numRows) {
			vector<vector<int>> vv;
			vv.resize(numRows, vector<int>());

			for (size_t i = 0; i < vv.size(); ++i)
			{
				vv[i].resize(i + 1, 0);
				vv[i][0] = vv[i][vv[i].size() - 1] = 1;

				for (size_t j = 0; j < vv[i].size(); ++j)
				{
					if (vv[i][j] == 0)
					{
						vv[i][j] = vv[i - 1][j - 1] + vv[i - 1][j];
					}
				}
			}
			return vv;
		}
	};

	void test_vector4()
	{
		using namespace std;
		vector<vector<int>> vv = Solution().generate(3);
		for (size_t i = 0; i < vv.size(); ++i)
		{
			for (size_t j = 0; j < vv[i].size(); ++j)
			{
				cout << vv[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;

		vector<vector<int>> v3 = vv;//初始化=是拷贝构造 ,深拷贝过程中=是重载
		for (size_t i = 0; i < v3.size(); ++i)
		{
			for (size_t j = 0; j < v3[i].size(); ++j)
			{
				cout << v3[i][j] << " ";
			}
			cout << endl;
		}

		vector<int> v1;
		v1.resize(3, 1);
		vector<int> v2 = v1; //初始化=是拷贝构造
		for (auto e : v2)
		{
			cout << e << " ";
		}
	}

	void test_vector5()
	{
		vector<int> v = { 1,2,3,4,5 }; //initializer_list 初始化

	}



}



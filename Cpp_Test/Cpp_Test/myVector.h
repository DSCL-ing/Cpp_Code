#pragma once
#include<assert.h>
//模板参数省略:1.作为时  2.作为类型名
template <typename T> //数组名:类型名:xx数组
class vector
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
private:
	//构造函数太多,初始化列表重复太多麻烦,直接给缺省参数方便
	iterator _start = nullptr; //数组头
	iterator _finish = nullptr;//数组有效数据尾的下一个(类似\0位置)
	iterator _end_of_storage = nullptr;//数组容量尾

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

	vector<T>& operator=(const vector<T>& v)
	{
		_start =  new T[v.capacity()];
		_finish = _start + v.size();
		_end_of_storage = _start + v.capacity();
		for (int i = 0; i < v.size(); ++i)
		{
			_start[i] = v._start[i];
		}
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
			for (size_t i =size() ; i <= n; ++i)
			{
				_start[i] = val;
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

	iterator insert(iterator pos ,const T& val)//插入
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
	iterator erase(iterator pos)//删除
	{
		assert(!empty());
		iterator begin = pos+1; //增加用begin
		while (begin != _finish)
		{
			*(pos - 1) = *pos;
			++begin;
		}
		--_finish;
		return pos;
	 }

	




};

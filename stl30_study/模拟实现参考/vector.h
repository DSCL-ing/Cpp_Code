#pragma once

namespace bit
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

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

		T& operator[](size_t pos)
		{
			assert(pos < size());
			return _start[pos];
		}

		const T& operator[](size_t pos) const
		{
			assert(pos < size());
			return _start[pos];
		}

		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}

		// v2(v1)
		/*vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			reserve(v.capacity());
			for (const auto& e : v)
			{
				push_back(e);
			}
		}*/

		//vector<int> v1(10, 1);
		//vector<char> v1(10, 'A');

		vector(int n, const T& val = T())
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			reserve(n);
			for (int i = 0; i < n; ++i)
			{
				push_back(val);
			}
		}

		vector(size_t n, const T& val = T())
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				push_back(val);
			}
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			vector<T> tmp(v.begin(), v.end());
			swap(tmp);
		}

		// v1 = v2
		// v1 = v1;  // 极少数情况，能保证正确性，所以这里就这样写没什么问题
		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}

		~vector()
		{
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}

		// 17:12继续
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t oldSize = size();
				T* tmp = new T[n];

				if (_start)
				{
					//memcpy(tmp, _start, sizeof(T)*oldSize);
					for (size_t i = 0; i < oldSize; ++i)
					{
						tmp[i] = _start[i];
					}

					delete[] _start;
				}

				_start = tmp;
				_finish = tmp + oldSize;
				_endofstorage = _start + n;
			}
		}

		void resize(size_t n, T val = T())
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

		bool empty() const
		{
			return _finish == _start;
		}

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _endofstorage - _start;
		}

		void push_back(const T& x)
		{
			if (_finish == _endofstorage)
			{
				size_t newCapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newCapacity);
			}

			*_finish = x;
			++_finish;
		}

		void pop_back()
		{
			assert(!empty());

			--_finish;
		}

		// 迭代器失效 : 扩容引起，野指针问题
		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= _start);
			assert(pos < _finish);

			if (_finish == _endofstorage)
			{
				size_t len = pos - _start;
				size_t newCapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newCapacity);

				// 扩容会导致pos迭代器失效，需要更新处理一下
				pos = _start + len;
			}

			// 挪动数据
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}

			*pos = val;
			++_finish;

			return pos;
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);


			iterator begin = pos+1;
			while (begin < _finish)
			{
				*(begin-1) = *(begin);
				++begin;
			}

			--_finish;

			return pos;
		}
		
		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}

		void clear()
		{
			_finish = _start;
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};

	void test_vector1()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);

		for (size_t i = 0; i < v.size(); ++i)
		{
			cout << v[i] << " ";
		}
		cout << endl;

		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;

		v.pop_back();
		v.pop_back();
		v.pop_back();
		v.pop_back();
		v.pop_back();

		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void test_vector2()
	{
		vector<int> v;
		v.resize(10, -1);
		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;

		v.resize(5);
		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void test_vector3()
	{
		vector<int> v;
		//v.reserve(10);
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);

		for (size_t i = 0; i < v.size(); ++i)
		{
			cout << v[i] << " ";
		}
		cout << endl;

		v.insert(v.begin(), 0);
		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;

		vector<int>::iterator it = find(v.begin(), v.end(), 3);
		if (it != v.end())
		{
			v.insert(it, 30);
		}
		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void test_vector4()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);

		vector<int>::iterator it = find(v.begin(), v.end(), 3);
		if (it != v.end())
		{
			v.insert(it, 30);
		}

		// insert以后 it还能否继续使用 -- 不能，可能迭代器失效（野指针）
		//(*it)++;
		//*it *= 100;

		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void test_vector5()
	{
		std::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);

		// it失效还是不失效？
		std::vector<int>::iterator it = find(v.begin(), v.end(), 3);
		if (it != v.end())
		{
			v.erase(it);
		}

		// 读 
		cout << *it << endl;
		// 写
		(*it)++;

		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	//void test_vector6()
	//{
	//	// 要求删除所有偶数
	//	std::vector<int> v;
	//	v.push_back(1);
	//	v.push_back(2);
	//	v.push_back(2);
	//	v.push_back(3);
	//	v.push_back(4);

	//	std::vector<int>::iterator it = v.begin();
	//	while (it != v.end())
	//	{
	//		if (*it % 2 == 0)
	//		{
	//			it = v.erase(it);
	//		}
	//		else
	//		{
	//			++it;
	//		}
	//	}

	//	for (auto e : v)
	//	{
	//		cout << e << " ";
	//	}
	//	cout << endl;
	//}

	void test_vector6()
	{
		// 要求删除所有偶数
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		//v.push_back(5);


		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			if (*it % 2 == 0)
			{
				it = v.erase(it);
			}
			else
			{
				++it;
			}		
		}

		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	// 休息21:10继续
	void test_vector7()
	{
		// 要求删除所有偶数
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);

		vector<int> v1(v);

		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;

		vector<int> v2;
		v2.push_back(10);
		v2.push_back(20);
		v1 = v2;
		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;

		v1 = v1;
		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void test_vector8()
	{
		std::string str("hello");

		// 要求删除所有偶数
		vector<int> v(str.begin(), str.end());
		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;

		//vector<int> v1(v.begin(), v.end());
		vector<int> v1(10, 1);
		//vector<char> v1(10, 'A');

		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;
	}


	class Solution {
	public:
		vector<vector<int>> generate(int numRows) {
			vector<vector<int>> vv;
			vv.resize(numRows);
			for (size_t i = 0; i < vv.size(); ++i)
			{
				vv[i].resize(i + 1, 0);
				vv[i][0] = vv[i][vv[i].size() - 1] = 1;
			}

			for (size_t i = 0; i < vv.size(); ++i)
			{
				for (size_t j = 0; j < vv[i].size(); ++j)
				{
					if (vv[i][j] == 0)
					{
						vv[i][j] = vv[i - 1][j] + vv[i - 1][j - 1];
					}
				}
			}

			return vv;
		}
	};

	void test_vector9()
	{
	/*	vector<vector<int>> vvRet = Solution().generate(5);

		for (size_t i = 0; i < vvRet.size(); ++i)
		{
			for (size_t j = 0; j < vvRet[i].size(); ++j)
			{
				cout << vvRet[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;*/

		vector<vector<int>> vv;
		vector<int> v(5, 1);
		vv.push_back(v);
		vv.push_back(v);
		vv.push_back(v);
		vv.push_back(v);
		vv.push_back(v);

		for (size_t i = 0; i < vv.size(); ++i)
		{
			for (size_t j = 0; j < vv[i].size(); ++j)
			{
				cout << vv[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}
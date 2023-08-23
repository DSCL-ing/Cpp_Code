#pragma once

#include"26RBT_container.h"
namespace test
{


	template<class K>
	class set
	{

	private:
		struct setKeyOfT//命名? 返回RBT的类型T接收的 set的key
		{
			const K& operator()(const K& key) //类似函数重载
			{
				return key; //返回key --重载原函数
			}
		};
	private:
		RBTree< K, K, setKeyOfT>_t;
	public:
		//使用类域的要加typename,以防和静态变量冲突
		typedef typename RBTree<K, K, setKeyOfT>::const_iterator iterator; //普通迭代器
		typedef typename RBTree<K, K, setKeyOfT>::const_iterator const_iterator; //const迭代器
	/**
	 * set中因为key不能修改,所以RBT的模板参数T位置需要是const K,但是,const迭代器中的是const T,使用const K的话会const迭代器变成const const K
	 * 解决:set的普通迭代器也使用const迭代器
	 *
	 */

		iterator begin()const
		{
			return _t.begin(); //begin是普通迭代器,返回值是const,发生隐式类型转换(单参数)
			//如果有相应的构造函数,则支持隐式类型转换 ,但此时迭代器没有参数为迭代器的构造函数,需要添加
			//
		}
		iterator end()const
		{
			return _t.end();
		}

		const_iterator begin()const
		{
			return _t.begin();
		}
		const_iterator end()const
		{
			return _t.end();
		}

		

	public:
		pair<iterator, bool> insert(const K& key)
		{
			return _t.insert(key);
		}


	};

	void test_mySet1()
	{
		test::set<int> s;
		s.insert(2);
		s.insert(1);
		s.insert(3);

		set<int>::iterator it = s.begin();
		//while (it!=s.end())
		//{
		//	cout << *it << " ";
		//	++it;
		//}
		for (auto& e : s)
		{
			cout << e << " ";
		}
		cout << *++it << " ";
		cout << *--it << " ";
		cout << endl;
		

	}
}







﻿#pragma once

#include"26RBT_container.h"
namespace test
{
	template<class K,class V>
	class map
	{
	private:
		struct mapKeyOfT//命名? 返回RBT的类型T接收的 map的key
		{ 
			const K& operator()(const pair<const K,V>& kv) //类似函数重载
			{
				return kv.first; //返回pair的key
			}
		};
	private:
		RBTree<K, pair<const K, V>, mapKeyOfT> _t;
	public:
		typedef typename RBTree<K, pair<const K,V>, mapKeyOfT>::iterator iterator; //使用类域的要加typename,以防和静态变量冲突

		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}

	public:
		bool insert(const pair<const K, V>& kv)
		{
			return _t.insert(kv);
		}

	};

	void test_myMap1()
	{
		test::map<int, int> m;
		m.insert(std::make_pair(1, 1));
		m.insert(std::make_pair(3, 3));
		m.insert(std::make_pair(2, 2));
		test::map<int,int>::iterator it = m.begin();
		//while (it != m.end())
		//{
		//	cout << it->first << " ";
		//	++it;
		//}
		for (auto e : m)
		{
			cout << e.first << " ";
		}

		cout << (++it)->first << " ";
		cout << (--it)->first << " ";
		cout << endl;

	}

	void test_myMap2()
	{
			//map的使用
	map<std::string, std::string>  dict;
	dict.insert(std::pair<std::string, std::string>("sort", "排序")); //匿名对象插入
	dict.insert(std::make_pair("string", "字符串"));    //pair封装插入
	dict.insert(std::make_pair("count", "计数"));
	dict.insert(std::make_pair("count", "(计数)")); //插入失败的
	auto it = dict.begin();
	while (it != dict.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	}

}



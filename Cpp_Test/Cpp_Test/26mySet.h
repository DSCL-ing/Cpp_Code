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
		RBTree<K, K, setKeyOfT>_t;
	public:
		typedef typename RBTree<K, K, setKeyOfT>::iterator iterator; //使用类域的要加typename,以防和静态变量冲突
		
		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}



		

	public:
		bool insert(const K& key)
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

		//set<int>::iterator it = s.begin();
		//while (it!=s.end())
		//{
		//	cout << *it << " ";
		//	++it;
		//}
		for (auto& e : s)
		{
			cout << e << " ";
		}
		

	}
}







#pragma once

#include"26RBT_container.h"
namespace test
{
	template<class K,class V>
	class map
	{
	private:
		struct mapKeyOfT//命名? 返回RBT的类型T接收的 map的key
		{ 
			operator()(const pair<K,T>& kv) //类似函数重载
			{
				return kv.first; //返回pair的key
			}
		};
	private:
		RBTree<K, T, mapKeyOfT>_t;
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
		bool insert(const pair<K, T>& kv)
		{
			return _t.insert(kv);
		}


	};

}







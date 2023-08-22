#pragma once

#include"26RBT_container.h"
namespace test
{
	template<class K,class V>
	class map
	{
		struct mapKeyOfT//命名? 返回RBT的类型T接收的 map的key
		{ 
			operator()(const pair<K,T>& kv) //类似函数重载
			{
				return kv.first;
			}
		};

		bool insert(const pair<K, T>& kv)
		{
			return _t.insert(kv);
		}

	private:
		RBTree<K, T, mapKeyOfT>_t;
	};

}







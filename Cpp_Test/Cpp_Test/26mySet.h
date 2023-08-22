#pragma once

#include"26RBT_container.h"
namespace test
{
	template<class K>
	class set
	{
		struct setKeyOfT//命名? 返回RBT的类型T接收的 set的key
		{
			operator()(const K& key) //类似函数重载
			{
				return key;
			}
		};

		bool insert(const K& key)
		{
			return _t.insert(key);
		}

	private:
		RBTree<K, K, setKeyOfT>_t;
	};

}







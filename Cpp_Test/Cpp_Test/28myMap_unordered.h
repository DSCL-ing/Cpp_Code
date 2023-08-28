#pragma once
#pragma once

#include"28hashtable_container.h"
namespace test
{
	template<class K,class V>
	class unordered_map
	{
	private:
		struct mapKeyOfT
		{
			const K& operator()(const pair<const K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		bool insert(const pair<K, V> kv)
		{
			return _ht.insert(kv);
		}

	private:
		HashBucket::HashTable<K, pair<const K, V>, mapKeyOfT> _ht;

	}; //unordered_map_end

	void test_My_unordered_map1()
	{
		test::unordered_map<int, int> m;
		m.insert(make_pair(1, 1));
	}
}



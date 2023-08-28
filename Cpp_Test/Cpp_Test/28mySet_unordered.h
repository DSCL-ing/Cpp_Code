#pragma once
#pragma once

#include"28hashtable_container.h"

namespace test
{
	
	template<class K>
	class unordered_set
	{
	public:
		 struct setKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		bool insert(const K& key)
		{
			return _ht.insert(key);
		}

	private:
		HashBucket::HashTable<K, K, setKeyOfT> _ht;

	}; //unordered_set_end;

	void test_My_unordered_set1()
	{
		test::unordered_set<int> s;
		s.insert(1);
	}


}







#pragma once
#pragma once

#include"28hashtable_container.h"

namespace test
{
	//template < 
	// class Key,                        // unordered_set::key_type/value_type
	//	class Hash = hash<Key>,           // unordered_set::hasher
	//	class Pred = equal_to<Key>,       // unordered_set::key_equal
	//	class Alloc = allocator<Key>      // unordered_set::allocator_type
	//> class unordered_set;

	template<class K, class Hash = HashBucket::HashFunc<K>>
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
		HashBucket::HashTable<K, K, setKeyOfT , Hash> _ht;

	}; //unordered_set_end;

	void test_My_unordered_set1()
	{
		test::unordered_set<int> s;
		s.insert(1);
	}


}







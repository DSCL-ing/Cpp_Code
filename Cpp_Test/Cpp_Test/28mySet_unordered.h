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
	private:
		 struct setKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename HashBucket::HashTable<K, K, setKeyOfT, Hash>::const_iterator iterator;
		typedef typename HashBucket::HashTable<K, K, setKeyOfT, Hash>::const_iterator const_iterator;

	public:
		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}
		const_iterator begin()const
		{
			return _ht.begin();
		}

		const_iterator end()const
		{
			return _ht.end();
		}

		bool insert(const K& key)
		{
			return _ht.insert(key);
		}

		iterator find(const K& key)
		{
			node* cur = _ht.find(key);
		}

	private:
		HashBucket::HashTable<K, K, setKeyOfT , Hash> _ht;

	}; //unordered_set_end;

	void test_My_unordered_set1()
	{
		int a[] = { 3, 33, 2, 13, 5, 12, 1002 };

		test::unordered_set<int> s;
		//s.insert(1);
		
		for (auto i : a)
		{
			s.insert(i);
		}

		test::unordered_set<int>::iterator it = s.begin();
		while (it!=s.end())
		{
			cout << *it << endl;
			++it;
		}

	}


}







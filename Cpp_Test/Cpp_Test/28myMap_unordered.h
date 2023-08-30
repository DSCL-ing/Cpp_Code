#pragma once
#pragma once

#include"28hashtable_container.h"
namespace test
{
	//template < class Key,                                    // unordered_map::key_type
	//	class T,                                      // unordered_map::mapped_type
	//	class Hash = hash<Key>,                       // unordered_map::hasher
	//	class Pred = equal_to<Key>,                   // unordered_map::key_equal
	//	class Alloc = allocator< pair<const Key, T> >  // unordered_map::allocator_type
	//> class unordered_map;

	template<class K,class V,class Hash = HashBucket::HashFunc<K>>
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
		typedef typename HashBucket::HashTable<K, pair<const K, V>, mapKeyOfT, Hash>::iterator iterator;
		typedef typename HashBucket::HashTable<K, pair<const K, V>, mapKeyOfT, Hash>::const_iterator const_iterator;

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

		
		pair<iterator,bool> insert(const pair<K, V> kv)
		{
			return _ht.insert(kv);
		}

		V& operator[](const K& key)
		{
			pair<iterator,bool> ret = insert(make_pair(key, V()));
			return ret.first->second;
		}

	private:
		HashBucket::HashTable<K, pair<const K, V>, mapKeyOfT, Hash> _ht;

	}; //unordered_map_end

	void test_My_unordered_map1()
	{
		unordered_map<int, int> m;
		m.insert(make_pair(1, 1));
		m.insert(make_pair(3, 3));
		m.insert(make_pair(2, 2));

		//unordered_map<int, int>::const_iterator it = m.begin(); //测试没问题
		unordered_map<int, int>::iterator it = m.begin();
		while (it != m.end())
		{
			//it->first = 1;
			//it->second = 1;

			cout << it->first << ":" << ++it->second << endl;
			++it;
		}
		cout << endl;
	}

	void test_My_unordered_map2()
	{
		std::string arr[] = { "西瓜", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉", "梨" };
		unordered_map<std::string, int> countMap;
		for (auto& e : arr)
		{
			countMap[e]++;
		}

		for (auto& kv : countMap)
		{
			cout << kv.first << ":" << kv.second << endl;
		}
	}

}



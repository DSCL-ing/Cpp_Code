#pragma once

#include"28hashtable_container.h"
#include"1Date.h"//测试用



namespace test
{
	//template < class Key,                                    // unordered_map::key_type
	//	class T,                                      // unordered_map::mapped_type
	//	class Hash = hash<Key>,                       // unordered_map::hasher      //用于支持取模的仿函数
	//	class Pred = equal_to<Key>,                   // unordered_map::key_equal   //用于支持==重载的仿函数
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
			return ret.first->second; //模拟的是指针,ret.first是iterator,iterator->可以直接访问到node的成员
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


	struct HashDate
	{
		size_t operator()(const Date& d)
		{
			size_t ret = 0;
			ret += d._year;
			ret *= 31;
			ret += d._month;
			ret *= 31;
			ret += d._day;
			ret *= 31;
			return ret;
		}
	};

	void test_My_unordered_map3()
	{

	   // 自定义类型作map,set的key需要支持比较大小(需要重载<) ,只需要重载一个 '<' 或 '>' 就可以比较大小 ,
		//自定义类型作unordered的key需要满足1.要有可以取模的对象 2.支持比较是否相等,hashtable需要比较key(需要重载==)
		/**
		 * stl::如果作为哈希key的自定义类型不支持等于,stl的哈希map支持传仿函数 class Pred = equal_to<Key>用于自己适配
		 * 
		 */

		Date d1(2023, 3, 13);
		Date d2(2023, 3, 13);
		Date d3(2023, 3, 12);
		Date d4(2023, 3, 11);
		Date d5(2023, 3, 12);
		Date d6(2023, 3, 13);

		Date a[] = { d1,d2,d3,d4,d5 ,d6};

		unordered_map<Date, int, HashDate> m;

		for (auto& e : a)
		{
			++m[e];
		}

		for (auto& kv : m)
		{
			cout << kv.first << ":"<<kv.second << endl;
		}

		
	}

}



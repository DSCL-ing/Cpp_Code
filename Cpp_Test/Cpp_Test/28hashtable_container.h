#pragma once

#include<vector>
#include<string>
#include<iostream>
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;


namespace HashBucket 
{

	template<class T>
	struct HashNode
	{
		HashNode* _next = nullptr;
		T _data; 

		HashNode(const T& data)
			:_data(data)
		{}

	}; //HashNode_end


	//见27.
	template<class K>
	struct HashFunc 
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};
	template<>
	struct HashFunc<std::string> 
	{
		size_t operator()(const std::string& s)
		{
			size_t ret = 0;
			for (auto ch : s)
			{
				ret += ch;
				ret *= 31;
			}
			return ret;
		}
	};

	//template<class K, class T, class Ref, class Ptr, class keyOfT, class Hash>
	//struct __Hash_iterator; 

	//根据声明顺序,使用下面的类需要前置声明
	template<class K, class T, class keyOfT, class Hash >
	class HashTable; 

	template<class K , class T, class Ref, class Ptr, class keyOfT,class Hash>
	struct __Hash_iterator
	{
//迭代器怎么写?
/**
 * 1.迭代器需要什么模板类?
 * -> 先写符号重载,看需要什么:写了++,需要结点,哈希表
 * 
 * 2.需要什么函数重载?
 * -> ++ . -- , != , * , -> ,
 * 
 */

		typedef __Hash_iterator<K, T, T&, T*, keyOfT, Hash > iterator;
		typedef __Hash_iterator<K, T, Ref, Ptr, keyOfT, Hash > Self;

		typedef HashNode<T> node;
		typedef HashTable<K, T, keyOfT,Hash> HashTable;

		node* _node;
		const HashTable* _ht; //不允许修改

		__Hash_iterator(node* node, const HashTable* ht) //普通构造函数 --- 绝对不能用引用,因为迭代器是有可能会修改指针,使用引用可能会改崩原指针,
			:_node(node)
			,_ht(ht)
		{}

		__Hash_iterator(const iterator& it)
			:_node(it._node)
			,_ht(it._ht)
		{}

		Ref operator*()
		{
			return _node->_data;
		}
		Ptr operator->()
		{
			return &_node->_data;
		}
		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}

		Self& operator++() //迭代器++返回什么? 返回新的迭代器
		{
			/** 迭代器怎么++ ?
			 * 条件:
			 * 
			 * 1.当前结点为空
			 *  a.循环,计算哈希值,找下一个不为空的数组
			 *   循环出口:1.哈希值超过数组最大长度 2.找到不为空的元素
			 *   循环入口:1
			 *   循环结束后:返回空--没找到
			 * 
			 * 2.当前结点非空
			 *  a.返回下一个位置
			 * 
			 */
			Hash hash;
			keyOfT kot;
			if (_node->_next)  //_node&& _node->_next  迭代器不会为空,直到end为止,end再加就崩了,看库怎么限制法
			{
				_node = _node->_next;
				
			}
			else
			{
				size_t hashi = hash(kot(_node->_data))% _ht->_tables.size();//计算哈希值
				++hashi;//这个已经是空了,从下一个开始,
				size_t sz = _ht->_tables.size();
				while (hashi < sz)
				{
					if (_ht->_tables[hashi])
					{
						_node = _ht->_tables[hashi];
						break;
					}
					++hashi;
				}
				if (sz == hashi)
				{
					_node = nullptr;
				}
			}
			return *this;
		} //operater++_end;



	}; //iterator_end;

	template<class K, class T,class keyOfT,class Hash >
	class HashTable
	{
		template<class K, class T, class Ref, class Ptr, class keyOfT, class Hash>
		friend struct __Hash_iterator;


	public:
		typedef HashNode<T> node;
		typedef __Hash_iterator<K, T, T&, T*, keyOfT, Hash> iterator;
		typedef __Hash_iterator<K, T, const T&,const T*, keyOfT, Hash> const_iterator;
	private:
		size_t _n = 0;
		std::vector<node*> _tables;

	public:
		iterator begin() 
		{
			node* cur = nullptr;
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i])
				{
					cur = _tables[i];
					break;
				}
			}
			return iterator(cur,this);
		} // begin_end;

		iterator end()
		{
			return iterator(nullptr, this);
		}

		const_iterator begin() const
		{
			return begin(); //类型转换即可
		}

		const_iterator end() const
		{
			return end(); //类型转换即可
		}

		size_t GetNextPrime(size_t prime)
		{
			static const int __stl_num_primes = 28;
			static const unsigned long __stl_prime_list[__stl_num_primes] =
			{
				53, 97, 193, 389, 769,
				1543, 3079, 6151, 12289, 24593,
				49157, 98317, 196613, 393241, 786433,
				1572869, 3145739, 6291469, 12582917, 25165843,
				50331653, 100663319, 201326611, 402653189, 805306457,
				1610612741, 3221225473, 4294967291
			};
			size_t i = 0;
			for ( ;i < __stl_num_primes; ++i)
			{
				if (__stl_prime_list[i] > prime) 
					return __stl_prime_list[i];   
			}

			return __stl_prime_list[i];
		}


		bool insert(const T& data)
		{
			keyOfT kot;
			Hash hash;
			if (find(kot(data))!=nullptr)
			{
				return false;
			}

			if (_n == _tables.size())
			{
				size_t newsize = GetNextPrime(_tables.size());

				std::vector<node*> newht(newsize, nullptr);

				for (auto& cur : _tables)
				{
					while (cur) 
					{
						node* next = cur->_next;

						size_t hashi = hash(kot(cur->_data)) % newht.size();

						cur->_next = newht[hashi];
						newht[hashi] = cur;

						cur = next;
					}
				}
				_tables.swap(newht);
			}
			size_t hashi = hash(kot(data)) % _tables.size();

			node* newnode = new node(data);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;

			return true;
		}//insert_end

		node* find(const K& key)
		{
			keyOfT kot;
			Hash hash;

			if (_n == 0)
			{
				return nullptr;
			}
			size_t hashi = hash(key) % _tables.size();
			node* cur = _tables[hashi];

			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					return cur;
				}
				cur = cur->_next;
			}

			return nullptr;
		} //find_end

		bool erase(const K& key)
		{
			keyOfT kot;

			Hash hash;
			size_t hashi = hash(key) % _tables.size();

			node* cur = _tables[hashi];
			node* prev = nullptr;
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					if (!prev)
					{
						_tables[hashi] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}
					delete cur;

					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			
			return false;
		}//erase_end

		size_t MaxBucketSize()
		{
			size_t max = 0;
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				auto cur = _tables[i];
				size_t size = 0;
				while (cur)
				{
					++size;
					cur = cur->_next;
				}

				if (size > max)
				{
					max = size;
				}
			}

			return max;
		}


	};//HashBucket_end

	
}










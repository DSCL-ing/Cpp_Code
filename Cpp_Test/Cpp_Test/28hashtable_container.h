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


	template<typename K>
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

	struct __hash_iterator
	{

	};

	template<class K, class T,class keyOfT,class Hash = HashFunc<K>>
	class HashTable
	{
	public:
		typedef HashNode<T> node;
	public:
		size_t _n = 0;
		std::vector<node*> _tables;

	public:

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










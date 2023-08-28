#pragma once

//#include<unordered_map>
//#include<unordered_set>
#include<string>
#include<iostream>
using std::cout;
using std::endl;
using std::cin;
//unordered_set和unordered_map -- 还有multi共4中
/**
 *
 *
 * 和RBT的区别是
 * 1.unordered遍历是无序的
 * 2.unordered系列的底层是哈希表
 * 3.unordered是C++11更新的,RBT是C++98
 * 4.unordered是单向迭代器,RBT是双向迭代器
 *
 * 优势:
 * $ 在不关注顺序,冗余比较大的情况下,hash更快,快很多,删除基本都比较快,插入可能有时慢一点.但大部分还是快.
 * $ 查找最快,,快了数量级,一骑绝尘
 * 劣势:有序情况下,删除和插入RBT快
 *
 * 总结:综合情况下,hash更胜一筹,极端有序情况再使用RBT
 *
 */

 //哈希/散列
 /**
  * hash是散列的意思,哈希表也可以叫散列表
  *
  *
  *
  *
  */

  //哈希函数
  /**
   *
   * 哈希函数:
   *
   *
   * 哈希函数的设计
   *
   * 哈希冲突/哈希碰撞:可能会冲突,不同的值映射到了同一个位置
   *
   * 哈希冲突的解决:
   *   解决哈希冲突两种常见的方法是：闭散列和开散列
   * 1.闭散列:也叫开放定址法，当发生哈希冲突时，如果哈希表未被装满，说明在哈希表中必然还有空位置，那么可以把key存放到冲突位置中的“下一个” 空位置中去。
   *   寻找空位置方法:
   *   a.线性探测 -- 简单暴力的遍历
   *      比如2.1中的场景，现在需要插入元素44，先通过哈希函数计算哈希地址，hashAddr为4，因此44理论上应该插在该位置，但是该位置已经放了值为4的元素，
   *      即发生哈希冲突。线性探测：从发生冲突的位置开始，依次向后探测，直到寻找到下一个空位置为止。
   *    缺点:线性探测可能会有一些相邻聚集位置连续冲突,形成拥堵、踩踏问题出现
   *   b.二次探测 -- key+i^2(i为1,2,3,4...) -- 二次方探测
   *    评价:一定程度上缓解踩踏问题,但不能解决
   *   c.还有类似的其他方法--属于设计哈希函数 --
   * 总结:总体而言,闭散列都不是很好,实际中使用比较少 , 本质还是一个零和游戏
   *
   * 2.开散列 --别名:哈希桶/拉链法/开链法...
   * 开散列
   * 1. 开散列概念
   * 开散列法又叫链地址法(开链法)，首先对关键码集合用散列函数计算散列地址，具有相同地址的关键码归于同一子集合，每一个子集合称为一个桶，
   * 各个桶中的元素通过一个单链表链接起来，各链表的头结点存储在哈希表中。
   * (桶排序也是类似原理,不过桶排序很垃圾,智只能用整型,不要学)
   *
   */

   //哈希表什么情况下进行扩容？如何扩容？
   /**
	* 散列表的载荷因子/负载因子α -- 存储数据量的百分比 == 填入表中的元素个数/散列表的长度
	*
	* α越大,产生冲突可能性就越大
	*
	* 早期各种库中
	* 对于开放定址法(闭散列,现在不用了),载荷因子限制在0.7-0.8.java为0.75,超过就resize
	*
	*/

	//常见哈希函数
	/**
	 * 1. 直接定址法--(常用) --直接映射,适合数据范围比较集中,直观
	 * 优点：简单、均匀
	 * 缺点：需要事先知道关键字的分布情况
	 * 使用场景：适合查找比较小且连续的情况 ,如数组
	 * 特点:每个元素都有唯一的key
	 *
	 * 2. 除留余数法--(常用) --适合数据分布较为分散,空间零碎等,将分散的值映射到有限或固定的区间里
	 * 设散列表中允许的地址数为m，取一个不大于m，但最接近或者等于m的质数p作为除数，
	 * 按照哈希函数：Hash(key) = key% p(p<=m),将关键码转换成哈希地址
	 * 映射关系是模出来的
	 * 缺点:可能会冲突,不同的值映射到了同一个位置(哈希冲突)
	 * 注意:模数最好为素数,需要证明,使用素数冲突少一点
	 *
	 */



#include<iostream>
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;
#include<vector>

namespace OpenAddress
{

	//state:状态
	enum state { EMPTY, EXIST, DELETE }; //ctrl shitf U 一键变大

	template<class K, class V>
	struct HashData
	{
		pair<K, V> _kv; //键值对
		state _state = EMPTY; //状态//默认是空
	};//HashData_end


	template<class K, class V>
	class HashTable
	{
	private:
		std::vector<HashData<K, V>> _tables;
		size_t _n = 0;
	public:
		bool insert(const pair<K, V>& kv)
		{
			if (find(kv.first))//找到就不能插入 unique
			{
				return false;
			}
			//负载因子超过0.7和空表就扩容 -- 负载因子是直接算出来的 -- 负载因子== 个数/容量
			//扩容:
			/**
			 * 建立新的哈希表 -- 考虑空表
			 * 遍历旧表,调用自己的insert,重新映射到新表
			 *
			 */
			if (_tables.size() == 0 || _n * 10 / _tables.size() >= 7) //整型算不出小数
			{
				//空表和旧表都要开辟新表
				size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				HashTable<K, V> newht; //new HashTable

				//要满足随机插入特性,需要扩容并初始化所有的容量,所以需要使用resize,不能使用reserve
				newht._tables.resize(newsize);

				//遍历旧表
				for (auto& data : _tables)
				{
					if (data._state == EXIST)//只要存在就插入
						//?插入后,新表没有delete了,问题:如果该位置没删除之前插入一个值x,即下一个线性探测位置存在,
						//  然后负载因子0.7了,扩容,该位置delete变empty了,那再次find(x)能不能找得到? ---- 想多了,扩容后重新计算位置了,会有新的delete
					{
						newht.insert(data._kv);
					}
				}
				//swap(newht._tables, _tables); //
				_tables.swap(newht._tables); //好像这个好一点
			}

			//常规插入
			//计算哈希值
			//线性探测,如果当前哈希值位置状态存在,则进入循环 -- 

			size_t hashi = kv.first % _tables.size();
			size_t i = 1;
			size_t index = hashi;
			while (_tables[index]._state == EXIST) //所有都存在呢??????? --走完一圈就跳出来
			{
				index = hashi + i; //该结构是为了和其他如二次探测的算法结构类似
				++i;
				index %= _tables.size();//每次都模,一满就从0开始
				if (index == hashi)
				{
					break;
				}
			}

			_tables[index]._kv = kv;
			_tables[index]._state = EXIST;
			++_n;

			return true;
		} //insert_end

		HashData<K, V>* find(const K& key)
		{
			if (_tables.size() == 0) //如果为数组空则不可能找到,返回空;
			{
				return nullptr;
			}

			size_t hashi = key % _tables.size();//起始位置
			//线性探测
			size_t i = 1;
			size_t index = hashi;
			while (_tables[index]._state != EMPTY) //数组中数据的状态不为空,即是“存在”或"删除"都进行查找
			{
				//哈希值应该有范围的

				//元素状态为存在且key相等,则返回该元素地址?为什么不返回引用
				if (_tables[index]._state == EXIST && _tables[index]._kv.first == key)
				{
					return &_tables[index];
				}

				index = hashi + i;
				++i;
				index %= _tables.size();

				if (index == hashi)
				{
					break;
				}
				//不存在则继续往下遍历,走到底就从头开始,直到走完一圈
				//如果走完一圈,回到起始位置后,结束循环

			}
			return nullptr;
			//出循环后,说明没找到,返回空
		}//find_end

		bool erase(const K& key)
		{
			//找到key的位置,找不到返回否,找到则删除
			/** 删除原理
			 *
			 * 为了因为冲突而插在非哈希值位置的元素,
			 * 删除要将其置为|删除|状态,满足(空不查找,删除和存在都要查找)
			 *
			 *
			 */
			HashData<K, V>* ret = find(key);
			if (ret)
			{
				ret->_state = DELETE;
				--_n;
				return true;
			}
			else
			{
				return false;
			}
		} //erase_end

	}; //HashTable_end

	void test_hash1()
	{
		int a[] = { 3,33,2,13,5,12,102 };
		OpenAddress::HashTable<int, int> ht;

		//insert test
		for (auto i : a)
		{
			ht.insert(std::make_pair(i, i));
		}
		ht.insert(std::make_pair(15, 15));


		//find and erase test
		if (ht.find(13))
		{
			cout << "13在" << endl;
		}
		else
		{
			cout << "13不在" << endl;
		}

		ht.erase(13);

		if (ht.find(13))
		{
			cout << "13在" << endl;
		}
		else
		{
			cout << "13不在" << endl;
		}

	}

}


//哈希桶的时间复杂度
/**
 * 
 * 最坏情况O(n) :所有值都冲突,插在一个数组元素上
 * 
 * 但最坏情况基本不会发生,因为扩容存在,每次扩容都会重新计算哈希值,所以哈希桶一般不看最坏情况,和快排类似 
 * 
 * 增删查改时间复杂度:O(1)
 * 
 * 性能分析:统计各个桶的长度的概率,很少有极端场景出现
 * 
 * 万一有极端场景出现的解决方案
 * 1.负载因子控制:减小负载因子,空间换时间
 * 2.单个桶超过一定长度(java好像是8),这个桶不同链表改成红黑树 -- 通过联合体/共用体来控制  -- 绝对解决太长问题
 * 
 * .
 */


namespace HashBucket //哈希桶
{
	//enum State{ EMPTY,EXIST,DELETE };//不需要状态

	//建一个原生结点方便控制
	template<class K, class V>
	struct HashNode
	{
		HashNode* _next = nullptr; //单链
		pair<K, V> _kv; //KV都是存键值对

		HashNode(const pair<K, V>& kv)
			:_kv(kv)
		{}

	}; //HashNode_end

	//解决key不同类型取模的问题
	template<typename K>
	struct HashFunc //默认仿函数
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};
	template<>
	struct HashFunc<std::string> //string 特化
	{
		//字符串哈希处理
		/**
		 * 一般处理是将字符串的每个字符加起来(字符可以加)
		 * 
		 * 但直接相加很容易发生冲突,如aabb,bbaa.abab等
		 * 
		 * (衍生场景:字符串比对:来一个地址很长,通过相加计算他的哈希值,然后搜索库中的哈希表中,把冲突的几个拿出来比对.这种方法比一个一个比对快很多.)
		 * 
		 * 使用BKDR算法
		 * https://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html
		 * 
		 */
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

	//计算哈希值用的太多了,可以考虑封装成函数
	template<class K, class V,class Hash = HashFunc<K>>
	class HashTable
	{
	public:
		typedef HashNode<K, V> node;
	public:
		size_t _n = 0;
		std::vector<node*> _tables;

	public:

		size_t GetNextPrime(size_t prime)
		{
			// SGI -- 控制每次扩容的值为素数 --- 目前没有证据必要是素数 ,java没有使用这种方法
			// 因为每次扩容的值为素数不好控制,SGI给定一个数组
			static const int __stl_num_primes = 28; //一共28个值
			static const unsigned long __stl_prime_list[__stl_num_primes] =
			{
				53, 97, 193, 389, 769,
				1543, 3079, 6151, 12289, 24593,
				49157, 98317, 196613, 393241, 786433,
				1572869, 3145739, 6291469, 12582917, 25165843,
				50331653, 100663319, 201326611, 402653189, 805306457,
				1610612741, 3221225473, 4294967291
			};
			size_t i = 0;//后面复用需要
			for ( ;i < __stl_num_primes; ++i)
			{
				if (__stl_prime_list[i] > prime) 
					return __stl_prime_list[i];    //返回比实参大的元素
			}

			return __stl_prime_list[i];
		}


		bool insert(const pair<K, V>& kv)
		{
			Hash hash;
			//插入:头插有什么好处? 1.高效O(1) 
			
			//负载因子越大,冲突的概率越高,查找效率越低,空间利用率越高
			//负载因子越小,冲突的概率越低,查找效率越高,空间利用率越低 : 空间换时间
			
			//最好的情况是负载因子==1,相当于平均每个下标挂一个. 先负载因子==1时扩容 
			
			//扩容直接将原结点挪动下来 -- 每一个结点都需要重新计算hash值插入
			if (find(kv.first)!=nullptr)
			{
				return false;
			}

			//负载因子为1时扩容,什么时候负载因子为1? : 平均每个数组元素下边挂一个结点,即结点数量==数组大小
			//空表时呢? 空表时结点数量也 == 数组大小 == 0
			if (_n == _tables.size())//负载因子
			{
				size_t newsize = GetNextPrime(_tables.size());

				//size_t newsize = _tables.size() == 0 ? 10 : 2 * _tables.size();
				/*_tables.resize(newsize,nullptr);*/ //不能直接resize,因为会使原数据全部丢失
				std::vector<node*> newht(newsize, nullptr);

				//遍历旧表,插到新表
				for (auto& cur : _tables)//拿到每个元素:元素是一个存放结点的指针变量(通过这个指针变量可以使用*和->控制结点行为,但这个指针变量是vector的元素,不操作vector则不会收到影响)
				{
					while (cur) //遍历悬挂的单链表
					{
						node* next = cur->_next;
						/*newht.insert(cur._kv);*/ //不能这么写,因为这就是个顺序表,不是闭散列哈希表

						size_t hashi = hash(cur->_kv.first) % newht.size();

						cur->_next = newht[hashi];
						newht[hashi] = cur;

						cur = next;
					}
				}
				_tables.swap(newht);
				//需不需要主动释放旧数组? 不需要出了insert自动释放
				//newht.~vector();C++11
			}
			//常规插入
			size_t hashi = hash(kv.first) % _tables.size();

			node* newnode = new node(kv);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;

			return true;
		}//insert_end

		//find和erase都需要查找:因为有key,只需要确定哈希值去遍历就行

		node* find(const K& key)
		{
			Hash hash;

			if (_n == 0)
			{
				return nullptr;
			}
			size_t hashi = hash(key) % _tables.size();
			node* cur = _tables[hashi];

			while (cur)
			{
				if (cur->_kv.first == key)
				{
					return cur;
				}
				cur = cur->_next;
			}

			return nullptr;
		} //find_end

		bool erase(const K& key)
		{
			Hash hash;
			size_t hashi = hash(key) % _tables.size();

			node* cur = _tables[hashi];
			node* prev = nullptr;
			while (cur)
			{
				if (cur->_kv.first == key)
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

				//printf("[%d]->%d\n", i, size);
				if (size > max)
				{
					max = size;
				}
			}

			return max;
		}


	};//HashBucket_end


	void test_hash1()
	{
		int a[] = { 3,33,2,13,5,12,102 };
		HashBucket::HashTable<int, int> ht;

		for (auto& i : a)
		{
			ht.insert(make_pair(i, i));
		}

		ht.insert(make_pair(15, 15));
		ht.insert(make_pair(25, 25));
		ht.insert(make_pair(35, 35));
		ht.insert(make_pair(45, 45));

		//find 不用测试,嵌在insert里了
		ht.erase(12);
		ht.erase(3);
		ht.erase(33);
	}

	void test_hash2()
	{
		std::string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜","苹果", "香蕉", "苹果", "香蕉" };
		HashBucket::HashTable<std::string, std::string> ht; 
		for (auto& s : arr)
		{
			ht.insert(std::make_pair(s,s));
		}
	}

	//性能分析 -- 自己改成高随机算法再测试
	void test_hash3()
	{
		size_t N = 900000;
		HashTable<int, int> ht;
		srand((size_t)time(0));
		for (size_t i = 0; i < N; ++i)
		{
			size_t x = rand() + i;
			ht.insert(make_pair(x, x));
		}

		cout << ht.MaxBucketSize() << endl;
	}
	
}










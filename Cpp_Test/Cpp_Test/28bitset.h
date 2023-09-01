﻿#pragma once

/** 基础知识
 * 
 * 位运算:
 * $ 任何数和0进行或运算结果都是它本身 -- 0和任何数或运算结果还是那个数
 * 用途:在二进制运算时,需要修改其中的一个位或几个位,但要保证不需要修改的位不被修改.,则可以用使用 "0或" 来控制:
 * -- 只要给不需要修改的位或上0,即可保证不被修改
 * 场景:需要将某个位从0置为1,其他位保持不变:> 将需要的二进制数或上000...001000...000(1为需要置1的位),即可将该位置1
 * 
 * $ 任何数和全1(111....111)进行与运算结果都是它本身 -- 全1和任何数进行与运算结果还是那个数
 * 场景:reset:将某一位置0 -- 只需要与上111...0...111(0为需要置零的位)
 * 
 * $ 获得全1的方法:按位取反
 * 
 * $ 左移:低位往高位移   右移:高位往低位移
 * 
 * $ C中位运算级别很低,注意要加上括号
 * 
 * $ 位运算取块用除.取位用模 --- 模从0开始,可以这种原因计算机很多以0开始
 * 
 */

/**
 * 1. 面试题
 * 给40亿个不重复的无符号整数，没排过序。给一个无符号整数，如何快速判断一个数是否在这40亿个数中。【腾讯】
 * 
 * 解决:构建位图,调用bs.test(x)即可
 */

#include<time.h>
#include<string>
#include<vector>
#include<iostream>
using std::cout;
using std::endl;
using std::string;

namespace test
{
/**位图概念
 * 所谓位图，就是用每一位来存放某种状态，适用于海量数据，数据无重复的场景。通常是用来判断某个数据存不存在的。
 * 
 * 	位图的应用
 * 		1. 快速查找某个数据是否在一个集合中
 * 		2. 排序 + 去重
 * 		3. 求两个集合的交集、并集等
 * 		4. 操作系统中磁盘块标记
 * 如果能够映射到位图,则会使等价的数据量大大减小,使其能够进入内存
 * 位图效率极高,时间复杂度O(1),节省内存
 * 
 * 缺点:只能映射整型
 * 
 */




	template<size_t N> // 非类型模板参数 -- N一般给最大值
	class bitset //位图可以叫做bitmap好点,不过stl叫做bitset
	{
		/** 位图
		 * 
		 * 位图在C++标准库std中
		 * https://legacy.cplusplus.com/reference/bitset/bitset/
		 * 
		 * 位图功能:
		 * $ 能够操作比特位,在某些场景下能使消耗空间大大 减小,足以容纳进内存,快速执行
		 *
		 *
		 * 需要实现的功能:
		 * 1.接收数用于开辟多大空间 -- 非类型模板参数 -- 根据不同情况传不同的值,位图还有很多功能,如果计算无符号整型需要传整型最大值
		 * 2.能够对位图某一比特位 置零 -- reset
		 * 3.能够对位图某一比特位 置1  -- set
		 * 4.能够得知某一比特位是0还是1 -- return bool ret
		 *
		 * 成员
		 * 1.成员:char数组 - vectot
		 *
		 * 位图调试,在监视窗口中获取原始视图的指针,然后从数组首地址开始看内存,内存是从右往左,从上往下看 ,两个字母为1个字节,字节内按二进制写法
		 *
		 */

	private:
		std::vector<char> _bits; //不允许访问,因为实现位图必须通过特殊操作

	public:
		bitset()
		{
			//1.求所需要的字节数,需要至少有N个bit位,而8bit一个字节,所以至少需要N/8个字节,由于会截断,故需要+1
			//2.必须全部置成0,或者1(如果逻辑全部取反的话)
			_bits.resize(N / 8 + 1, 0);
		}

		void set(size_t x) //置1
		{
			int i = x / 8; //确定下标
			int j = x % 8; //确定该字节内的第几位 -- 用来左移,定位到第j比特位
			//置1 对左移j位 进行或运算
			_bits[i] |= 1 << j;

		}

		void reset(size_t x) //置0
		{

			int i = x / 8; //确定下标
			int j = x % 8; //确定该字节内的第几位 -- 用来左移,定位到第j比特位
			//置0: 对取反后的左移j位的1 进行与运算
			_bits[i] &= ~(1 << j);
		}

		
		bool test(size_t x) //返回x所在的位是0或1 //标准库就叫做test
		{
			int i = x / 8; //确定下标
			int j = x % 8; //确定该字节内的第几位 -- 用来左移,定位到第j比特位
			return _bits[i] & (1 << j);
		}

		//bitset& filp(size_t x = N) //翻转全部bit位或某一位
		//{

		//}


	};


	void test_bitset1()
	{
		test::bitset<100> bs;//测试用
		//test::bitset<-1> bs;//无符号整型最大值 -- 和size_t npos = -1 一样 -- 可以看资源管理器,开的内存空间
		bs.set(10);
		bs.set(11);
		bs.set(15);
		cout << bs.test(10) << endl;
		cout << bs.test(11) << endl;

		bs.reset(10);
		bs.reset(11);
		cout << bs.test(10) << endl;
		cout << bs.test(11) << endl;
	}

}

//问题引申:1. 给定100亿个整数，设计算法找到只出现一次的整数？
//题目分析:1.100亿中,最大值为42亿,很多重复,只需要开辟size_t-1个空间,即500多M即可,所以位图可以使用
//解决:双位图 -- 封装两个位图的位图
namespace test2
{
	/** 位图扩展
	 * 
	 * 位图玩法多种多样,多练习才能驾驭
	 * 
	 * 
	 */

	template<size_t N>
	class twobitset //开了两个位图的封装 
	{
	public:
		void set(size_t x)
		{
			/** 原理
			 * 通过双位图,给三种状态 00,01,10;
			 * 00代表 0次
			 * 01代表 1次
			 * 10代表 2次及以上
			 * 
			 * 个位用bs1控制,十位用bs2控制
			 * 示例图如:
			 * _bs1:▭▭▭▭▭▭▭▭▭▭011
			 * _bs2:▭▭▭▭▭▭▭▭▭▭101
			 * 
			 */
			if (_bs1.test(x) == false && _bs2.test(x) == false)
			{
				_bs1.set(x);
			}
			else if (_bs1.test(x) == true && _bs2.test(x) == false)
			{
				_bs1.reset(x);
				_bs2.set(x);
			}
		}

		bool test(size_t x)
		{
			return _bs1.test(x) == true && _bs2.test(x) == false;//由题,只出现1次返回真
		}

	private:
		test::bitset<N> _bs1; //已经初始化成0了
		test::bitset<N> _bs2;
	};

	void test_twobitset1()
	{
		int a[] = { 3, 45, 53, 32, 32, 43, 3, 2, 5, 2, 32, 55, 5, 53,43,9,8,7,8 };
		test2::twobitset<100> bs;
		for (auto i : a)
		{
			bs.set(i);
		}
		for (auto i : a)
		{
			if (bs.test(i))
			{
				cout << i << " ";
			}
		}

	}

}


//2. 给两个文件，分别有100亿个整数，我们只有1G内存，如何找到两个文件交集？
/**
 * 题目分析:1G内存只能足够一个位图使用(512M)
 * 
 * 基础方法:一个文件进位图,另一个文件进行比对,如果存在就是交集
 * 存在问题:基础方法得到的交集有重复的,违背集合互异性,需要再次去重
 * 
 * (如果不限空间,可以开两个位图分别存两个文件的数据,然后再与运算选出两个都是1的就是交集
 * 
 * 解决方法1:在基础方法的基础上,每次匹配到交集就reset.下次重复值就不会匹配成功了
 * 
 * 
 */


//3. 位图应用变形：1个文件有100亿个int，1G内存，设计算法找到出现次数不超过2次的所有整数
/**
 * 方法:双位图
 * 出现0次:00
 * 出现1次:01
 * 出现2次:10
 * 出现3次及以上:11
 * 
 * 
 */


//---------------------------------------------------------------------------------------------------------



//布隆过滤器 ---  解决:某样东西一定不存在或者可能存在
/**
 * 布隆过滤器提出
 * 我们在使用新闻客户端看新闻时，它会给我们不停地推荐新的内容，它每次推荐时要去重，去掉
 * 那些已经看过的内容。问题来了，新闻客户端推荐系统如何实现推送去重的？ 用服务器记录了用
 * 户看过的所有历史记录，当推荐系统推荐新闻时会从每个用户的历史记录里进行筛选，过滤掉那
 * 些已经存在的记录。 如何快速查找呢？
 * 1. 用哈希表存储用户记录，缺点：浪费空间
 * 2. 用位图存储用户记录，缺点：位图一般只能处理整形，如果内容编号是字符串，就无法处理
 * 了。
 * 3. 将哈希与位图结合，即布隆过滤器
 * 解决:将所有广告都映射到布隆过滤器中,然后在匹配和比对
 * 
 * 对于字符串的组合有265^n种,n为长度,n如果很大,那将会比无符号整型最大值大很多,所以一般的数据结构是不能支持的
 * 单纯使用位图,也一定会存在冲突(有重复的哈希值)问题,位图是不允许冲突的,哈希的话空间开销太大
 * 
 * 布隆过滤器就是在位图和哈希的基础上结合而成,对一个数据计算多个哈希映射到位图上,即一个数据占了位图的多个bit
 *	主要目的是降低冲突的概率,允许误判,不是根绝冲突的发生
 * 
 * 布隆过滤器不存在一定是正确的,存在可能是误判 -- 冲突
 * 
 * 本质上布隆过滤器是一种数据结构，比较巧妙的概率型数据结构（probabilistic data structure），特点是高效地插入和查询，
 *	 可以用来告诉你 “某样东西一定不存在或者可能存在”。相比于传统的 List、Set、Map 等数据结构，它更高效、占用空间更少，但是缺点是其返回的结果是概率性的，而不是确切的。
 * 
 * 显然，过小的布隆过滤器很快所有的 bit 位均为 1，那么查询任何值都会返回“可能存在”，起不到过滤的目的了。布隆过滤器的长度会直接影响误报率，布隆过滤器越长其误报率越小。
 * 哈希函数的个数也需要权衡，个数越多则布隆过滤器 bit 位置位 1 的速度越快，且布隆过滤器的效率越低,花费空间也会增多；但是如果太少的话，那我们的误报率会变高。
 * 哈希函数个数代表一个值映射几个位
 * 
 * 布隆过滤器不方便删除,可以重建来达到修改目的 -- 一种支持删除的方法:用多个bit位来计数,同理开销会增大,看情况使用
 * 
 * 查找时间复杂度O(1)
 * 
 */

/** 布隆过滤器优点
 * 
 * 1. 增加和查询元素的时间复杂度为:O(K), (K为哈希函数的个数，一般比较小)，与数据量大小无关
 * 2. 哈希函数相互之间没有关系，方便硬件并行运算
 * 3. 布隆过滤器不需要存储元素本身，在某些对保密要求比较严格的场合有很大优势
 * 4. 在能够承受一定的误判时，布隆过滤器比其他数据结构有这很大的空间优势
 * 5. 数据量很大时，布隆过滤器可以表示全集，其他数据结构不能
 * 6. 使用同一组散列函数的布隆过滤器可以进行交、并、差运算
 * 
 */

/**布隆过滤器缺陷
 * 1. 有误判率，即存在假阳性(False Position)，即不能准确判断元素是否在集合中(补救方法：再
 * 	建立一个白名单，存储可能会误判的数据)
 * 	2. 不能获取元素本身
 * 
 * 
 * 	3. 一般情况下不能从布隆过滤器中删除元素
 * 	4. 如果采用计数方式删除，可能会存在计数回绕问题,丧失低开销优势,还有可能有溢出问题
 * 
 * 
 * .
 */

/** 布隆过滤器的使用场景  -- 非整型数据存不存在
 * 1.快速响应且容许误判的场景:注册昵称是否存在
 * 
 * 2.手机号注册:如果bloom判断不存在,则直接返回,响应很快.如果在,再去数据库中确认后再返回精确结果 ---  精确且效率高 -- 比纯布隆慢一点点
 *		布隆过滤器发挥作用,可以快速过滤掉大量数据,剩下极小部分数据可以方便使用其他数据结构解决
 * (很实用)
 * 
 * $如果能容忍误判就可以直接用了
 * $如果不能容忍误判则当过滤器用 -- 最后一般都在数据库中查找--信息型数据
 * 数据分为信息型,数据型,内容型,文件型.....(不准确)
 * 
 * 最佳实践
 * 常见的适用常见有，利用布隆过滤器减少磁盘 IO 或者网络请求，因为一旦一个值必定不存在的话，我们可以不用进行后续昂贵的查询请求。
 * 
 */


//布隆过滤器变量控制
/**
 * k 为哈希函数个数，m 为布隆过滤器长度，n 为插入的元素个数，p 为误报率
 * $ -1 * (ln2)^2 * m = n * lnp
 * $ k * n = m * ln2;
 * 
 */

namespace BloomFilter
{
	struct BKDRHash
	{
		size_t operator()(const string& s)
		{
			size_t hash = 0;
			for (auto ch : s)
			{
				hash += ch;
				hash *= 31;
			}
			return hash;
		}
	};

	struct APHash
	{
		size_t operator()(const string& s)
		{
			size_t hash = 0;
			for (size_t i = 0; i<s.size(); i++)
			{
				size_t ch = s[i];
				if ((i & 1) == 0) //偶数
				{
					hash ^= ((hash << 7) ^ ch ^ (hash >> 3)); // 
				}
				else //奇数
				{
					hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
				}
			}
			return hash;
		}
	};

	struct DJBHash
	{
		size_t operator()(const string& s)
		{
			size_t hash = 5381;
			for(auto ch:s)
			{
				hash += (hash << 5) + ch;
			}
			return hash;
		}
	};

	template<size_t N, class K = string, class Hash1 =BKDRHash , class Hash2 =APHash , class Hash3=DJBHash> //可以有多个hash
	class bloomfilter
	{
	private:
		//开辟多少空间根据公式k * n = m * ln2;   m 为布隆过滤器长度，n 为插入的元素个数,k为哈希个数
		/**
		 * m = k/ln2 * N ;K=3,3/ln2 = 4.32...=4 ;
		 * 
		 */
		static const size_t _X = 6;  //数字是相当于每个值使用多少位 //计算出来是4,但感觉4误判率高很多,使用6开销也大很多,得具体验证才知好坏
		test::bitset<N * _X> _bs;   //_X越大消耗越多

	public:
		void set(const K& key)
		{
			//Hash1 hash1;具体对象写法:hash1(key)
			//			  匿名对象写法Hash1()(key);

			size_t len = N * _X;//长度
			size_t hash1 = Hash1()(key) % len;//匿名对象写法
			_bs.set(hash1);
			size_t hash2 = Hash2()(key) % len;
			_bs.set(hash2);
			size_t hash3 = Hash3()(key) % len;
			_bs.set(hash3);
			//cout << hash1 << " " << hash2 << " " << hash3 << " " << endl; //观察哈希值的数据
		}

		bool test(const K& key)
		{
			size_t len = N * _X;//长度

			//只要有一个不是1就是不存在,所有都存在才可能存在
			size_t hash1 = Hash1()(key) % len;
			if (_bs.test(hash1) == false)
			{
				return false;
			}
			size_t hash2 = Hash2()(key) % len;
			if (_bs.test(hash2) == false)
			{
				return false;
			}
			size_t hash3 = Hash3()(key) % len;
			if (_bs.test(hash3) == false)
			{
				return false;
			}

			return true;
		}


	};

	void test_BloomFilter1()
	{
		BloomFilter::bloomfilter<100> bs;
		bs.set("sort");
		bs.set("bloom");
		bs.set("hello world hello bit");
		bs.set("test");
		bs.set("etst");
		bs.set("estt");

		cout << bs.test("sort") << endl;
		cout << bs.test("bloom") << endl;
		cout << bs.test("hello world hello bit") << endl;
		cout << bs.test("test") << endl;
		cout << bs.test("etst") << endl;
		cout << bs.test("estt") << endl;


		cout << bs.test("ssort") << endl;
		cout << bs.test("tors") << endl;
		cout << bs.test("ttes") << endl;
	}


	void test_BloomFilter2()
	{
		srand((size_t)time(0));
		const size_t N = 100000; //切换release,不然很慢
		BloomFilter::bloomfilter<N> bf;



		//基准,用于与下面两个比较
		std::vector<std::string> v1;
		std::string url = "https://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html";

		for (size_t i = 0; i < N; ++i)
		{
			v1.push_back(url + std::to_string(i));
		}

		for (auto& str : v1)
		{
			bf.set(str);
		}
		//-----------------------------------------------------------------------------

		// v2跟v1是相似字符串集，但是不一样
		std::vector<std::string> v2;
		for (size_t i = 0; i < N; ++i)
		{
			std::string url = "https://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html";
			url += std::to_string(999999 + i);
			v2.push_back(url);
		}

		size_t n2 = 0;
		for (auto& str : v2)
		{
			if (bf.test(str))
			{
				++n2;
			}
		}
		cout << "相似字符串误判率:" << (double)n2 / (double)N << endl;


		// 不相似字符串集
		std::vector<std::string> v3;
		for (size_t i = 0; i < N; ++i)
		{
			string url = "zhihu.com";
			//string url = "https://www.cctalk.com/m/statistics/live/16845432622875";
			url += std::to_string(i + rand());
			v3.push_back(url);
		}

		size_t n3 = 0;
		for (auto& str : v3)
		{
			if (bf.test(str))
			{
				++n3;
			}
		}
		cout << "不相似字符串误判率:" << (double)n3 / (double)N << endl;
	}

	/**海量数据题:哈希切分
	 * 
	 * 1. 给两个文件，分别有100亿个query，我们只有1G内存，如何找到两个文件交集？分别给出精确算法和近似算法() 
	 * 	分析:query是查询语句,是字符串,一个query大概有50字节
	 * 
	 * 精确算法，一个query字符串大概算60字节，100亿大概600G，那么我们可以进行哈希切割。那么我们切分6000块把源文件，
	 *  即对源文件中的query字符串进行哈希得到key值，然后用除留余数法进行哈希（ % 6000），把不同的query放到不同的文件中。
	 *   切割完毕后，读取第二个文件时也是对其分割成6000份，对其每一个字符串进行哈希(MD5)，然后得到的key 用除留余数法 
	 *    看落在那个被切割的子文件中，然后把子文件内容读取到unordered_map中, 然后进行find, 在不在就是不在。这个就是精确的算法。
	 *     切割6000块，一块文件大概100M, 所以也符合题意。(此题解是复制的)
	 * 
	 * 哈希切分: HashFunc(query)%1000;(1000是分成多少个小文件) -- 大号哈希桶,桶内都是冲突的值 -- 两个哈希表的桶号都一样(特征相同),大大减小数据量,方便用set/map比对
	 * 
	 * 哈希切分存在的问题:切割不均匀,可能会出现极端大小不平衡,分两种情况
	 * 1.这一块中有大量的重复值,这种情况下换哈希函数也不好使,难切分.分析:如果大量重复,则使用set/哈希set插入的话是足够的,因为重复的插入失败不占内存
	 * 2.有很多不重复的值.                                          分析:直接插入set会插满内存,最后报bad_alloc异常
	 * 处理方法:把这一块插入到set/哈希set中,如果插入成功 -- 说明重复值多,直接处理完毕.如果异常,说明重复值少,只能换哈希函数,重新分割,为什么?因为哈希值是需要同一个哈希函数映射才行
	 * 
	 * $ 哈希分割的文件都需要提前开好
	 * 
	 * 近似算法:开满空间,然后一次性放一个进布隆过滤器,用另一个判断在不在
	 * 
	 * 
	 * 
	 * 2.给一个超过100G大小的log file, log中存着IP地址, 设计算法找到出现次数最多的IP地址？
	 * 解:哈希切分+map/set统计
	 *  1.如果在统计过程中,出现抛异常,则说明单个小文件过大,冲突过多,需要换哈希函数重新分割
	 *  2.如果没有抛异常,则正常统计,统计完一个小文件后记录下最大的,然后clear(),再统计下一个
	 * 
	 * 3.与上题条件相同，如何找到top K的IP？如何直接用Linux系统命令实现？
	 * 解:在建立第一个文件后,将前K个出现次数最多的ip作为键值对,次数为码,插入到小堆中,然后在clear,之后就是比较到结束
	 * 
	 * 在第一个文件中，我们已经求出了每个IP地址出现的次数，将这些IP地址和出现次数封装为一个结构体(键值对)，
	 *  给一个只能容纳K个键值对的小堆，在向堆中插入元素时，IP地址出现的次数作为关键码，先向堆中插入K个元素，
	 *   以后再插入元素时，先于堆顶元素进行比较，如果小于堆顶元素，不做处理；如果大于，则将堆顶元素删除，
	 *    将此元素重新插入堆中，当遍历完所有IP地址后，堆中保存的元素就是出现次数最多的K个。(搜索的题解)
	 * 
	 * 
	 */





}












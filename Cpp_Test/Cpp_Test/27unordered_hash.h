#pragma once



/** 哈希和红黑树总结
 * 
 * 一.
 * // 自定义类型作unordered的key需要满足1.要有可以取模的对象 2.支持比较是否相等,hashtable需要比较key(需要重载==)
 * // 自定义类型作map,set的key需要支持比较大小(需要重载<) ,只需要重载一个 '<' 或 '>' 就可以比较大小 
 * 
 */









//hash 和 RBT 数据结构测试

//#include<unordered_map>
//#include<unordered_set>
//#include<map>
//#include<set>
//#include<vector>
//
//#include <ctime>
//#include <random>
//
//int main()
//{
//
//	std::random_device rnd;//random num device //效率低，只用于生成种子
//	std::mt19937 rng(rnd()); //random num generator 0-40多亿
//	std::uniform_int_distribution<int> uni(0, 10000000);//整型区间筛选 -- 10N --9成无重复
//	//结论:无序下unordered非常快
//
//	std::unordered_set<int> us;
//	std::set<int> s;	
//	std::vector<int> v;
//
//	const size_t N = 1000000;
//	v.reserve(N);
//
//	for (size_t i = 0; i < N; ++i)
//	{
//		v.push_back(uni(rng));
//	}
//
//	//插入测试
//	size_t begin1 = clock();
//	for (auto e : v)
//	{
//		s.insert(e);
//	}
//	size_t end1 = clock();
//	cout << "set insert:" << end1 - begin1 << endl;
//	size_t begin2 = clock();
//	for (auto e : v)
//	{
//		us.insert(e);
//	}
//	size_t end2 = clock();
//	cout << "unordered_set insert:" << end2 - begin2 << endl;
//
//	//查找测试
//	size_t begin3 = clock();
//	for (auto e : v)
//	{
//		auto ret = s.find(e);
//	}
//	size_t end3 = clock();
//	cout << "set find:" << end3 - begin3 << endl;
//	size_t begin4 = clock();
//	for (auto e : v)
//	{
//		auto ret = us.find(e);
//	}
//	size_t end4 = clock();
//	cout << "unordered_set find:" << end4 - begin4 << endl << endl;
//
//	cout << s.size() << endl;
//	cout << us.size() << endl << endl;;
//
//	//删除测试
//	size_t begin5 = clock();
//	for (auto e : v)
//	{
//		s.erase(e);
//	}
//	size_t end5 = clock();
//	cout << "set erase:" << end5 - begin5 << endl;
//	size_t begin6 = clock();
//	for (auto e : v)
//	{
//		us.erase(e);
//	}
//	size_t end6 = clock();
//	cout << "unordered_set erase:" << end6 - begin6 << endl << endl;
//
//	return 0;
//}

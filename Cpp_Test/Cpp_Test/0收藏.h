#pragma once




/** 高度随机数算法
 * 
 * 
 * 
 */
#include <ctime>
#include <random>
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	std::random_device rnd;//random num device //效率低，只用于生成种子

	std::mt19937 rng(rnd()); //random num generator -- 生成随机数

	std::uniform_int_distribution<int> uni(0, 100);//整型区间筛选
	//[0-N]有6成为不重复,4成重复 --若需要9成不重复需要扩大筛选范围为10倍的N,即插入N需筛选10N

	std::uniform_real_distribution<float> unf(0.0f, 1.0f);//浮点区间筛选

	for (int i = 0; i < 100; ++i)
	{
		int num = uni(rng);
		double f = unf(rng);
		cout << num << " ";
		cout << f << " ";
		cout << endl;
	}
	return 0;
}
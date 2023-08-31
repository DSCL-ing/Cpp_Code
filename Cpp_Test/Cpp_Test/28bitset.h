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
 * 如果能够使用位图,则会使等价的数据量大大减小,使其能够进入内存,
 */

#include<vector>
#include<iostream>
using std::cout;
using std::endl;

namespace test
{
	template<size_t N> // 非类型模板参数
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
		 * 1.接收数用于开辟多大空间 -- 非类型模板参数 -- 不过应该设置成固定值,因为传进来的数据是随机的,可能很大可能很小,一般都开设size_t -1(最大值)个空间
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



		bool test(size_t x) //返回x是0或1 //标准库就叫做test
		{
			int i = x / 8; //确定下标
			int j = x % 8; //确定该字节内的第几位 -- 用来左移,定位到第j比特位
			return _bits[i] & (1 << j);
		}
	};


	void test_bitset1()
	{
		test::bitset<100> bs;
		bs.set(10);
		bs.set(11);
		bs.set(15);
		cout << bs.test(10) << endl;
		cout << bs.test(15) << endl;

	}

}





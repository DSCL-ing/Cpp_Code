#pragma once


//$Parameter	$
//^Template Parameter^
//.Member	.
//!Static	!
//@Local	@
//%Macro%



/**
 * 学习一个轮子:
 * 1..分步 要做什么?
 * 
 * 写一个轮子:
 * 耦合,要想到返回值是什么,参数
 * 
 * 
 */



// int b = 1234 ; //则b&1的意思是:将前31位清0,再取最后1位

//不能随意使用引用
/**
 * $ 因为引用很好用,容易习惯性使用引用,有些对象是不支持引用
 * 
 * $ 使用引用前必须确定,引用的对象需要被修改.如果不能修改则不能使用引用.
 * 
 * $ 常量不允许引用
 * 
 * 
 */

//typeid()
/**
 * 可以查看变量的类型
 * 
 */



//原理是不变的知识 -- 1.可以解释历史知识  2.可以预测未来


//一生二,二生三,三生万物
//机器码生汇编，汇编生 C，C 生万物。
/**
 * 学习学第一遍,了解了基本原理,能够回忆起
 * 第二轮运用,局部应用,能够有一定的掌握
 * 第三轮,在前面基础上,局部向全局扩展,逐步掌握总体脉络 --- 具有独立扩展能力,
 * ...
 * 
 * 
 * 
 */


 /**
  * while可以看作if的递归 -- 作用:保证处理任务之后,依旧是满足条件的,才能break
  * if(条件)
  * {
  *     //处理任务...
  *     if(条件)
  *     {
  *         //处理任务...
  *         if()
  *         {
  *             //...
  *             
  *         }
  *     }
  * }
  *  
  * 
  */



/** 高度随机数算法
 * 
 * 
 * 
 */
 /*
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
*/

/** 树节点


struct TreeNode
{
	TreeNode* left;
	TreeNode* right;
	int data;
};
 */

 /* 打印十六进制 */
 /*
#include<iostream>
#include<string>
std::string toHex(int num) 
{
	char buffer[64] ={0};
	snprintf(buffer,64,"0x%x",num);
	return buffer;
 }
 */
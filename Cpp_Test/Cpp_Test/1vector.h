#pragma once


//参照string

//C++二维vector (和二维数组不一样,与数组类似,用法超越了二维数组)
/**
 * 二维vector逻辑结构
 * ----------行-------------
 * 列列列列列列列列列列列列
 * 
 * vector<vector<int>> vv ;
 * vector<int>() //匿名对象,用于二维vector初始化
 * 访问二维vector,vv[]是范围二维vector的元素,vv[][]是访问二维vector的元素的元素
 * resize(i,vector<int>()) //开辟i个,类型为vector<int>的空间 //一般用于开辟二维vector的行和列
 * 
 * //vector训练
 * https://leetcode.cn/problems/pascals-triangle/submissions/
 * 
 */

//iterator
/**
 * 迭代器失效问题 - 原数据修改后需要重新初始化迭代器
 * 
 * .
 */

//capacity
/**
 * resize()
 * vector的resize使用得更频繁, 支持开空间加初始化
 * .
 */

//Modifiers
/**
 * vector也不推荐使用insert和erase
 * .
 */

//operator
/**
 * vector不提供find,推荐使用std::find(),string中有find是因为string的需求
 * 
 * .
 */






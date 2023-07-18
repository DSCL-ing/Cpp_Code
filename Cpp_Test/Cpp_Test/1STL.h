﻿#pragma once

//打印变量的类型：cout<< typeid(变量).name();

//STL standard template library 标准模板库
/**
 * STL是C++标准库的一部分
 * 1.微软用的是P.J.版本
 * 2.RW版本已被微软干翻
 * 3.linux是SGI,继承自HP原始版本 -- 开源 -- 可读性好
 *
 *
 * STL六大组件:
 * 1.容器(数据结构) --containers
 * 2.算法
 * 3.迭代器
 * 4.配接器(栈,队列)
 * 5.仿函数
 * 6.空间配置器(内存池)
 *
 */


//单词
/**
 * constructor  构造函数
 * destructor   析构函数
 * member  成员
 * copy constructor 拷贝构造函数
 * 
 */


//容器- Srting类
/**
 * #include<string>
 * 
 * 
 * .
 */

//迭代器
/**
 * 迭代器失效
 * 1.野指针:缩容/扩容后开辟新空间,指向旧空间的迭代器未更新,成为野指针
 * 2.异位失效:没有缩容/扩容,但是因为增加或删除数据而导致pos指向其他位置
 * 
 * 数组/原生指针是天然的迭代器
 * 
 */













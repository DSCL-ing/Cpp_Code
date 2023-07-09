#pragma once



//构造函数
/**
 * 1.string();  //无参构造
 * 2.string(const string& str);//拷贝构造
 * 3.string(const string& str,size_t pos,size_t len = npos); //	子串拷贝构造
 *	 注释:pos为起始位置(重0开始),npos为最长位置,如果超出实际位置,就取到最长,npos默认为无符号-1,即最大的int 
 * 4.string(const char* s);//字符串常量构造
 * 5.string(const char* s ,size_t n);//以字符串常量的前n个进行构造
 * 6.string(size_t n , char c);//以n个一样的字符进行构造
 * 7.迭代器...
 */

//定义
/**
 * string s1("hello");
 * string s2 = "hello";//隐式类型转换:构造+拷贝构造 = 构造//(const char*)转成string
 * .
 */


//运算符重载
/**
 * 赋值运算符重载:3个
 * 
 * 流插入运算符重载
 * 
 * .
 */

//Capacity(vs都不计算'\0')
/**
 * 1.size(重点)和length:一样,历史遗留问题,保留了length,新增了size(为了和其他数据结构保持一致)
 * 作用:计算字符串的长度
 * 
 * 2.max_size:
 * 作用:字符串最大长度,实际上没什么价值
 * 
 * 3.resize(重点),两个重载
 * 功能:重新调整字符串大小,改size和capacity(扩容+初始化),且会初始化,
 * 重载:
 * void resize(size_t n);		  //调整大小至n,并将新增的空间初始化成缺省值
 * void resize(size_t n, char c); //调整大小至n,并将新增的空间初始化成'c'
 * 注释:如果调整的大小更小了,则截断末尾小于n的部分,capacity不受影响
 * 
 * 
 * 4.capacity
 * 
 * 5.reserve(重点)
 * 功能:申请修改容量,修改capacity(扩容)
 * 注释;实际空间可能会大于申请的空间,字节对齐
 * 使用:如果知道需要多少空间,可以提前申请,减少扩容,提高效率
 * 
 * 6.clear(重点)
 * 功能:清空字符串
 * 
 * 7.empty(重点)
 * 
 * 8.shrink_to_fit
 * 功能:缩容至合适
 * 注释:缩容是不支持原地缩容的,几乎都是异地,缩容代价很大,很少会缩容
 * 
 * 
 * 
 * .
 */
 

//Modifiers(编辑器)
/**
 * 尾插
 * 1.push_back(char c);//字符拼接追加
 * 2.append();//字符串追加拼接
 * 3.operator+=();//能够实现append和push_back.是他们两个的封装
 * 
 */

//迭代器
/**
 * 
 * 
 * .
 */






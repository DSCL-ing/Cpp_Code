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
 * 1.size和length:一样,历史遗留问题,保留了length,新增了size(为了和其他数据结构保持一致)
 * 作用:计算字符串的长度
 * 
 * 2.max_size:
 * 作用:字符串最大长度,实际上没什么价值
 * 
 * 3.resize,两个重载
 * 功能:重新调整字符串大小,
 * 
 * 4.capacity
 * 
 * 5.reserve
 * 功能:申请修改容量
 * 
 * 6.clear
 * 功能:清空字符串
 * 
 * 7.empty
 * 
 * 8.shrink_to_fit
 * 功能:缩容至合适
 * 
 * 
 * 
 * .
 */
 





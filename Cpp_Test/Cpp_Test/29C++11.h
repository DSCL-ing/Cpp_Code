#pragma once

//C++11
/**
 * 
 * C++目前最期待的是网络库
 * 
 * C++官方网站
 * https://en.cppreference.com/w/cpp/11
 * 
 * DEV编译器是一个套着壳的GCC
 * DEV不支持范围for --> 没有支持C++11
 * 没有公司会用DEV,但学校可能会用DEV,---原因是DEV成本比较低 -- 适合入门
 * 
 * .
 */

//｛｝初始化 -- 花括号初始化 -- 列表初始化 -- 一起都可以用花括号去初始化
/**
 * 在C++98中，标准允许使用花括号{}对数组或者结构体元素进行统一的列表初始值设定
 * 
 * C++11扩大了用大括号括起的列表(初始化列表)的使用范围，使其可用于所有的内置类型和用户自定义的类型，使用初始化列表时，可添加等号(=)，也可不添加。
 * .创建对象时也可以使用列表初始化方式调用构造函数初始化
 */

#include<vector>
#include"1Date.h"
#include <map>
void test1()
{
	struct Point //结构体可以定义在函数体内部
	{
		int _x;
		int _y;
	};
	int x1 = 1;
	int x2 = { 2 };
	int x3{ 3 }; //省略赋值符号
	//int x4(4);//这个写法是模板引进的,调了int的构造 -- 与列表初始化无关

	int array1[] = { 1,2,3,4,5 };
	int array2[]{ 1,2,3,4,5 };//省略赋值符号
	int array3[5] = { 0 }; //只初始化1个还是全部初始化了?
	int array4[5]{ 0 };//省略赋值符号
	Point p{ 1,2 };


	// C++11中列表初始化也可以适用于new表达式中
	int* pa = new int[4]{ 0 };

	//日期类也可以支持花括号,不带赋值是拷贝构造
	//但日期类带赋值是构造+拷贝...优化而成
	//如果不想自定义类型显式调用拷贝构造可以加explicit(意思:明确),即使自定义不能通过赋值符号初始化 -- 把构造干掉,也拷贝不了了
	
	//自定义类型初始化时可以把圆括号换成花括号
	//花括号和圆括号的区别是,花括号可以用 = 号,或者省略等号(省略时和圆括号一样). 而圆括号只能跟/贴着对象或类型


	//C++11 std::initializer_list<T> -- 接收常量数组 --该数组在常量区 -- 不允许修改
	/**
	 * 中文名 :初始化器表
	 * 
	 * 是C++标准程序库中的一个头文件，定义了C++标准中一个非常轻量级的表示初始化器列表的类模板initializer_list及有关函数。
	 * 为了编写能够处理不同数量实参（但是类型相同），C++11新标准提供了initializer_list的方法。
	 * 与vector不同的是，initializer_list对象中的元素永远是常量值，我们无法改变initializer_list对象中元素的值。在进行函数调用的时候需要使用花括号将所有的参数括起来。
	 * 
	 * 支持:vector,list,map
	 * 
	 * std::initializer_list一般是作为构造函数的参数，C++11对STL中的不少容器就增加std::initializer_list作为参数的构造函数，
	 * 这样初始化容器对象就更方便了。也可以作为operator=的参数，这样就可以用大括号赋值。
	 * 
	 */
	auto il = { 1,2,3,4,5,6 };
	std::initializer_list<int>::iterator it = il.begin();
	//++(*it); -- 报错,不允许


	Date d1(1, 1, 1);
	Date d2(2, 2, 2);

	//initializer_list<Date>
	std::vector<Date> v1 = { d1,d2 };
	std::vector<Date> v2 = {Date(1,1,1),Date(2,2,2)};
	std::vector<Date> v3 = { {1,1,1},{2,2,2} };
	 //typename std::vector<int>::iterator it = v2.begin(); // ------ 不知道为什么迭代器不对

	//map 可以使用初始化器表
	map<std::string, std::string> dict = { {"1","1"},{"2","2"} };

	//pair支持花括号 -- 和圆括号一样
	pair<int, int> kv = { 2,2};

}








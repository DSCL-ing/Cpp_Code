#pragma once

//笔记
/**
 * string可以理解为管理数组的顺序表
 * 
 * 
 * 对于字符串常量和string , 可以相互隐式类型转换,没必要实现多个重载
 * 实现多个重载目的是追求极致效率
 * 
 * 
 * 
 * 
 * 
 */

//string的特点
/**
 * string和字符串常量不一样,string可以认为是字符数组的顺序表,可以修改,交换,增删等
 * 
 * 
 */

//string使用优化
/**
 * 1.容量增加可知 -- 使用resize提前扩容
 * 2.顺序查找修改多个元素时,每次修改pos缩减查找范围
 * 
 */


//string类域成员
/** member
 * 
 * npos
 * 
 * .
 */

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
 * 1.size()(重点)和length():一样,历史遗留问题,保留了length,新增了size(为了和其他数据结构保持一致)
 * 作用:计算字符串的长度
 * 
 * 2.max_size():
 * 作用:字符串最大长度,实际上没什么价值 
 * 注释:和npos不相等,可能是返回能开辟的最大空间
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
 
//[
//Modifiers(编辑器)
/**
 * 尾插
 * 1.push_back(char c);//字符拼接追加
 * 2.append();//字符串追加拼接
 * 3.operator+=();//能够实现append和push_back.是他们两个的封装
 * 
 * 插入(不推荐,效率低)
 * string& insert(size_t pos , ...) //还有7个重载
 * 注释:插入一般都是前插,记忆:头插,intsert(0),插在0的前面,在n的前面插入(插在n前)
 * 配合迭代器使用:s.insert(s.begin()+5,' ');//在第5个位置前面插入空格
 * 注意:迭代器插入重载函数只能是字符,没有字符串参数
 * 
 * 删除(不推荐,效率低)
 * erase() //将下标及往后的删除,删除下标n,从下标n开始删除(包括n)
 * s.erase(5); //删除下标为5及其以后的所有元素
 * 配合迭代器使用:s.erase(s.begin()+5); //删除下标为5及其以后的所有元素
 * 
 * 
 * 更换,更新,替换
 * replace(不推荐,效率低)
 * replace(size_t pos , size_t len , "");
 * repalce(pos,1,' ');//将pos位置替换成空格
 * == str[pos] = ' ';
 * 
 * 赋值,分配
 * assign()
 * 
 * 交换
 * swap() //更快,改变的是指向 ,std中的是临时变量交换
 * 
 * 
 */
//]

//operations
/**
 * 截取字串
 * substr(size_t pos = 0, size_t len = npos) 
 * 
 * 查找
 * find(const char* s, size_t pos=0, size_t npos)
 * find(char , 位置)
 * rfind()
 * 
int main()
{
	string file("string.h.cpp");
	//size_t pos = file.find('.'); //只限一个'.'
	size_t pos = file.rfind('.'); //通用,只取最后一个.开始为后缀
	if (pos != string::npos)
	{
		cout << file.substr(pos) << endl;
		//cout << file.substr(pos, file.size() - pos) << endl;
	}
	else
	{
		cout << file << endl;
	}
	return 0;
}
 * 
 * 返回c语言的字符串(兼容)
 * c_str() //以'\0'为结束标志
int main()
{
	system("chcp 65001"); //临时修改cmd字符集.字符集要匹配,不然输出有问题
	string filename("string.h");
	FILE* fout = fopen(filename.c_str(), "r"); //VS2019检查严格,关闭GS或SDL检查
	if (fout == nullptr)
	{
		perror("fopen fail");
	}
	char ch = fgetc(fout);
	while (ch != EOF)
	{
		cout << ch;
		ch = fgetc(fout);
	}
	fclose(fout);
	return 0;
}
 * 
 * 正向查找在原字符串中第一个与指定字符串（或字符）内的任意字符匹配的字符,返回下标
 * find_first_of(const char* s, size_t pos = 0, size_t npos)
 * find_first_not_of()//正向查找 非指定字符串内
 * find_last_of()	  //反向查找,指定字符串
 * find_last_not_of   //反向查找,非指定字符串
 * 
int main1()
{
	//屏蔽敏感词
	string str("Please ,replace the vowels in this sentence by asterisks");
	size_t pos = str.find_first_of("abcd");
	while (pos != string::npos)
	{
		//str.replace(pos, 1,"*");
		str[pos] = '*';
		pos = str.find_first_of("abcd",pos+1);
	}
	cout << str << endl;
	return 0;
}
 * 
 * compare() //几乎不用,一般使用运算符重载
 * 
 * 
 */

//Non-member function overloads
/**
 * relational operators (string)
 * operator+ (不建议使用)
 * 
 * 
 * getline:获取数据,遇到'\n'停止,或者自定义符号
 * istream& getline (istream& is, string& str, char delim);
 * istream& getline (istream& is, string& str);
 * 使用:
 *  getline(cin,str);
 */



//[
//迭代器特点
/**
 * 长类型使用auto自动推导,减少代码量,但可读性远远降低
 * 
 * 关于迭代器的特性,相关的,对数据操作往往是一次只能操作一个指针下标,即一个数据
 * 1.注意迭代器初始化后,大小是固定了,中途大小变大或变小都不能影响到迭代器
 * 2.迭代器区间都是左闭右开
 * 
 * iterator是类型typedef出来的类型重命名,需要类作用限定符
 * 
 */
//迭代器
/**
 * 
 *  int main()
 * {
 * 		string s1("hello world!");
 * 		string::iterator it = s1.begin();
 * //auto it = s1.begin();
 * 		while (it != s1.end())
 * 		{
 * 			cout << *it++ << " ";
 * 		}
 * 		cout << endl;
 * 		return 0;
 * }
 * 
 * it可以先理解成指针
 * begin()是第一个数据的下标
 * end()是最后一个数据的下一个下标 -- 在string中是'\0'
 * 
 * 
 * foreach范围for底层是迭代器
 * for(auto ch :s1)
 * {//...}
 * 
 * 
 * .
 */


//反向迭代器
/**
 *
 *  
int main()
{
	string s1 = "hello world!";
	string::reverse_iterator rit = s1.rbegin();
// auto string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend())
	{
		cout << *rit << " ";
		++rit; //逻辑设计上对称：反向走，往前也是++
	}
	cout << endl;
	return 0;
}
 * 
 * 
 * .
 */

//const修饰的迭代器/反向迭代器
/**
 * 
void fun(const string& s)
{
	//迭代器和begin的const重载,只允许迭代器读,不允许写
	//const_reverse -- 安全,保护数据不被破坏
	//string::const_reverse_iterator rit = s.rbegin();
	auto rit = s.rbegin(); //auto自动推导类型
	while (rit != s.rend())
	{
		//rit+=1; //	不允许修改指针指向的对象的内容,
		cout << *rit << " ";
		++rit;
	}
}
 * 
 * 对于const迭代器,还有新增的相应的cbegin()和cend //const
 * begin和cbegin都可以用,前者用的人更多
 * 
 * 
 * 
 */
//]


//element access;
/**
 * 1.(重点)operator[] /operator[]const //越界会奔溃,assert
 * 2.at(int i)  //越界会抛异常
 * 3.back  //==[0]
 * 4.front //==[size()-1]
 * .
 */


 // iterator ,capacity和modifiers综合使用
 /**
  * 
  * 	//题目:将空格替换成%20
  * 方法一:时间效率低
int main()
{
	string s = "hello world i love you!";
	size_t num = 0;
	for (auto ch : s)
	{
		if (ch == ' ')
		{
			num++;
		}
	}
	s.reserve(size(s) + 2 * num);
	size_t pos = s.find(' ');
	while (pos !=string::npos) {
		s.replace(pos,1, "%20");
		pos = s.find(' ',pos + 3);
	}
	cout << s << endl;
	return 0;
}
  * 
  * 方法二:空间换时间
  int main()
{
	string s = "hello world i love you!";
	string newStr;
	size_t num = 0;
	for (auto ch : s)
	{
		if (ch == ' ')
		{
			++num;
		}
	}
	newStr.reserve(s.size() + num * 2);
	for (auto ch : s)
	{
		if (ch != ' ')
		{
			newStr += ch;
		}
		else
		{
			newStr += "%20";
		}
	}
	cout << newStr << endl;
	return 0;
}
  * .
  */


//Convert from strings  从字符串转换
/**
 * stoi
 * //stol(long和int一样)
 * //stoul(无符号long)
 * stoll(长整型longlong)
 * stoull(无符号长整型longlong)
 * stof
 * stod
 * stold
 * 
 * 
 * 
 * 
 * 
 */

//可以在string上用的其他函数
/**
 * 
 * 逆置 - 传迭代器区间
 * std::reverse
 * void reverse (BidirectionalIterator first, BidirectionalIterator last);.
 */






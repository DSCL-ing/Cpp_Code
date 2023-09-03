//在VS预编译器加上这句话,或者放在main函数所在文件才有效
//#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include<string.h> //写在main
#include<assert.h>
//#include<iostream> //写在main中
#include<iostream>
using std::cout;
using std::endl;
using std::cin;
namespace test {

	class string {
		//friend std::ostream& operator<<(std::ostream& out, const string& s);
		//friend std::istream& operator>>(std::istream& in, const string& s);

	private:
		//char* 和 字符数组char[] 基本等价
		//const char* 是字符串常量 "xxxxxxxx"
		char* _str; //不能是const,因为要修改_str的内容,
		size_t _size; //有效字符长度(不包括\0)
		size_t _capacity; //有效容量(不包括'\0'),但真实容量为有效容量+1(包括'\0')

		//member constant (static const size_t npos = -1; //C++手册的写法)
		static size_t npos; //静态成员变量不能给缺省值,因为静态成员不走初始化列表,缺省值是辅助初始化列表使用的

		//但是,const修饰的静态整型常量可以给缺省值,仅限整型,double什么的都不可以
		//static const size_t N = 1;
		//int _a[N]; //可以这么用

	public:
		typedef char* iterator;
		typedef const char* const_iterator;


		//iterator
		iterator begin()
		{
			return _str;
		}
		const const_iterator begin() const
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const const_iterator end() const
		{
			return _str + _size;
		}
		//反向迭代器暂时不写
		//...

		//constructor 

		//string()
		//	//无参不能为空,因为一旦访问就会解引用空指针,不符合需求
		//	//而且不能赋值为0 ,'\0', -- 
		//	:_str(new char[1]) //必须使用new[]
		//	, _size(0)
		//	, _capacity(0)
		//{
		//	_str[0] = '\0';
		//} // ------------------------通过缺省值合并到带参构造函数
		string(const char* s = "") //---支持const char* 隐式转化成string ,走构造+拷贝构造 => 构造
			:_size(strlen(s))
			,_capacity(_size)
		{
			//如果多个参数有关联,尽量不走初始化列表,防止因为声明位置导致初始化错误
			//strlen计算不包含'\0'
			//strcpy会拷贝'\0'
			//所以需要多开1个空间用于存放'\0'

			//_capacity = _size == 0 ? 3 : _size;
			_str = new char[_capacity + 1]; //_capacity是0也没关系,因为至少会1个空间
			strcpy(_str, s);
		}


		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		//copy constructor
		string(const string& s) //拷贝构造的参数是本对象类型的引用
			:_str(nullptr)
		{
			cout << "string(string&& s) -- 移动拷贝" << endl;
			string tmp(s._str); //复用:走带参构造造一个临时string,然后交换信息,之后自动释放掉临时对象
			swap(tmp);
		}

		string& operator=(const string& s)
		{
			if (this != &s)
			{
				//考虑极端复杂情况
				//1._str本身很大,s很小,如果不缩容,则会浪费很多空间
				//2._str本身很小,s很大,则必须扩容,需要扩容很多次
				//干脆直接开新空间,拷贝过去
				/*char* tmp = new char[s._size + 1];
				strcpy(tmp, s._str);
				delete[] _str;
				_str = tmp;
				_size = s._size;
				_capacity = s._capacity;*/

				cout << "string& operator=(string s) -- 深拷贝" << endl;  //移动拷贝和深拷贝测试
				string tmp(s);
				swap(tmp);
			}
			return *this;
		}

		//移动构造 -- c++只提供拷贝构造的移动构造
		string(string&& s) ///------ &&
			:_str{nullptr}
		{
			cout << "string(string&& s) -- 移动拷贝" << endl;
			string tmp(s._str);
			swap(tmp);
		}

		//destructor
		~string()
		{
			delete[] _str;
			_size = _capacity = 0;
		}





	   //Capacity
		size_t size() const
		{
			return _size;
		}
		size_t capacity() const
		{
			return _capacity;
		}
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp; //指针,可以直接赋值,指向新的对象
				_capacity = n;
			}
		}
		void resize(size_t n, char ch = '\0')
		{
			if (n <= _size)
			{
				_str[n] = '\0'; //只要放'\0',后面都识别不出来了
				_size = n;
			}
			else
			{
				reserve(n);
				//memset();
				size_t begin = _size;
				while (begin != n)
				{
					_str[begin] = ch;
					++begin;
				}
				_size = n;
				_str[_size] = '\0';
			}
		}
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}

		//Element access
		char& operator[](size_t pos)//必须返回真实数据地址
		{
			assert(pos < size()); //size_t无符号数不需要判断小于0
			return _str[pos];
		}
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}



		//Modifiers
		void push_back(char ch)
		{
			/*
			if (_size >= _capacity) //满了
				reserve(_capacity * 2);
			_str[_size] = ch;
			++_size; //不需要给[_size] = '\0' , 因为\0在[capacity+1]处而不是在[_size]处
			_str[_size] = '\0'; // \0不算有效字符,不用++_size
			*/
			insert(_size, ch);
		}
		void append(const char* s)
		{
			/*
			size_t len = strlen(s);
			if (_size+len > _capacity)//需要的容量大于现有容量
				reserve(_size+len);
			strcpy(_str+_size, s); //不用strcat:strcat底层需要自己找\0(如果很长则浪费),strcpy不用找,直接一步到位
			_size += len;
			*/

			insert(_size, s);
		}
		string& operator+=(char ch) //char 和char &基本一样,但函数内传参引用的引用最好不用, s1+=' '+=""时出错
		{
			push_back(ch);
			return *this;
		}
		string& operator+=(const char* s)
		{
			append(s);
			return *this;
		}

		string operator+(char ch)
		{
			string tmp(*this);
			tmp += ch;
			return tmp;
		}

		string operator+(const char* s)
		{
			string tmp(*this);
			tmp += s;
			return tmp;
		}

		string& insert(size_t pos, char ch)//插入字符
		{
			assert(pos <= _size); //pos在'\0'处也可以插入
			if (_size - 1 > _capacity) //满了
				reserve(_capacity * 2);
			for (size_t i = _size + 1; i > pos; --i) //当size_t i减到0时,--i会变成最大整数,导致奔溃,所以i只减到1
			{
				_str[i] = _str[i - 1];
			}
			_str[pos] = ch;
			++_size;
			//_str[_size] ='\0';   //\0第一次循环就拷贝过去了
			return *this;
		}
		string& insert(size_t pos, const char* s)//插入字符串
		{
			assert(pos <= _size);
			size_t len = strlen(s);
			if (_size + len > _capacity)//需要的容量大于现有容量
				reserve(_size + len);
			for (size_t i = _size + len; i > pos + len - 1; --i) //当i==0时,i--会变成最大整数,错位一下
			{
				_str[i] = _str[i - len];
			}
			strncpy(_str + pos, s, len);
			_size = _size + len;
			//_str[_size] = '\0';
			return *this;
		}
		string& erase(size_t pos, size_t len = npos)//起始位置，删除长度 --删1个，删多个都满足
		{
			assert(pos < _size); //此处不为_size原因是,删除\0没有意义,没必要加上去
			if (len == npos || pos + len >= _size) //超出长度 ,前条件不能省略 , 因为后条件超出最大值后可能会溢出
			{
				_str[pos] = '\0';
				_size = pos; //size = \0的下标
			}
			else
			{
				for (size_t i = pos; i <= _size - len; i++)
				{
					_str[i] = _str[i + len];
				}
				_size = _size - len;
			}
			return *this;
		}

		size_t find(char ch, size_t pos = 0)
		{
			assert(pos < _size);//加不加无所谓
			for (size_t i = pos; i < _size; ++i)
			{
				if (ch == _str[i])
				{
					return i;
				}
			}
			return npos;
		}
		size_t find(const char* s, size_t pos = 0)
		{
			assert(pos < _size);

			//return strstr(_str + pos, s) - _str;
			char* p = strstr(_str + pos, s);//原理是BF暴力匹配match ,还有KMP(纸老虎) , BM(最实用)
			//if (p == nullptr)
			//	return -1;
			//else
			//	return p - _str;
			return p == nullptr ? npos : p - _str;
		}



		//String operator
		const char* c_str()
		{
			return _str;
		}

		//Non-member function overloads


		//relational operators
		//必须加上const
		bool operator<(const string& s) const
		{
			return strcmp(_str, s._str) < 0;
		}
		bool operator==(const string& s) const
		{
			return strcmp(_str, s._str) == 0;
		}
		bool operator!=(const string& s) const
		{
			return !(*this == s);
		}
		bool operator<=(const string& s) const
		{
			//如果没加const,此时s(const)调用==,s即为==的左操作数*this,==中左操作数为非const,即const调用非const函数,权限放大
			//return s > *this && s == *this;
			return *this < s || *this == s;
		}
		bool operator>(const string& s) const
		{
			return !(*this <= s);
		}
		bool operator>=(const string& s) const
		{
			return !(*this < s);
		}

	};

	size_t test::string::npos = -1; //类型 (域::)变量名 = 值;


	//流插入 和 流提取 (不是必须是友元函数,不是友元也可以 -- 重修,流插入需要支持什么功能?)
	//Extract string from stream
	std::ostream& operator<<(std::ostream& out, const string& s)
	{
		for (auto ch : s)	//string类要打印到size
		{
			out << ch;
		}
		//out << s.c_str();  //1.非友元函数,需要调用接口 2.不能直接打印字符串,遇到\0就终止
		return out;
	}
	std::istream& operator>>(std::istream& in, string& s) //此处string要修改,不能加const
	{
		s.clear();//每次流提取都需要清掉旧数据。

		//一定是不能使用C语言的流，因为C和C++的缓冲区是不一样的。getchar什么的都不允许使用
		char ch = in.get();  // get()是in的成员函数
		char buff[128];
		size_t i = 0;
		while (ch != ' ' && ch != '\n')
		{
			buff[i] = ch;
			++i;
			if (i == 127)
			{
				buff[127] = '\0'; //流插入不会给'\0', 会直接覆盖掉原本的'\0',而字符数组也不会给\0,所以需要手动给
				s += buff; //+=字符数组(字符串)底层是insert("字符串"),每次都只扩容一次,一步到位,避免了频繁扩容
				i = 0;
			}
			ch = in.get();
		}
		if (i !=0) //0和127都可以,0更好一点,127会比0多走一步无用操作,插一个\0
		{
			buff[i] = '\0';
			s += buff;
		}
		return in;
	}

	//测试用例
	/*
	void Print(const string& s)
	{
		string::const_iterator it = s.begin();
		while (it != s.end())
		{
			cout << *it;
			++it;
		}

		//for (size_t i = 0; i < s.size(); ++i)
		//{
		//	cout << s[i];
		//}

		cout << endl;
	}

	void test1_string()
	{
		string s1;
		string s2("hello");
		string s3(s2);
		s2[0] = 'a';
		string s4 = s3;
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
		cout << s3.c_str() << endl;
		cout << s4.c_str() << endl;
	}

	void test2_string()
	{
		string s1("hello world!");
		string s2(s1);
		//for (size_t i = 0; i < s1.size(); ++i)
		//{
		//	++s1[i];
		//}
		//for (size_t i = 0; i < s1.size(); ++i)
		//{
		//	cout << s1[i] << "";
		//}
		Print(s1);

		//string::iterator it = s2.begin();
		//while (it != s2.end())
		//{
		//	cout << ++*it;
		//	++it;
		//}
		//cout << endl;
		//for (auto ch : s2)
		//{
		//	cout << ch;
		//}
	}
	void test3_string()
	{
		string s1 = "hello";
		string s2 = "Hello";
		cout << (s1 == s2) << endl;
		cout << (s1 != s2) << endl;
		cout << (s1 > s2) << endl;
		cout << (s1 >= s2) << endl;
		cout << (s1 < s2) << endl;
		cout << (s1 <= s2) << endl;
		cout << s1 << s2 << endl;
		cout << (s1 == "hello") << endl;

	}
	void test4_string() //modifiers
	{
		//白盒测试
		string s1 = "0123456789";
		//(s1 += ' ');
		//s1+= "world";
		//cout << s1 << endl;
		//s1.insert(0, 'a');
		//s1.insert(s1.size(), 'a');
		//s1.insert(0, "aaa");
		//s1.insert(s1.size(), "aaa");
		//s1.erase(s1.size());
		//s1.erase(s1.size() - 2, 1);
		int ret = s1.find("23");
		cout << ret << endl;
		cout << s1 << endl;
	}

	void test5_string()
	{
		string s1 = "0123456789";
		s1.resize(3, 'x');
		s1.resize(6, 'x');
		s1.resize(15, 'x');
		s1.resize(7, 'x');
	}

	void test6_string()
	{
		string s1 = "01234 56789";
		cout << s1 << endl;
		cin >> s1;
		cout << s1 << endl;
	}
	
	*/
}

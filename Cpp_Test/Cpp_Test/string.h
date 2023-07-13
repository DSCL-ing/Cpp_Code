//在VS预编译器加上这句话,或者放在main函数所在文件才有效
//#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include<string.h>
#include<assert.h>

namespace test{

	class string {
		friend std::ostream & operator<<(std::ostream & out, const string& s);

	private:
		//char* 和 字符数组char[] 基本等价
		//const char* 是字符串常量 "xxxxxxxx"
		char* _str; //不能是const,因为要修改_str的内容,
		size_t _size; //有效数据
		size_t _capacity; //有效容量(不包括'\0'),真实容量为有效容量+1(包括'\0')
	public:

		//constructor 
		string()
			//无参不能为空,因为一旦访问就会解引用空指针,不符合需求
			//而且不能赋值为0 ,'\0', -- 
			:_str(new char[1]) //必须使用new[]
			, _size(0)
			, _capacity(0)
		{
			_str[0] = '\0';
		}
		string(const char* s)
			:_size(strlen(s))
		{
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, s);
		}

		//copy constructor
		string(const string& s) //拷贝构造的参数是本对象类型的引用
			:_size(s._size)
			, _capacity(s._capacity)
		{
			//如果多个参数有关联,尽量不走初始化列表,防止因为声明位置导致初始化错误
			//strlen计算不包含'\0'
			//strcpy会拷贝'\0'
			//所以需要多开1个空间用于存放'\0'
			_str = new char[_capacity + 1];
			//深拷贝也是需要一个一个拷贝,只要是需要复制空间内容
			strcpy(_str, s._str);
		}

		//destructor
		~string()
		{
			delete[] _str;
			_size = _capacity = 0;
		}


		 string& operator=(const string& s)
		{
			 if (this != &s)
			 {
				 //考虑极端复杂情况
				 //1._str本身很大,s很小,如果不缩容,则会浪费很多空间
				 //2._str本身很小,s很大,则必须扩容,需要扩容很多次
				 //干脆直接开新空间,拷贝过去
				 char* tmp = new char[s._size+1];
				 strcpy(tmp, s._str);
				 delete[] _str;
				 _str = tmp;
				 _size =  s._size;
				 _capacity = s._capacity;
			 }
			 return *this;
		}

		 //iterator
		 typedef char* iterator;
		 typedef const char* const_iterator;
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
			 return _str+_size;
		 }
		 const const_iterator end() const
		 {
			 return _str + _size;
		 }
		 //反向迭代器暂时不写
		 //...

		//Capacity
		 size_t size() const
		{
			return _size;
		}
		 void reserve(size_t n = 0)
		 {
			 
		 }

		//Element access
		char& operator[](size_t pos)//必须返回真实数据地址
		{
			return _str[pos];
		}
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}



		//Modifiers
		void push_back(const char& ch)
		{
			if (_size > _capacity)
				reserve(2 * _capacity);
			_str[_size] = ch;
		}
		
		//String operator
		const char* c_str()
		{
			return _str;
		}

		
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
	//Extract string from stream
	std::ostream& operator<<(std::ostream& out, const string& s)
	{
		out << s._str;
		return out;
	}


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

	}


}

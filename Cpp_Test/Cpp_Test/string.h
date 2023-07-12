//在VS预编译器加上这句话,或者放在main函数所在文件才有效
//#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include<string.h>


namespace test{

	class string {
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
			strcpy(_str, s);
		}

		//destructor
		~string()
		{
			delete[] _str;
			_size = _capacity = 0;
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

		//Capacity
		size_t size()
		{
			return _size;
		}

		//Element access
		char& operator[](size_t pos)//必须返回真实数据地址
		{
			return _str[pos];
		}

		//String operator
		const char* c_str()
		{
			return _str;
		}
		
	};

	void test1_string()
	{
		string s1;
		string s2("hello");
		s2[0] = 1;
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
	}


}

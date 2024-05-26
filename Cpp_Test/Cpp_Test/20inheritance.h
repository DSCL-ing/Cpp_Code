#pragma once


#include<string>
#include<iostream>
using std::cout;
using std::endl;
using std::cin;
using std::string;
class Person
{
protected:
	string _name = "peter";
public:
	Person()
	{

	}
	Person(string name)
		:_name( name)
	{
		cout << "Person()" << endl;
	}
	Person(const Person& p)
	{
		cout << "Person(const Person& p)" << endl;
		_name = p._name;
	}
	Person& operator=(const Person& p)
	{
		cout << "operator=(const Person& p)" << endl;
		if (this != &p)
		{
			_name = p._name;
		}
		return *this;
	}
	~Person()
	{
		cout << "~Person()" << endl;
	}


};
//   派生类derived  继承方式    基类 base_class
class Student :     public     Person
{
private:
	int _num;//学号
public:
	Student(string name , int num)
		:Person(name)
		,_num(num)
	{
		cout << "Student()" << endl;
	}
	Student(const Student& s)
		:Person(s)
		,_num(s._num)
	{
		cout << "Student(const Student& s)" << endl;
	}
	Student& operator=(const Student& s)
	{
		cout << "operator=(const Student& s)" << endl;
		if (&s != this)
		{
			Person::operator=(s);
			_num = s._num;
		}
		return *this;
	}
	~Student()
	{
		cout << "~Student()" << endl;
	}
};

class Teacher
{
protected:
	int _jobid;
};

namespace test1
{
	class A
	{
	public:
		void func1()
		{
			cout << "A:func1()" << endl;
		}
		int _a;
	};
	// class B : public A
	class B : virtual public A
	{
	public:
		void func1()
		{
			cout << "B:func1()" << endl;
		}
		void func2()
		{
			cout << "B:func2()" << endl;
		}
		int _b;
	};
	// class C : public A
	class C : virtual public A
	{
		void func1()
		{
			cout << "C:func1()" << endl;
		}
		void func3()
		{
			cout << "C:func3()" << endl;
		}

	public:
		int _c;
	};
	class D : public B, public C
	{
	public:
		void func1()
		{
			cout << "D:func1()" << endl;
		}
		void func4()
		{
			cout << "D:func4()" << endl;
		}
		int _d;
	};

	void test_inheritance1()
	{
		D d;
		d.B::_a = 1;
		d.C::_a = 2;
		d._b = 3;
		d._c = 4;
		d._d = 5;
	}

}






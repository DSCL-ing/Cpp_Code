#pragma once

/**
 * 特点:
 * 1.继承的权限可以被缩小，但是不能放大，和const一样
 *   继承下来的成员的的权限不会超过继承方式的权限
 * 
 * 1.1 .私有成员也是继承下来了,只是子类和外界都不能访问,,语法上称为不可见(子类和外部都不可见)
 * 
 * 2.保护和私有都能防外人
 *   私有不仅能防外人还能防儿子
 * 
 * 3.子类可以通过父类的函数去调用父类的私有成员
 * 
 * 4.继承方式也可以不写 -- 一般都是public,其他的实用性不大,并建议显式写出继承方式
 * a.对于class,默认继承方式是私有
 * b.对于struct默认继承方式是公有
 * 
 * 4.1 继承权限表
|类成员/继承方式        |public继承                |protected继承              |private继承			  |
|基类的public成员       |派生类的public成员        |派生类的protected成员      |派生类的private成员	  |
|基类的protected成员    |派生类的protected成员     |派生类的protected成员      |派生类的private成员	  |
|基类的private成员      |在派生类中不可见          |在派生类中不可见           |在派生类中不可见	  |
 * 
 * 4.2 子类赋值给父类
 *   在公有继承中,子类可以赋值给父类 并且是天然支持,没有临时变量,(不是隐式类型转换,不存在类型转换发生)
 *   赋值过程是通过切片方式,将从父类继承下的部分赋值给父类,调用父类拷贝构造完成赋值
 * $验证:
 * student s;
 * person& rp = s;//可以不加const -- 说明没有隐式类型转换
 * $对于父类对象引用子类对象,父类只引用子类中继承父类的那一部分 -- 指针也差不多
 * 
 * 4.3 父类赋值给子类
 *  $现阶段认为不可以
 * 
 * 4.4 继承中的作用域
 * $不同作用域可以定义同一个名字的变量
 * $不同作用域的同名函数不能构成重载,同一个作用域内同名函数才有可能构成重载
 * a.隐藏:子类和父类有同名成员时,子类成员将屏蔽父类对同名成员的直接访问,这种情况叫做隐藏或重定义
 * b.想指定某父类成员时,可以使用域作用限定符显式指出,语法:> 基类::基类成员
 * 
 * 4.5 默认成员
 * a.子类自动生成的构造函数会自动调用父类构造函数,子类自动生成的析构函数会自动调用父类析构函数
 * $规定:父类的成员必须通过调用父类的构造函数完成初始化
 * b.如果子类中没写父类构造函数,则父类会自动调用无参的构造函数,但是父类写了其他构造函数,但没写无参则报错,除非全缺省
 * c.父类构造会经过子类初始化列表,无论显式还是隐式
 * d.需要显式指定参数完成父类初始化时,可以在初始化列表中显式写出父类构造函数Person(<参数>),
 * $理解:继承下来的父类可以理解成隐藏的子类成员,和其他子类成员一样,需要初始化,只是在调用时需要显式指定出来
 * e.拷贝构造初始化列表写法:Person(s) -- 切片:父类拷贝构造需要父类对象,通过子类切片得到父类对象
 * 
 * 4.6 析构的特殊处理
 * 析构在继承及以后的多态中会被处理成Destructor,即父类和子类的析构函数构成隐藏.因为名字相同
 * 所以在调用父类构造的时候需要显式指定出父类类域
 * 
 * 4.7 析构顺序
 *     析构保持和普通类一样,按照进栈的顺序,后进的先析构,先析构子类,再析构父类
 * 父类析构会在子类析构结束后自动调用
 * 
 * 4.8 不允许显式调用父类析构
 *     因为要保证析构顺序,所以父类析构是自动调用的 -- 如果是用户自己写,可能不能保证析构顺序,容易出问题
 * 
 * 4.9.父类不能用子类的成员
 * (注:析构子类只析构属于子类的那部分)
 * a.保证了析构时析构子类后父类不会析构到野指针
 * 
 * 6.友元关系不能继承
 * 
 * 7.静态成员不能被继承,但是父类子类都能调用
 * a.静态成员属于父类也属于子类,属于整个类,  
 * 
 * 8.不能被继承的类 --
 * a.私有构造函数
 * b.私有析构函数
被私有后需要进行特殊处理
public :
	static A CreateObj(){ return A()};
private:
	A(){};


 */

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




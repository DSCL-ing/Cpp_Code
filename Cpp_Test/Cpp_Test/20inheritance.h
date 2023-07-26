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
 *   在公有继承中,子类可以赋值给父类 并且是天然支持,没有临时变量,(不是隐式类型转换)
 *   赋值过程是通过切片方式,将从父类继承下的部分赋值给父类
 * 
 * 5.父类不能用子类的成员
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
	int _age = 18;
public:
	void Print()
	{
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	}
};
//   派生类derived  继承方式    基类 base_class
class Student :     public     Person
{
protected:
	int _stuid;
};

class Teacher
{
protected:
	int _jobid;
};

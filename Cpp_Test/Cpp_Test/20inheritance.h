#pragma once

/**
 * 特点:
 * 1.继承的权限可以被缩小，但是不能放大，和const一样
 *   继承下来的成员的的权限不会超过继承方式的权限
 * 
 * 2.保护和私有都能防外人
 *   私有不仅能防外人还能防儿子
 * 
 * 3.子类可以通过父类的函数去调用父类的私有成员
 * 
 * 4.继承方式也可以不写
 * a.对于class,默认继承方式是私有
 * b.对于struct默认继承方式是公有
 *  
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

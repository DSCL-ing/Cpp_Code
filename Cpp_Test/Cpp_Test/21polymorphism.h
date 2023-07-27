#pragma once
/*****************************************************************//**
 * \file   21polymorphism.h
 * \brief  
 * 
 * \author 26390
 * \date   July 2023
 *********************************************************************/

/** 多态
 * 
 * 
 * 1.虚函数/虚拟函数
 * 语法:在函数前面加上virtual
 * 
 * 1.1虚函数与虚继承没有关系,只是共用了关键字
 * 
 * 2.重写/覆盖:虚函数且函数名字类型等完全一样
 * $注:虚函数是覆盖,不是虚函数才构成隐藏
 * 
 * 3.多态的条件
 * a.虚函数的重写  -- 多态的基础
 * b.父类的指针或引用去调用  -- 很重要,必须是父类的指针或引用去调用虚函数
 * $一个不满足都实现不了多态
 * 
 * 4.必须使用多态的场景
 * a.继承中对析构函数的特殊处理场景
 * $引入:继承中析构的特殊处理引入 Destructor
 *  &如果是父类指针接收子类类型,则析构函数调用父类的,没调子类,
 *  $析构特殊处理后,构成隐藏的析构函数,类型是谁就调用谁的析构,目前不能解决
 *  $多态,虚函数,父类指针或引用调用虚函数,->彻底解决继承的析构问题
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
public:
	//虚函数:在函数前面加virtual
	virtual void BuyTicket() { cout << "买票-全价" << endl; }

	virtual ~Person() { cout << "~Person()" << endl; }
};

class Student : public Person
{
public:
	//重写/覆盖:虚函数且函数名字类型等完全一样
	virtual void BuyTicket() { cout << "买票-半价" << endl; }

	virtual ~Student() { cout << "~Student()" << endl; }
};

//测试用例

//多态的用法
void fun(Person& p)
{
	p.BuyTicket();
}
void test_polymorphism1()
{
	Person p;
	Student s;
	fun(p);
	fun(s);
}

void test_polymorphism2()
{
	Person p;
	Student s;
	cout << " ================ " << endl;

	//有virtual和无virtual区别
	Person* p1 = new Person();
	Person* p2 = new Student();
	delete p1;
	delete p2;
}

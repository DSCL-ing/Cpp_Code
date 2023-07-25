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
	int _age = 18;
public:
	void Print()
	{
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	}
};

class Student :public Person
{
protected:
	int _stuid;
};

class Teacher
{
protected:
	int _jobid;
};

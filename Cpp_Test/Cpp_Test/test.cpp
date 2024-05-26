#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

class Person
{
public:
    Person(std::string name,int age):_name(name),_age(age)
    {};
    void Print()
    {
        std::cout << "name:" << _name << " ";
        std::cout << "age:" << _age << " ";
        std::cout << std::endl;
    }
private:
    std::string _name;
    int _age;
};

class Student : private Person
{
public:
    Student():Person("stu",18){};
    void Print1()
    {
        Print();
    }
private:
    int _stuid;
}
;

class Teacher : public Person
{
public:
    Teacher():Person("tea",28){};
private:
    int _teaid;
};

int main()
{
    Student stu;
    stu.Print1();
    Teacher tea;
    tea.Print();
    
    return 0;
}
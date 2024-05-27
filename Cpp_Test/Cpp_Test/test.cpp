#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

class Person
{
public:
    std::string _name; // 姓名
};
class Student : public Person
{
protected:
    int _num; //学号
};
class Teacher : public Person
{
protected:
    int _id; // 职工编号
};
class Assistant : public Student, public Teacher
{
protected:
    std::string _majorCourse; // 主修课程
};
int main()
{
    Assistant a;
    //a._name = "peter";

    // 显示指定访问哪个父类的成员可以解决二义性问题，但是数据冗余问题无法解决
    a.Student::_name = "xxx";
    a.Teacher::_name = "yyy";
}




//class Person
//{
//public:
//    Person(std::string name, int age) :_name(name), _age(age)
//    {
//        _count++;
//    };
//    void Print()
//    {
//        std::cout << "name:" << _name << " ";
//        std::cout << "age:" << _age << " ";
//        std::cout << std::endl;
//        std::cout<<_count<<std::endl;
//    }
//protected:
////private:
//    std::string _sex = "男";
//    static int _count;
//private:
//    std::string _name;
//    int _age;
//};
//int Person::_count = 0;
//
//class Student : private Person
//{
//public:
//    Student() :Person("stu", 18)
//    {
//        _count++;
//        _sex = "女";
//    };
//    void Print1()
//    {
//        Print();
//        std::cout<<_sex<<std::endl;
//    }
//private:
//    int _stuid;
//};
//
//class Teacher : public Person
//{
//public:
//    Teacher() :Person("tea", 28)
//    {
//        Person::_count++;
//    };
//private:
//    int _teaid;
//};
//
//class Graduate :protected Person
//{
//public:
//    Graduate() :Person("gra", 65)
//    {
//        _count++;
//    };
//};


//int main()
//{
//    Teacher tea;
//    Student stu;
//    Graduate gra;
//    //std::cout << tea._count << std::endl;
//    //std::cout << Teacher::_count << std::endl;
//    tea.Print();
//    stu.Print1();
//
//    return 0;
//}
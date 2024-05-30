#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

class Person {
public:
    ~Person() { std::cout << "~Person()" << "\n"; }
};

class Student :public Person {
public:
    ~Student() { std::cout << "~Student()" << "\n"; }
};

int main()
{
    Person* ptr1 = new Student; 
    Person* ptr2 = new Student;

    delete ptr1;
    delete ptr2;
    return 0;
}

#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

class A{};
class B : public A{};

class Person {
public:
    virtual A* BuyTicket() {
        std::cout << "全票" << std::endl;
        return nullptr;
    }
};

class Student :public Person {
public:
    A* BuyTicket() {
        std::cout << "半票" << std::endl;
        return nullptr;

    }
};
void func(Person& p){
    p.BuyTicket();
}

int main(){
    Person p;    
    Student s;    
    func(p);     
    func(s);      
    return 0;
}

#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

class Person {
public:
    virtual void BuyTicket() {
        std::cout << "全票" << std::endl;
    }
};

class Student :public Person {
public:
    void BuyTicket() {
        std::cout << "半票" << std::endl;
    }
};

class Children : public Person {
public:
    void BuyTicket(){
        std::cout << "三折票" << std::endl;
    }
};

void func(Person& p){
    p.BuyTicket();
}

int main(){
    Person p;    
    Student s;    
    Children c;
    func(p);     
    func(s);      
    func(c);
    return 0;
}

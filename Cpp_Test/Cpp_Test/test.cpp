#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

class A{
public:
    int _a = 1;
};

class B : public A{
public:
    int _b = 2;
};

class C : public A{
    public:
    int _c = 3;
};

class D :public B, public C {
    public:
    int _d = 4;
};

int main()
{
    D d;
    return 0;
}

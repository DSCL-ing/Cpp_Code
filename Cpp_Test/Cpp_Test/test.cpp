#include<iostream>
class Base
{
public:
    int x;
};

class Derive : public Base
{
    int y;
};

void fun(Base* b)
{
    b[1].x = 1;
}

int main()
{
    Derive arr[5];
    fun(arr);
    std::cout<<arr[1].x<<std::endl;

    return 0;
}
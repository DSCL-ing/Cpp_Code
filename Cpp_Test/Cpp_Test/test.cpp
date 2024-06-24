#include<iostream>
#include<list>

//enum { yellow, orange };
enum struct Color { red, yellow = 2, blue };
int main() {
    int a  = (int)Color::red;
    printf("%d\n",a);
    std::cout<< static_cast<int>(Color::yellow) <<std::endl;
    return 0;
}
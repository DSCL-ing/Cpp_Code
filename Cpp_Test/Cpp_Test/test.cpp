#include<iostream>
#include<list>

//enum { yellow, orange };
//enum struct Color { red, yellow = 1, blue };

template<typename T>
struct Container {
    void Traversal(T& t) {
        for (_it = t.begin(); _it != t.end(); _it++) {
            std::cout<< *_it << " ";
        }
    }
    //typename T::iterator _it;
    decltype(T().begin()) _it;  //也可以这样
};

int main() {
    std::list<int> lt{ 1,2,3,4,5,6 };
    //Container<std::list<int>> con;
    Container<const std::list<int>> con;
    con.Traversal(lt);

    //std::cout<<color::yellow<<std::endl;
    //std::cout<< std::underlying_type<Color>::type<<std::endl;
    //std::cout << typeid(std::underlying_type<Color>::type).name() << std::endl;
    //int a;
    //decltype(1 + 2) c = 1;
    //decltype(a) b = 1;
    //printf("%d",color::yellow);
    //printf("%d",color::blue);
    return 0;
}
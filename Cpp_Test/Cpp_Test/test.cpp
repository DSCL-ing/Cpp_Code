#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>
#include<queue>
#include<stack>
#include<memory>

#if 1
// bugTest.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class BugTemplate {
public:
    virtual void FixTest() = 0;
};

//存在1个bug
class ClassBug :public BugTemplate
{
private:
    const std::string StringToUpper(const std::string& src)
    {
        std::string temp;
        temp = src;
        //std::transform(输入起始,输入结束,输出起始,处理函数);
        std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        return temp;    //返回拷贝
    }

    const std::string StringToLower(const char* src)
    {
        std::string temp;
        temp = src;
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        return temp;
    }

public:
    ClassBug() {}
    ~ClassBug() {}
    //需要修复乱码问题
    //tip:考察对类的作用域理解
    virtual void FixTest()  override//不上override,提高可读性
    {
        std::cout << "请修复bug，使程序正确输出转大写转小写" << std::endl;
        const char* test = "ABCddasdasdaddaweqWADfFcddasdasdaddaweqewabcddasdasdaddaweWQD";
        std::string test1 = StringToUpper(test);
        //const char* test2 = StringToLower(test).c_str();  //该函数返回的是一个临时对象,char*又指向的是一个由临时对象管理的资源,临时对象一销毁,char*就是垂悬指针了;因此不能使用指针,需要使用对象来拷贝或移动使资源的生命周期延长;
        std::string test2 = StringToLower(test).c_str();    //不需要显式使用std::move,现在编译器会自动优化,比使用效果更好

        std::cout << test << std::endl;
        std::cout << test1 << std::endl;
        std::cout << test2 << std::endl;

    }

};


struct buffertest {
    char strbuffer1[9];
    char strbuffer2[9];
    char strbuffer3[9];
};

//存在3个bug
class CopyBug :public BugTemplate
{
public:
    CopyBug() {}
    ~CopyBug() {}
    //需要修复乱码问题
    virtual void FixTest()
    {

        std::cout << "请让程序能够正常输出ABCDEFGHIJKLMNOP" << std::endl;
        buffertest* buffer = (buffertest*)malloc(sizeof(buffertest));   //bug1:内存泄漏 -> 智能指针或free
        //bug2:malloc可能不会成功返回有效空间指针,例如内存不足时可能会返回NULL,因此需要检测
        if (buffer == nullptr) {
            perror("malloc is NULL");
            return ;
            //exit;
            //assert(false);
            //...
        }

        //bug3:malloc的对象是未初始化的,可能存在不确定的值 -> 使用memset清零
        memset(buffer,0,sizeof(buffer));
        
        //bug4:字符串常量隐藏了一个\0,大小是字面值的个数+1;因此解决方法可以是给buffer的数组扩大容量
        strcpy(buffer->strbuffer2, "IJKLMNOP");
        strcpy(buffer->strbuffer1, "ABCDEFGH");
        //也可以使用strncpy,strncpy,保证buffer不会溢出;

        std::cout << buffer->strbuffer1;
        std::cout << buffer->strbuffer2 << std::endl;
        
        free(buffer);
    }
};

//存在一个bug
class VectorBug :public BugTemplate
{
public:
    VectorBug() {}
    ~VectorBug() {}
    virtual void FixTest()
    {
        std::vector<int> vec = { 1,2,3,4,5,6,7,8,9 };
        std::cout << "正确使用迭代器删除程序前三个数值,使程序不崩溃" << std::endl;
        std::vector<int>::iterator it = vec.begin();
        for (int i = 0; i < 3; i++)
        {
            it = vec.erase(it); //erase后会返回删除前该元素的下一个元素位置的迭代器
            //it++; //迭代器失效了,不能再++
        }
        for (it = vec.begin(); it != vec.end(); it++)
        {
            std::cout << *it << " ";
        }

    }
};


//修复bug 使程序正常运作
int main()
{
    {
        ClassBug bug;
        bug.FixTest();
    }
    {
        CopyBug bug;
        bug.FixTest();
    }
    {
        VectorBug bug;
        bug.FixTest();
    }
    system("pause");
    return 0;
}



#elif 0
#include <cstring>
#include <iostream>
#include <thread>

class my_string {
public:
    using Self = my_string;

    // 左值 带参构造函数
    my_string(const char* str = "")
        : _size(strlen(str)),  // 依据_size的大小是0还是非0,决定如何分空间
        _capacity(0),
        _str(nullptr) {
        if (_size == 0) {
            _capacity =
                3;  // msvc缺省值是15,不过我们这个用来学习的,小一点可以测试结果
        }
        else {
            _capacity = _size;
        }

        _str = new char[_capacity];
        strcpy(_str, str);
    }

    ~my_string() {
        _size = 0;
        _capacity = 0;
        delete[] _str;
    }

    void Swap(my_string& str) {
        std::swap(str._size, _size);
        std::swap(str._capacity, _capacity);
        std::swap(str._str, _str);
    }

    my_string(const my_string& str) {
        my_string tmp(str._str);
        Swap(tmp);
    }

    Self& operator=(my_string str) { Swap(str); }

    char* _str;
    size_t _capacity;  // 总容量
    size_t _size;      // 有效字符串长度
};

int main() {
    return 0;
}
#endif

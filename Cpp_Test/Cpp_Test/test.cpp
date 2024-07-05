#include<iostream> //std::cout 
#include<thread> //std::thread
#include<queue> //std::queue
#include<condition_variable> //std::condition_variable
#include<mutex> //std::mutex, std::unique_lock, std::lock_guard
#include<functional> //std::bind
#include <cstring>
#include<atomic>


class Text {
public:
    void bad(const std::string& parm)const;
private:
    char* _text;
};
void Text::bad(const std::string& parm) const
{
    for (int ix = 0; ix < parm.size(); ++ix)
    {
        _text[ix] = parm[ix];  // 不好的风格，但不是错误     
    }
    //_text = parm.c_str();  // 错误：不能修改数据成员
}


int main() {
    std::atomic<int> a;
}

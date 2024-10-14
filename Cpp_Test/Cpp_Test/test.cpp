#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>
#include<queue>
#include<stack>
#include<memory>
#include<vector>

#if 1
#include <queue>
#include <unordered_map>
#include <vector>
#include <functional>


#include<iostream>
#include<string>
#include<cstring>
#include<memory>
#include<vector>

//POD 平凡 标准布局
template <typename T, size_t Cap>
struct Vec {
    T arr[Cap];
    size_t len;
};

template <size_t Cap>
struct Str {
    char str[Cap];
    size_t len;
};

struct MyData {
    Str<128> name{};
    Vec<int, 512> vec{};         //设为INT先,可以改模板
};

bool ser_my_data(const MyData& data, uint8_t* buff, size_t len)
{
    //len是输出缓冲区长度,如果len<data.size,说明缓冲区存不下 -> false
    if (len > sizeof(data)) {
        return false;
    }

    //序列化
    size_t offset = 0;

    //序列化Str.len
    //值+类型大小
    std::memcpy(buff + offset, &data.name.len, sizeof(data.name.len));
    offset += sizeof(data.name.len);

    //序列化Str.str
    //内容+长度
    std::memcpy(buff + offset, &data.name.str, sizeof(data.name.str));
    offset += sizeof(data.name.str);

    //序列化vec
    std::memcpy(buff + offset, &data.vec.len, sizeof(data.vec.len));    //值
    offset += sizeof(data.vec.len);                                   //长度

    std::memcpy(buff + offset, &data.vec.arr, sizeof(data.vec.arr));     //数组
    offset += sizeof(data.vec.arr);                                      //数组长度

    return true;

}

//C++17 optional 还不会
std::shared_ptr<MyData> deser_my_data(uint8_t* buff, size_t len)
{
    std::shared_ptr<MyData> data = std::make_shared<MyData>();
    size_t offset = 0;

    // 反序列化 Str<128> name
    std::memcpy(&data->name.len, buff + offset, sizeof(data->name.len));
    offset += sizeof(data->name.len);

    std::memcpy(&data->name.str, buff + offset, sizeof(data->name.str));
    offset += sizeof(data->name.str);

    // 反序列化 Vec<int, 512> vec
    std::memcpy(&data->vec.len, buff + offset, sizeof(data->vec.len));
    offset += sizeof(data->vec.len);

    std::memcpy(&data->vec.arr, buff + offset, sizeof(data->vec.arr));
    offset += sizeof(data->vec.arr);

    return data;
}


int main() {
    //MyData data;
    //std::string str = "zhangsan";   //输入数据
    //strcpy(data.name.str,str.c_str());
    //data.name.len = str.size();
    //int a[] = {1,2,3,4,5};    //输入数据
    //for(int i = 0 ; i< sizeof(a); i++){
    //    data.vec.arr[i] = a[i];
    //}


    ////序列化
    //uint8_t buffer[1024];
    //if (ser_my_data(data, (uint8_t*)buffer, sizeof(buffer))) {
    //    std::cout<<"serialize success"<<std::endl;
    //}
    //else {
    //    std::cerr<<"serialize error"<<std::endl;
    //    return -1;
    //}

    ////反序列化
    //auto deser_data = deser_my_data(buffer,sizeof(buffer));
    //std::cout<<"name: "<< data.name.str << " len: "<<data.name.len<<std::endl;
    ////for std::cout<<"Vec: "<< 


    std::shared_ptr<int> sp1(new int(10)); //需要两次申请内存,new int + new RefCnt
    auto bar = std::make_shared<int>(10);
    //auto foo = std::make_shared<std::array<char, 64>>();


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

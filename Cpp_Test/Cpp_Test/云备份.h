#pragma once



//C++17文件系统库
//https://zh.cppreference.com/w/cpp/experimental/fs
/*
std::experimental::filesystem
*/


//json
/*
编译:g++ -ljsoncpp
头文件:<jsoncpp/json.h>


常规操作是Json::Value root["key"] = value; --- json类

json只有数组比较特殊,需要使用append进行添加
    如: Json::Value subArray["key"].append(value):







class Json::Value {
    Value& operator=(const Value& other); //Value重载了[]和=，因此所有的赋值和获取数据都可以通过
    Value& operator[](const std::string& key);//简单的方式完成 val["姓名"] = "小明";
    Value& operator[](const char* key);
    Value removeMember(const char* key);//移除元素
    const Value& operator[](ArrayIndex index) const; //val["成绩"][0]
    Value& append(const Value& value);//添加数组元素val["成绩"].append(88); 
    ArrayIndex size() const;//获取数组元素个数 val["成绩"].size();
    std::string asString() const;//转string string name = val["name"].asString();
    const char* asCString() const;//转char*   char *name = val["name"].asCString();
    Int asInt() const;//转int int age = val["age"].asInt();
    float asFloat() const;//转float
    bool asBool() const;//转 bool
};

//json序列化类，低版本用这个更简单
class JSON_API Writer {
  virtual std::string write(const Value& root) = 0; }
class JSON_API FastWriter : public Writer {     //低版本常用序列化
  virtual std::string write(const Value& root);
}
class JSON_API StyledWriter : public Writer {  //格式化打印
  virtual std::string write(const Value& root);
}
//json序列化类，高版本推荐，如果用低版本的接口可能会有警告
class JSON_API StreamWriter {
    virtual int write(Value const& root, std::ostream* sout) = 0; 
 }
class JSON_API StreamWriterBuilder : public StreamWriter::Factory {
    virtual StreamWriter* newStreamWriter() const; 
 }

//json反序列化类，低版本用起来更简单
class JSON_API Reader {
 bool parse(const std::string& document, Value& root, bool collectComments = true); //低版本反序列化
}
//json反序列化类，高版本更推荐
class JSON_API CharReader {
    virtual bool parse(char const* beginDoc, char const* endDoc, Value* root, std::string* errs) = 0;
}
class JSON_API CharReaderBuilder : public CharReader::Factory { 
    virtual CharReader* newCharReader() const; 
}


用例:
-------------------------------------------- json.cpp
#include<iostream>
#include<jsoncpp/json/json.h>
#include<sstream>
#include<memory>


std::string test1() //序列化
{

  const char *name = "xiaoming";
  int age = 18;
  float score[]={77.5,88,93.6};

  Json::Value root; //构建一个json格式的对象-Value类型
  root["name"] = name;
  root["age"] = 18;
  root["score"].append(score[0]);
  root["score"].append(score[1]);
  root["score"].append(score[2]);

  Json::StreamWriterBuilder swb;
  std::unique_ptr<Json::StreamWriter> sw(swb.newStreamWriter());
  std::stringstream ss;
  sw->write(root,&ss);
  std::cout<<ss.str()<<std::endl;
  return ss.str();
}
void test2(std::string str) //反序列化
{
  Json::CharReaderBuilder crb;
  std::unique_ptr<Json::CharReader> cr(crb.newCharReader());

  Json::Value root;
  bool ret = cr->parse(str.c_str(),str.c_str()+str.size(),&root,nullptr);
  if(ret == false)
  {
    std::cout<<"parse error"<<std::endl;;
    return ;
  }
  std::string name = root["name"].asString();
  int age = root["age"].asInt();
  float score[root["score"].size()];
  std::cout<<name<<std::endl;
  std::cout<<age<<std::endl;

  for(uint i =0; i< root["score"].size();i++)
  {
      score[i] = root["score"][i].asFloat();
      std::cout<<score[i]<<std::endl;
  }
}

int main()
{
  std::string ret = test1();
  test2(ret);
  return 0;
}
------------------------------------------------- json.cpp__end;
*/



//httplib
/*


namespace httplib{
    struct MultipartFormData {
        std::string name; //字段名 -- key
        std::string content; //文件内容
        std::string filename; //文件名
        std::string content_type; //文件类型
   };
    using MultipartFormDataItems = std::vector<MultipartFormData>;
//multipart不一定是上传文件,但通常用来上传文件

Request结构体的作用:
1.用户将请求数据放入Request结构体中,httplib组织成http请求的格式发送给个服务器
2.服务器收到http请求之后进行解析,将解析的数据保存在Request结构体中

    struct Request {
        std::string method; //请求方法
        std::string path;   //资源路径 -- ip:port/后面的一串j
        Headers headers;    //map,保存头部字段
        std::string body;   //正文
        // for server
        std::string version; //协议版本
        Params params;       //map,查询字符串,字段
        MultipartFormDataMap files;   //保存客户端上传的文件信息,value类型:MultipartFormData
        Ranges ranges;  //用于实现断点续传的文件请求区间

        bool has_header(const char *key) const; //查询header中有没有某个字段
        std::string get_header_value(const char *key, size_t id = 0) const; //获取某个字段的值
        void set_header(const char *key, const char *val); //设置某个字段的值
        bool has_file(const char *key) const; //是否包含某个文件
        MultipartFormData get_file_value(const char *key) const; //获取某个文件的信息
   };
HTTP Request:
    首行:请求方法 URL 协议版本
    头部:key:value\r\nkey:value\r\n...
    空行:\r\n
    正文:(提交给服务器的数据)

请求方法:
    GET POST ...

URL:
    协议://[用户名:密码]@ip:端口/资源路径?查询字段1(key=value)&查询字段2...#信息片段
    http://[user:passwd]@ip:port/path?[query&query...]#fragment
    
协议版本:
    HTTP/1.1(常用)




//Response结构体功能:用户将响应数据放到结构体中,httplib会将其中的数据按照http响应的格式组织成http响应,发送给客户端

 struct Response  
 {
        std::string version;  //协议版本 -- 默认是HTTP/1.1,httplib会根据请求自动填充,可以不管他
        int status = -1; //响应状态码
        std::string reason; // ... 
        Headers headers; //头部字段,和request一样
        std::string body; //响应给客户端的正文
        std::string location; // Redirect location -- 重定向位置
 void set_header(const char *key, const char *val); //设置头部字段,放到header中
        void set_content(const std::string &s, const char *content_type);//设置正文,放到body中
   };
HTTP Response
    首行:协议版本 状态码 状态码描述
    头部:key:value\r\nkey:value\r\n...
    空行:\r\n
    正文:



 class Server {
using Handler = std::function<void(const Request &, Response &)>;
    Handler: 函数指针,--- server用于处理http请求的回调函数
        Request保存请求数据,让用户能够根据请求数据进行业务处理
        Response:输出型参数,把响应数据返回
using Handlers = std::vector<std::pair<std::regex, Handler>>;
    Handlers是一个请求路由数组,映射了客户端请求的资源路径和任务处理函数(Handler) -- 请求与处理函数映射表
        regex:正则表达式 - 用于匹配http请求资源路径
    服务器解析请求得到资源路径和请求方法,然后根据Handlers查看有没有对应的处理函数,有则调用这个函数进行请求处理,没有则404
std::function<TaskQueue *(void)> new_task_queue;
    new_task_queue是一个线程池,把接收到的请求交给线程池处理
    线程池中线程的工作:
        1.接收请求,解析请求,得到Request结构体,也就是请求的数据
        2.在handlers映射表中,根据请求信息查找处理函数,有则调用函数处理
        3.处理函数调用完毕后,根据返回的Response结构体阻止成http响应发送会客户端

//注册不同请求方法的handler,patten是样式,关键字
Server &Get(const std::string &pattern, Handler handler);
Server &Post(const std::string &pattern, Handler handler);
Server &Put(const std::string &pattern, Handler handler);
Server &Patch(const std::string &pattern, Handler handler);  
Server &Delete(const std::string &pattern, Handler handler);
Server &Options(const std::string &pattern, Handler handler);


//搭建并启动http服务器
bool listen(const char *host, int port, int socket_flags = 0);

 };


class Client 
{
Client(const std::string &host, int port); //构造函数,接收ip和端口
Result Get(const char *path, const Headers &headers);
    向服务器发送GET请求
        path是资源路径
        headers是头部字段
Result Post(const char *path, const char *body, size_t content_length, const char *content_type);
    向服务器发送post请求
        body是正文数据
        len是正文长度
        content_type是正文类型
Result Post(const char *path, const MultipartFormDataItems &items);
    向服务器以POST方法请求提交一个到多个文件(多区域数据)
}
}

演示代码
#include "httplib.h"
int main(void) {
    using namespace httplib;
    Server svr;  //定义Server类
    //注册GET方式的"/hi"方法
    svr.Get("/hi", [](const Request& req, Response& res) { 
       res.set_content("Hello World!", "text/plain");
     });
    //注册GET"/numbers/任意数字"方法
    svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
       auto numbers = req.matches[1]; //matches[0]保存整个path,往后保存的是正则捕捉的字符
       res.set_content(numbers, "text/plain");
     });
     //注册POST的"upload"上传文件的方法方法
    svr.Post("/upload", [&](const auto& req, auto& res) {
        auto size = req.files.size();
        auto ret = req.has_file("file1");  //这个file1是key来的,和客户端同步.不是真正的文件名
        std::cout <<  file.content_type << std::endl;
        std::cout <<  file.content << std::endl;
        const auto& file = req.get_file_value("file");//这个file就是multipartformdata
   });
 //启动服务器
 svr.listen("0.0.0.0", 9090);
 return 0;
}


$$$$ http头部字段
{

ETag: 存储了一个资源的唯一标识
            客户端第一次下载文件时,会收到这个响应信息.
        第二次下载时,就会将这个信息发送给服务器,想要让服务器根据这个唯一标识判断这个资源有没有被修改过.
        如果没有被修改过,就可以直接使用原先缓存过的数据.不用重新下载了.
    .组织方式 举例(由用户决定,http不关心):
        e.g.1:ETags:"inode-size-mtime"  //只适合纯linux
        e.g.2:ETags:"filename-fsize-mtime" //当前项目使用方案
    .其他用途:
        1.断点续传(判断)

Accept-Ranges:bytes:告诉客户端支持断点续传,以字节byte为单位,即字节流.(Ranges:范围,允许按区间访问,即区间请求,断点续传,)

Content-Length:文本长度,一般不需要设置,会自动计算(body.size())

Content-Type(重要):决定了浏览器如何处理响应正文
    "text/html":展示到浏览器的html页面(网页)
    "application/octet-stream":二进制流数据
        <application/octet-stream里的octet是什么意思 http://t.csdnimg.cn/Iptly >八位组
    
}
*/

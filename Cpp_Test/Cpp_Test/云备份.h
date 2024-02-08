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



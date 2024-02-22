#ifndef __DATA_HPP__
#define __DATA_HPP__

#include"util.hpp"
#include<unordered_map>
#include<sstream>

namespace ns_cloud_backup
{
    inline namespace v1
    {
        class DataManager
        {
            public:
                DataManager(const std::string backup_file):_backup_file(backup_file)
                {}
                
                bool Storage()//�־û��洢
                {
                    //1.��ȡ���б�����Ϣ
                    //2.��������Ϣ��֯�ɳ־û��洢�ĸ�ʽ
                    //3.�־û��洢
                   
                   //std::string body;
                    std::stringstream ss; //�ַ�������֯��ʽ������ 
                    for (auto& pair : _table)
                    {
                        //body+=pair.first;
                        //body+=" ";
                        //body+=pair.second;
                        //body+="\n";
                        ss<<pair.first<<" "<<pair.second<<"\n";
                    }
                    FileUtil fu(_backup_file);
                    fu.SetContent(ss.str());
                    return true;
                }

                int Split(const std::string& str, const std::string& sep, std::vector<std::string>* arry)
                {
                    //Χ��find��substr,���ַ����ָ��һ����Ԫ��
                    int count = 0;
                    size_t idx = 0, pos = 0;
                    //while (idx < str.size())
                    while (true) //��ѭ���ÿ���,���ٿ��Ǳ߽�
                    {
                        pos = str.find(sep, idx);//find(Ҫ���ҵ��Ӵ�,���ҵ���ʼλ��)
                        if (pos == std::string::npos) //�Ҳ�����,˵�������һ��,��ѭ����ִ�����Ĳ��� "SEP str"
                        {
                            break;
                        }
                        if (idx == pos) // ��ֹ��Ϊ�����ķָ���������հ��Ӵ� "... str SEP SEP str ..."
                        {
                            idx = pos + sep.size();
                            continue;
                        }

                        std::string substr = str.substr(idx, pos - idx);//substr(��ʼλ��,�Ӵ�����);
                        arry->push_back(substr);
                        idx = pos + sep.size();
                        count++;
                    }

                    if (idx < str.size()) //���ܲ�������:���һ�κ��滹���ָ��� -- "str SEP"
                    {
                        arry->push_back(str.substr(idx));//substr(��ʼλ��);����ʼλ�ÿ�ʼ��ȡ���ַ���ĩβ
                        count++;
                    }
                    return count;
                }

                bool InitLoad()//����ʱ����
                {
                    //1.���ļ��ж�ȡ��������
                    //2.��������,�������
                    FileUtil fu(_backup_file);
                    std::string body;
                    fu.GetContent(&body);

                    //��������,�����
                    std::vector<std::string> arry;
                    Split(body,"\n",&arry);
                    for (auto& str : arry)
                    {
                        std::vector<std::string> tmp;
                        Split(str," ",&tmp);
                        if (tmp.size() != 2) //˵���ָ�������
                        {
                            continue;//����
                        }
                        _table[tmp[0]] = tmp[1]; //_table[key] = val;
                    }
                    //std::string tmp;
                    //std::string key;
                    //std::string val;
                    //for (int i = 0; i < body.size(); i++)
                    //{
                    //    char c = body[i];
                    //    if (c == ' ')
                    //    {
                    //        key = tmp;
                    //        tmp.clear();
                    //    }
                    //    else if (c == '\n')
                    //    {
                    //        val = tmp;
                    //        _table[key] = val;
                    //        tmp.clear();
                    //    }
                    //    else
                    //    {
                    //        tmp += c;
                    //    }
                    //}
                    return true;
                }

                bool Insert(const std::string& key, const std::string& val)
                {

                }

                bool Update(const std::string& key, const std::string& val)
                {

                }

                bool GetOneByKey(const std::string& key, std::string* val)
                {

                }

        private:
            std::string _backup_file;//������Ϣ�ĳ־û��洢�ļ�
            std::unordered_map<std::string, std::string> _table;
        };

    }
}





#endif
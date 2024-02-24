#ifndef __MY_CLOUD__
#define __MY_CLOUD__

#include"data.hpp"
#include"httplib.h" //��ʷ��������,httplib�ڵ�winsock2.h���windows.h��ͻ,��Ҫ����һ��λ��
#include<windows.h> 
namespace ns_cloud_backup
{
    inline namespace v1
    {
#define SERVER_ADDR "8.134.236.217" //����д��,ʵ��ʹ�÷�������������ı�
#define SERVER_PORT 8888
        class Backup
        {
        public:
            Backup(const std::string& backup_dir, const std::string& filename/*ʵ����DataManager��Ҫ*/)
                :_backup_dir(backup_dir)
            {
                _dm = new DataManager(filename);
            }
            bool RunModule()
            {
                while (true)
                {
                    //1.ɨ���ȡָ��Ŀ¼�е������ļ�
                    FileUtil fu(_backup_dir);
                    std::vector<std::string> arry;
                    fu.ScanDirectory(arry);
                    //2.����ж��ļ��Ƿ���Ҫ�ϴ�
                    for (auto& a : arry)
                    {
                        if (IsNeedUpload(a) == false)
                        {
                            continue;
                        }
                        else if (Upload(a) == true)
                        {
                            //3.�ϴ��ļ�,����������
                            _dm->Insert(a, GetFileIdentifier(a));
                            std::cout << a << " upload success!" << std::endl;
                        }
                        //�ϴ�ʧ���޸���,�´�ѭ���������ϴ�
                    }
                    Sleep(1);
                }
            }
        private:
            std::string GetFileIdentifier(const std::string& filename)
            {
                //a.txt-fsize-mtime
                FileUtil fu(filename);
                std::stringstream ss;
                ss << fu.FileName() << "-" << fu.FileSize() << "-" << fu.LastMTime();
                return ss.str();
            }
            bool Upload(const std::string& filename)
            {
                //1.��ȡ�ļ����� 
                FileUtil fu(filename);
                std::string body;
                fu.GetContent(&body);
                //2.����http�ͻ��˶���,����ļ���Ϣ
                httplib::Client client(SERVER_ADDR, SERVER_PORT);
                httplib::MultipartFormData item;
                item.name = "file";
                item.filename = fu.FileName();
                item.content = body;
                item.content_type = "application/octet-stream";
                httplib::MultipartFormDataItems items;
                items.push_back(item);
                auto res = client.Post("/upload", items);
                return (!res) ? false : true;
                //if (!res || res->status != 200)
                //{
                //    return false;
                //}
                //return true;
            }

            bool IsNeedUpload(const std::string& filename)
            {
                //�ж��Ƿ���Ҫ�ϴ�������:
                //1.�����ϴ���¼
                //2.����,ԭ��Ǻ��±���Ƿ����
                std::string id;
                if (_dm->GetOneByKey(filename, &id) == true)
                //if (_dm->GetOneByKey(filename, &id) != false)
                {
                    std::string new_id = GetFileIdentifier(filename);
                    if (new_id == id)
                    {
                        return false;
                    }

                }
                //���һ���ļ��Ƚϴ�,��������ؿ��������Ŀ¼��,��������Ҫһ������.
                //���ÿ�α�������Ҫ�ϴ�����ļ�,��һ�����ļ�,��ʮ��G���ļ����ϴ��ϰٴ�
                //���,��ҪһЩ�����ֶ�
                //1.��Ϊ����:һ��ʱ����û�б��޸Ĺ����ļ������ϴ�
                //2.�ж��ļ��Ƿ�ĳ����������ռ��
                FileUtil fu(filename);
                if (time(nullptr) - fu.LastMTime() < 3)// ʹ�÷���1: 3����֮��û�б��޸Ĺ��������ϴ�
                {
                    return false;
                }

                return true;
            }

        private:
            std::string _backup_dir;//����Ŀ¼
            DataManager* _dm;       //���ݹ���

        };
    }
}


#endif
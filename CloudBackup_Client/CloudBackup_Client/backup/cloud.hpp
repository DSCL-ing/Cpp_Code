#ifndef __MY_CLOUD__
#define __MY_CLOUD__

#include"data.hpp"
#include<windows.h>
namespace ns_cloud_backup
{
    inline namespace v1
    {
        class Backup
        {
        public:
            Backup(const std::string& backup_dir, const std::string& filename/*实例化DataManager需要*/)
                :_backup_dir(backup_dir)
            {
                _dm = new DataManager(filename);
            }
            bool RunModule()
            {
                while (true)
                {
                    FileUtil fu(_backup_dir);
                    std::vector<std::string> arry;
                    fu.ScanDirectory(arry);
                    for (auto& a : arry)
                    {
                        std::string id = GetIdentifier(a);
                        _dm->Insert(a, id);
                    }
                    Sleep(1);
                }
            }
        private:
            std::string GetIdentifier(const std::string& filename)
            {
                //a.txt-fsize-mtime
                FileUtil fu(filename);
                std::stringstream ss;
                ss << fu.FileName() << "-" << fu.FileSize() << "-" << fu.LastMTime();
                return ss.str();
            }
        private:
            std::string _backup_dir;//备份目录
            DataManager* _dm;       //数据管理

        };
    }
}


#endif
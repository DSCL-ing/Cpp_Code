#include"util.hpp"
#include"data.hpp"

#define BACKUP_FILE "./backup.dat"

int main()
{
    //ns_cloud_backup::FileUtil fu("./");
    //std::vector<std::string> arry;
    //fu.ScanDirectory(arry);
    //ns_cloud_backup::DataManager dm(BACKUP_FILE);
    //for (auto& i : arry)
    //{
    //    dm.Insert(i,"fajlkjgldkajlkfjadlk");
    //}


    ns_cloud_backup::DataManager dm(BACKUP_FILE);
    std::string val;
    dm.GetOneByKey(".\\util.hpp",&val);
    std::cout<<val<<std::endl;

    return 0;
}
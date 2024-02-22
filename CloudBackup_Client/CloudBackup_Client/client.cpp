#include"util.hpp"

int main()
{
    ns_cloud_backup::FileUtil fu("./");
    std::vector<std::string> arry;
    fu.ScanDirectory(arry);
    for (auto& i : arry)
    {
        std::cout<<i<<std::endl;
    }
    return 0;
}
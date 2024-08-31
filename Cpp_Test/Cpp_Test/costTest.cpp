#include<iostream>
#include<chrono>
#include<functional>
#include<random>
#include<iomanip>
#include<string>
#include<cassert>
#include"24.2 AVLTree.hpp"
#include"25.2 RBTree.hpp"
//#include"25RBTree.h"

//排序算法用
int* CopyArray(int* src, int size) {
    assert(src && size);
    int* tmp = new int[size];
    memmove(tmp, src, size);
    return tmp;
}

void Cost(std::function<void(void)> func) {
    auto begin = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> cost = end - begin;
    std::cout << cost.count() << "/s" << std::endl;
}

void RBInsertTest(RBTree<int, int>& t, int* a, int size) {
    //test::RBTree<int,int> t; 
    for (int i = 0; i < size; i++) {
        t.Insert(std::make_pair(a[i], a[i]));
        //if (t.IsBalance() == false) assert(false);
    }
}

void AVLInsertTest(AVLTree<int, int>& t,int* a, int size) {
    
    for (int i = 0; i < size; i++) {
        t.Insert(std::make_pair(a[i], a[i]));
        //if (t.IsBalance() == false) assert(false);
    }
}

void RandomArray_Generator(int* a, int n) {
    std::random_device rnd;//random num device //效率低，只用于生成种子
    std::mt19937 rng(rnd()); //random num generator -- 生成随机数
    std::uniform_int_distribution<int> uni(0, 1000000000);//整型区间筛选
    //[0-N]有6成为不重复,4成重复 --若需要9成不重复需要扩大筛选范围为10倍的N,即插入N需筛选10N

    //int a[] = { 3,1,8,4,2,7,5,9,6,0 }; //自定义数组
    int size = n;
    std::cout << size << "个" << "随机数" << std::endl;
    //std::cout<<size<<"个"<<"逆序数"<<std::endl;
    //std::cout<<size<<"个"<<"正序数"<<std::endl;
    //std::cout<<size<<"个"<<"重复数"<<std::endl;
    for (int i = 0; i < size; i++) {
        a[i] = uni(rng); //随机数
        //a[i] = size - i; //逆序
        //a[i] = i;         //正序
        //a[i] = size/2;     //重复数
        //if (i % 10000 == 0) {
        //    a[i] = uni(rng);  //插入一些随机数
        //}
    }
}


void testInsert() {
    //int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
    //int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16,14 };
    //int size = sizeof(a)/sizeof(int);
    int size = 10000000;
    int* a = new int[size];
    RandomArray_Generator(a, size);

    std::cout << std::setw(15) << std::left;
    std::cout << "RBTree: ";
    RBTree<int,int> rbt;
    Cost([&]() {std::cout << "cost: "; RBInsertTest(rbt, a, size); });

    std::cout << std::setw(15) << std::left;
    std::cout << "AVLTree: ";
    AVLTree<int, int> avlt;
    Cost([&]() {std::cout << "cost: "; AVLInsertTest(avlt, a, size); });

    //Cost([&]() {std::cout << "cost: "; std::sort(a, a + size); });

}

void testHight() {
    //int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
    //int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16,14 };
    //int size = sizeof(a)/sizeof(int);
    int size = 1000000;
    int* a = new int[size];
    RandomArray_Generator(a, size);

    RBTree<int, int> rbt;
    std::cout << std::setw(15) << std::left;
    std::cout << "RBTree: "<<"\n";
    RBInsertTest(rbt, a, size);
    std::cout << "\t高度" << rbt.Hight()<<std::endl;;


    AVLTree<int, int> avlt;
    std::cout << std::setw(15) << std::left;
    std::cout << "AVLTree: \n";
    AVLInsertTest(avlt, a, size);
    std::cout << "\t高度" << avlt.Hight()<<std::endl;
}

void a() {

    std::random_device rnd;//random num device //效率低，只用于生成种子
    std::mt19937 rng(rnd()); //random num generator -- 生成随机数
    std::uniform_int_distribution<int> uni(0, 1000000000);//整型区间筛选
    //[0-N]有6成为不重复,4成重复 --若需要9成不重复需要扩大筛选范围为10倍的N,即插入N需筛选10N

    //int a[] = { 3,1,8,4,2,7,5,9,6,0 }; //自定义数组
    int size = 1000000;
    int *a = new int[size];
    std::cout << size << "个" << "随机数" << std::endl;
    //std::cout<<size<<"个"<<"逆序数"<<std::endl;
    //std::cout<<size<<"个"<<"正序数"<<std::endl;
    //std::cout<<size<<"个"<<"重复数"<<std::endl;
    for (int i = 0; i < size; i++) {
        a[i] = uni(rng); //随机数
        //a[i] = size - i; //逆序
        //a[i] = i;         //正序
        //a[i] = size/2;     //重复数
        //if (i % 10000 == 0) {
        //    a[i] = uni(rng);  //插入一些随机数
        //}
    }
}

void v() {
    std::random_device rnd;//random num device //效率低，只用于生成种子
    std::mt19937 rng(rnd()); //random num generator -- 生成随机数
    std::uniform_int_distribution<int> uni(0, 1000000000);//整型区间筛选
    //[0-N]有6成为不重复,4成重复 --若需要9成不重复需要扩大筛选范围为10倍的N,即插入N需筛选10N

    //int a[] = { 3,1,8,4,2,7,5,9,6,0 }; //自定义数组
    int size = 1000000;
    std::vector<int> a(size);
    std::cout << size << "个" << "随机数" << std::endl;
    //std::cout<<size<<"个"<<"逆序数"<<std::endl;
    //std::cout<<size<<"个"<<"正序数"<<std::endl;
    //std::cout<<size<<"个"<<"重复数"<<std::endl;
    for (int i = 0; i < size; i++) {
        a[i] = uni(rng); //随机数
        //a[i] = size - i; //逆序
        //a[i] = i;         //正序
        //a[i] = size/2;     //重复数
        //if (i % 10000 == 0) {
        //    a[i] = uni(rng);  //插入一些随机数
        //}
    }

}

void vp() {
    std::random_device rnd;//random num device //效率低，只用于生成种子
    std::mt19937 rng(rnd()); //random num generator -- 生成随机数
    std::uniform_int_distribution<int> uni(0, 1000000000);//整型区间筛选
    //[0-N]有6成为不重复,4成重复 --若需要9成不重复需要扩大筛选范围为10倍的N,即插入N需筛选10N

    //int a[] = { 3,1,8,4,2,7,5,9,6,0 }; //自定义数组
    int size = 1000000;
    std::vector<int> a;
    std::cout << size << "个" << "随机数" << std::endl;
    //std::cout<<size<<"个"<<"逆序数"<<std::endl;
    //std::cout<<size<<"个"<<"正序数"<<std::endl;
    //std::cout<<size<<"个"<<"重复数"<<std::endl;
    for (int i = 0; i < size; i++) {
        //a[i] = uni(rng); //随机数
        a.push_back(uni(rng));
        //a[i] = size - i; //逆序
        //a[i] = i;         //正序
        //a[i] = size/2;     //重复数
        //if (i % 10000 == 0) {
        //    a[i] = uni(rng);  //插入一些随机数
        //}
    }

}

void ve() {
    std::random_device rnd;//random num device //效率低，只用于生成种子
    std::mt19937 rng(rnd()); //random num generator -- 生成随机数
    std::uniform_int_distribution<int> uni(0, 1000000000);//整型区间筛选
    //[0-N]有6成为不重复,4成重复 --若需要9成不重复需要扩大筛选范围为10倍的N,即插入N需筛选10N

    //int a[] = { 3,1,8,4,2,7,5,9,6,0 }; //自定义数组
    int size = 1000000;
    std::vector<int> a;
    std::cout << size << "个" << "随机数" << std::endl;
    //std::cout<<size<<"个"<<"逆序数"<<std::endl;
    //std::cout<<size<<"个"<<"正序数"<<std::endl;
    //std::cout<<size<<"个"<<"重复数"<<std::endl;
    for (int i = 0; i < size; i++) {
        //a[i] = uni(rng); //随机数
        a.emplace_back(uni(rng));
        //a[i] = size - i; //逆序
        //a[i] = i;         //正序
        //a[i] = size/2;     //重复数
        //if (i % 10000 == 0) {
        //    a[i] = uni(rng);  //插入一些随机数
        //}
    }

}

int main() {
    //testInsert();
    //testHight();

    Cost([&]() {std::cout << "cost: "; a(); });
    Cost([&]() {std::cout << "cost: "; v(); });
    Cost([&]() {std::cout << "cost: "; vp(); });
    Cost([&]() {std::cout << "cost: "; ve(); });
}

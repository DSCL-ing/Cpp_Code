
#include<iostream>
#include<mutex>
#include<atomic>
#include<queue>
#include<chrono>
#include<thread>
#include<functional>
#include<random>

#include<cassert>

//void Swap(int* a, int* b) {
//    int tmp =  *a;
//    *a = *b;
//    *b = tmp;
//}

static void Swap(int* p1, int* p2)
{
    int tmp = 0;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void AdjustDown(int* a, int size, int parent) {
    int child = parent * 2 + 1;

    while (child < size) {
        if (child + 1 < size && a[child + 1] > a[child]) {
            child++;
        }
        if (a[parent] < a[child]) {
            Swap(&a[parent], &a[child]);
            parent = child;
            child = parent * 2 + 1;
        }
        else {
            break;
        }
    }
}

void HeapSort(int* a, int size)
{
    assert(a);

    // ---- 1. 向下调整算法建堆  ----
    //时间复杂度O(n)
    int parent = (size - 1 - 1) / 2;
    while (parent >= 0)
    {
        AdjustDown(a, size, parent);
        parent--;
    }


    // ---- 2. 选数 ----
    //时间复杂度O(n*logN),n个数都要高度次调整
    //int end = size - 1; //下标版本
    //元素个数版本,能够复用删除写法
    while (size > 1) //元素个数大于1
    {
        Swap(&a[0], &a[size - 1]);		//交换
        size--;
        AdjustDown(a, size, 0);  //调整堆 -- 注意,此处end为元素个数
    }

}

void ShellSort(int* a, int n)
{
    int gap = n;
    while (gap > 1) {
        gap /= 2;    //任何数除以2,最后一定能得到1,gap==1就是最后一轮
        //gap = gap/3+1; //除以3不一定能得到1,需要+1保证一定得到1.

        for (int i = 0; i < n - gap; i += 1) { //最后一轮排序,需要保证end+gap<n,即end(i)<n-gap
            int end = i;
            int tmp = a[end + gap];  //间隔排序

            while (end >= 0) {
                if (a[end] > tmp) {
                    a[end + gap] = a[end];
                    end -= gap;
                }
                else {
                    break;
                }
            }
            a[end + gap] = tmp;
        }
    }
}

void hoare(int* a, int begin, int end) {

    //一个元素或没有元素时,递归结束
    if (begin >= end) {
        return;
    }

    int left = begin;
    int right = end;
    int keyi = left; //keyi == key index == key是下标

    while (left < right) {
        while (left < right && a[right] >= a[keyi]) {  //要找小于key的,大于等于都要走,不然执行不了函数体(下标移动),导致死循环
            right--;  //不能合并,要保证下标指向的是找到的那个值
        }
        while (left < right && a[left] <= a[keyi]) {
            left++;
        }
        Swap(&a[left], &a[right]);
    }

    Swap(&a[left], &a[keyi]);
    keyi = left;

    // [begin,keyi-1] keyi [keyi+1,end]
    hoare(a, begin, keyi - 1);
    hoare(a, keyi + 1, end);
}

//void _HoareQuickSort(int* a, int begin, int end)
//{
//
//    //int mid = getMidIndex(a, begin, end);//mid是中间索引（中间值的下标）
//    //Swap(&a[begin], &a[mid]); //获取到中间值的下标后对换begin和mid对应的值，使key对应的是中间值，消除有序
//
//    if (begin >= end) {
//        return;
//    }
//    int left = begin; int right = end;
//    int keyi = left;
//
//    while (left < right)
//    {
//        while (left < right && a[right] >= a[keyi])
//        {
//            right--;
//        }
//
//        while (left < right && a[left] <= a[keyi])
//        {
//            left++;
//        }
//
//        Swap(&a[left], &a[right]);
//    }
//    Swap(&a[keyi], &a[right]);
//    keyi = right;
//
//    _HoareQuickSort(a, begin, keyi - 1);
//    _HoareQuickSort(a, keyi + 1, end);
//
//}

int main() {

    std::random_device rnd;//random num device //效率低，只用于生成种子
    std::mt19937 rng(rnd()); //random num generator -- 生成随机数
    std::uniform_int_distribution<int> uni(0, 100000);//整型区间筛选
    //[0-N]有6成为不重复,4成重复 --若需要9成不重复需要扩大筛选范围为10倍的N,即插入N需筛选10N

    //int a[] = { 3,1,8,4,2,7,5,9,6,0 };
    int size = 10000000;
    int* a = new int[size];
    for (int i = 0; i < size; i++) {
        a[i] = uni(rng);
    }
    
    //for (int i = 0; i < size; i++) {
    //    std::cout<<a[i] <<" ";
    //}
    //std::cout<<"\n";
    //std::cout<<"\n";

    
    int* a1 = new int[size];
    memmove(a1,a,size*sizeof(int));
    //for (int i = 0; i < size; i++) {
    //    std::cout<<a1[i] <<" ";
    //}
    //std::cout<<"\n";
    //std::cout<<"\n";
    std::cout << "Shell:" << " ";
    auto begin1 = std::chrono::steady_clock::now();
    ShellSort(a1, size);
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost1 = end1 - begin1;
    std::cout << cost1.count() << "秒" << std::endl;
    
    //for (int i = 0; i < size; i++) {
    //    std::cout<<a1[i] <<" ";
    //}
   
    //int* a2 = new int[size];
    ////memcpy(a2,a,size);
    //memmove(a2,a,size*sizeof(int));
    //std::cout << "Heap:" << std::endl;
    //auto begin2 = std::chrono::steady_clock::now();
    //HeapSort(a2, size);
    //auto end2 = std::chrono::steady_clock::now();
    //std::chrono::duration<double> cost2 = end2 - begin2;
    //std::cout << cost2.count() << "秒" << std::endl;
 
    //for (int i = 0; i < size; i++) {
    //    std::cout<<a2[i] <<" ";
    //}

    int* a3 = new int[size];
    //memcpy(a3,a,size);
    memmove(a3,a,size*sizeof(int));
    std::cout << "hoare:" << " ";
    auto begin3 = std::chrono::steady_clock::now();
    hoare(a3,0,size-1);
    //_HoareQuickSort(a3,0,size-1);
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost3 = end3 - begin3;
    std::cout << cost3.count() << "秒" << std::endl;
    //std::cout<<std::boolalpha<< (a3[0] == a2[0] &&a3[0]==a1[0]&&a3[size-1]==a2[size-1]&&a3[size-1] == a1[size-1])<<std::endl;
    std::cout << std::boolalpha << (a3[0] == a1[0] && a3[size - 1] == a1[size - 1]) << std::endl;


    int* a4 = new int[size];
    //memcpy(a3,a,size);
    memmove(a4,a,size*sizeof(int));
    std::cout << "std::heap:" << " ";
    auto begin4 = std::chrono::steady_clock::now();
    std::make_heap(a4,a4+size);
    std::sort_heap(a4,a4+size);
    auto end4 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost4 = end4 - begin4;
    std::cout << cost4.count() << "秒" << std::endl;
    std::cout<<std::boolalpha<< (a4[0]==a1[0]&&a4[size-1] == a1[size-1])<<std::endl;

    //for (int i = 0; i < size; i++) {
    //    std::cout<<a4[i] <<" ";
    //}


    int* a5 = new int[size];
    //memcpy(a3,a,size);
    memmove(a5,a,size*sizeof(int));
    std::cout << "stl::sort:" << " ";
    auto begin5 = std::chrono::steady_clock::now();
    //std::make_heap(a5,a5+size);
    //std::sort_heap(a5,a5+size);
    std::sort(a5,a5+size);
    auto end5 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost5 = end5 - begin5;
    std::cout << cost5.count() << "秒" << std::endl;
    std::cout<<std::boolalpha<< (a5[0]==a1[0]&&a5[size-1] == a1[size-1])<<std::endl;
 
 //*a是指针,不是数组,迭代器只支持数组,不支持指针
    //for (int it : a) {
    //    std::cout << it << " ";
    //}


    return 0;
}

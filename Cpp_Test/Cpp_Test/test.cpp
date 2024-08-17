﻿
#include<iostream>
#include<mutex>
#include<atomic>
#include<queue>
#include<chrono>
#include<thread>
#include<functional>
#include<random>
#include<iomanip>

#include<cassert>

#if 1

void PrintArray(int* a, int size) ;
void RandomArray_Generator(int *a,int n) ;

static void Swap(int* p1, int* p2)
{
    int tmp = 0;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

// 时间复杂度：O(N*logN)
// 空间复杂度：O(N)
// [begin, end]
//void _MergeSort(int* a, int begin, int end, int* tmp)
//{
//    if (begin >= end)
//        return;
//
//    int mid = (begin + end) / 2;
//    // [begin, mid] [mid+1, end] 递归让子区间有序
//    _MergeSort(a, begin, mid, tmp);
//    _MergeSort(a, mid + 1, end, tmp);
//
//    // 归并[begin, mid] [mid+1, end]
//    //...
//
//    int begin1 = begin, end1 = mid;
//    int begin2 = mid + 1, end2 = end;
//    int i = begin;
//    while (begin1 <= end1 && begin2 <= end2)
//    {
//        if (a[begin1] <= a[begin2])
//        {
//            tmp[i++] = a[begin1++];
//        }
//        else
//        {
//            tmp[i++] = a[begin2++];
//        }
//    }
//
//    while (begin1 <= end1)
//    {
//        tmp[i++] = a[begin1++];
//    }
//
//    while (begin2 <= end2)
//    {
//        tmp[i++] = a[begin2++];
//    }
//
//    memcpy(a + begin, tmp + begin, sizeof(int) * (end - begin + 1));
//}
//
//void MergeSort(int* a, int n)
//{
//    int* tmp = (int*)malloc(sizeof(int) * n);
//    if (tmp == NULL)
//    {
//        perror("malloc fail");
//        exit(-1);
//    }
//
//    _MergeSort(a, 0, n - 1, tmp);
//
//    free(tmp);
//    tmp = NULL;
//}

void _MergeSort(int* a, int begin, int end, int* tmp) {
    if(begin>=end) return ;

    int mid = (begin+end)/2;

    //先划分(或先递归让左右子树有序),再归并 ---> 后序 
    _MergeSort(a,begin,mid,tmp);
    _MergeSort(a,mid+1,end,tmp);
    //归并
    int begin1 = begin; int end1 = mid; 
    int begin2 = mid+1; int end2 = end; 
    int i = begin;
    while (begin1 <= end1 && begin2 <= end2) {
        if (a[begin1] < a[begin2]) {
            tmp[i] = a[begin1++];
        }
        else {
            tmp[i] = a[begin2++];
        }
        i++;
    }

    //出来后一个满足另一个不满足
    while (begin1 <= end1) {
            tmp[i++] = a[begin1++];
    }
    while (begin2 <= end2) {
            tmp[i++] = a[begin2++];
    }
    memmove(a+begin,tmp+begin,sizeof(int)*(end-begin+1));
}

void MergeSort(int *a,int n) {
    //因为要使用额外空间,所以需要辅助函数
    int *tmp = (int*)malloc(sizeof(int)*n);
    if (tmp == NULL) {
        perror("malloc fail!");
        exit(-999);
    }
    _MergeSort(a,0,n-1,tmp);
    free(tmp);
    tmp = NULL;
}


//直接插入排序
void InsertSort(int* a, int n)
{
    assert(a && n); //a不能为空且n不能为0 (当n为0,则i为最大整型值,错误)

    //当n==1,边界
    //当n>1,执行算法
    //i==n-2,最后一次插入
    for (int i = 0; i < n - 1; i++) {
        int end = i;
        int tmp = a[end + 1]; //因挪动会将end+1位置覆盖,因此使用tmp保存准备插入的元素

        while (end >= 0) {
            //挪动覆盖
            if (a[end] > tmp) {      // a[end]>tmp升序, a[end]<tmp降序
                a[end + 1] = a[end];
                end--;
            }
            else {
                break;
            }
        }
        //挪动覆盖方式,结束时将tmp写入到目标位置
        a[end + 1] = tmp;
    }
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

int getMidIndex(int* a, int begin, int end) {
    int mid = (begin + end) / 2;
    if (a[begin] > a[mid])
    {
        if (a[mid] > a[end])	return mid;
        else if (a[begin] > a[end]) return end;
        else return begin;
    }
    else //a[begin] <= a[mid]
    {
        if (a[begin] > a[end]) return begin;
        else if (a[mid] > a[end]) return end;
        else return mid;
    }
}

void hoare(int* a, int begin, int end) {

    //一个元素或没有元素时,递归结束
    if (begin >= end) {
        return;
    }

    int mid = getMidIndex(a, begin, end);
    Swap(&a[begin], &a[mid]);

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





void hoare_small(int* a, int begin, int end) {

    //一个元素或没有元素时,递归结束
    if (begin >= end) {
        return;
    }
    int mid = getMidIndex(a, begin, end);
    Swap(&a[begin], &a[mid]);
    if (end - begin + 1 < 16) {
        InsertSort(a + begin, end - begin + 1);
    }
    else {
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
        hoare_small(a, begin, keyi - 1);
        hoare_small(a, keyi + 1, end);
    }
}

void hoare2(int* a, int begin, int end) {
    if (begin >= end) {
        return;
    }
    int mid = getMidIndex(a, begin, end);
    Swap(&a[begin], &a[mid]);

    if (end - begin + 1 < 16) {
        InsertSort(a, end - begin + 1);
    }
    else {
        int left = begin;
        int right = end;
        int key = a[left];
        int hole = left;
        while (left < right) {
            while (left < right && a[right] >= key) {
                right--;
            }
            a[hole] = a[right];
            hole = right;
            while (left < right && a[left] <= key) {
                left++;
            }
            a[hole] = a[left];
            hole = left;
        }
        //相遇位置是最后一个坑,用来放key
        a[hole] = key;

        //[begin,hole-1] hole [hole+1,end];
        hoare2(a, begin, hole - 1);
        hoare2(a, hole + 1, end);
    }
}



//类似算法题移动零
void tow_point(int* a, int begin, int end) {
    if (begin >= end) return;
    int mid = getMidIndex(a, begin, end);
    Swap(&a[begin], &a[mid]);
    if (end - begin + 1 < 16) {
        InsertSort(a, end - begin + 1);
    }
    else {
        int cur = begin + 1;
        int prev = begin;
        int keyi = begin;
        while (cur <= end) {
            //只有小于时交换
            //if (a[cur] < a[keyi]) {
            //    Swap(&a[cur],&a[++prev]);
            //}
            //cur++; 

            //只有小于时交换,相同时不交换
            if (a[cur] < a[keyi] && ++prev != cur) {
                Swap(&a[cur], &a[prev]);
            }
            cur++;
        }
        Swap(&a[prev], &a[keyi]);
        keyi = prev;

        // [begin,keyi-1] keyi [keyi+1,end]
        tow_point(a, begin, keyi - 1);
        tow_point(a, keyi + 1, end);
    }
}


//[begin , left-1] [left , right] [right , end]
void partitionQSort(int* a, int begin, int end)
{
    if (begin >= end)
    {
        return;
    }
    int mid = getMidIndex(a, begin, end);
    Swap(&a[begin], &a[mid]);

    int left = begin; int right = end;
    int cur = begin + 1;
    int key = a[left];

    while (cur <= right)
    {
        if (a[cur] < key)
        {
            Swap(&a[cur++], &a[left++]);//a[left]永远小于key
        }
        else if (a[cur] == key)
        {
            cur++;
        }
        else
        {
            Swap(&a[cur], &a[right--]);
        }
        /*
        * 如果是大于，则c不动，只控制right往前走，原因是不知道a[right]大小，再走就会出问题。
        解决方法：交换a[right--]后保持cur不动，让循环进入下一轮，比较新的a[cur]和key，
        在新一轮的循环中如果上一轮从right换过来的a[cur]比key大就丢回去，如果小于等于就按命令走
        这样就能保证	左边<key ,中间 == key ,右边>key
        */
    }

    partitionQSort(a, begin, left - 1);
    partitionQSort(a, right + 1, end);

}


void test_Insert(int size) {
    int* a = new int[size];
    RandomArray_Generator(a, size);
    PrintArray(a, size);
    std::cout << std::setw(15) << "Insert:" << " ";
    auto begin1 = std::chrono::steady_clock::now();
    ShellSort(a, size);
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<long double> cost1 = end1 - begin1;
    std::cout << cost1.count() << "秒" << std::endl;
}

void test_Shell(int size) {
    int* a = new int[size];
    RandomArray_Generator(a, size);
    PrintArray(a, size);
    std::cout << std::setw(15) << "Shell:" << " ";
    auto begin1 = std::chrono::steady_clock::now();
    ShellSort(a, size);
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost1 = end1 - begin1;
    std::cout << cost1.count() << "秒" << std::endl;

}

void test_Heap(int size) {

    int* a = new int[size];
    RandomArray_Generator(a, size);
    //PrintArray(a,size);
    std::cout << std::setw(15) << "Heap:" << " ";
    auto begin2 = std::chrono::steady_clock::now();
    HeapSort(a, size);
    auto end2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost2 = end2 - begin2;
    std::cout << cost2.count() << "秒" << std::endl;
}

void test_hoare(int size) {
    int* a = new int[size];
    RandomArray_Generator(a, size);
    //PrintArray(a,size);
    std::cout << std::setw(15) << "hoare:" << " ";
    auto begin3 = std::chrono::steady_clock::now();
    hoare(a, 0, size - 1);
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost3 = end3 - begin3;
    std::cout << cost3.count() << "秒" << std::endl;
}

void test_hoare_small(int size) {

    int* a = new int[size];
    RandomArray_Generator(a, size);
    //PrintArray(a, size);
    std::cout << std::setw(15) << "hoare_small:" << " ";
    auto begin3 = std::chrono::steady_clock::now();
    hoare_small(a, 0, size - 1);
    //_HoareQuickSort(a3,0,size-1);
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost3 = end3 - begin3;
    std::cout << cost3.count() << "秒" << std::endl;
}

void test_hoare2(int size) {

    int* a = new int[size];
    RandomArray_Generator(a, size);
    //PrintArray(a, size);
    std::cout << std::setw(15) << "hoare2:" << " ";
    auto begin3 = std::chrono::steady_clock::now();
    hoare2(a, 0, size - 1);
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost3 = end3 - begin3;
    std::cout << cost3.count() << "秒" << std::endl;
}


void test_towpoint(int size) {

    int* a = new int[size];
    RandomArray_Generator(a, size);
    //PrintArray(a, size);
    std::cout << std::setw(15) << "tow_point:" << " ";
    auto begin3 = std::chrono::steady_clock::now();
    tow_point(a, 0, size - 1);
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost3 = end3 - begin3;
    std::cout << cost3.count() << "秒" << std::endl;
}

void test_partition(int size) {
    int* a = new int[size];
    RandomArray_Generator(a, size);
    //PrintArray(a, size);
    std::cout << std::setw(15) << "3路划分:" << " ";
    auto begin3 = std::chrono::steady_clock::now();
    partitionQSort(a, 0, size - 1);
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost3 = end3 - begin3;
    std::cout << cost3.count() << "秒" << std::endl;
    //PrintArray(a, size);
}

void test_std_sort(int size) {

    int* a = new int[size];
    RandomArray_Generator(a, size);
    //PrintArray(a, size);
    std::cout << std::setw(15) << "std::sort:" << " ";
    auto begin5 = std::chrono::steady_clock::now();
    std::sort(a, a + size);
    auto end5 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost5 = end5 - begin5;
    std::cout << cost5.count() << "秒" << std::endl;
}

void test_std_heap(int size) {
    int* a = new int[size];
    RandomArray_Generator(a, size);
    //PrintArray(a, size);
    std::cout << std::setw(15) << "std::heap:" << " ";
    auto begin4 = std::chrono::steady_clock::now();
    std::make_heap(a, a + size);
    std::sort_heap(a, a + size);
    auto end4 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost4 = end4 - begin4;
    std::cout << cost4.count() << "秒" << std::endl;
}

void test_Merge(int size) {
    int* a = new int[size];
    RandomArray_Generator(a, size);
    //PrintArray(a, size);
    std::cout << std::setw(15) << "Merge:" << " ";
    auto begin4 = std::chrono::steady_clock::now();
    MergeSort(a,size);
    auto end4 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost4 = end4 - begin4;
    std::cout << cost4.count() << "秒" << std::endl;

    //PrintArray(a, size);
}


void PrintArray(int* a, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

void RandomArray_Generator(int* a, int n) {
    std::random_device rnd;//random num device //效率低，只用于生成种子
    std::mt19937 rng(rnd()); //random num generator -- 生成随机数
    std::uniform_int_distribution<int> uni(0, 1000000000);//整型区间筛选
    //[0-N]有6成为不重复,4成重复 --若需要9成不重复需要扩大筛选范围为10倍的N,即插入N需筛选10N

    //int tmp[] = { 3,1,8,4,2,7,5,9,6,0 }; //自定义数组
    //memcpy(a,tmp,40);
    int size = n;
    for (int i = 0; i < size; i++) {
        a[i] = uni(rng); //随机数
        //a[i] = size - i; //逆序
        //a[i] = i;         //正序
        //a[i] = size / 2;     //重复数
        if (i % 10000 == 0) {
            //a[i] = uni(rng);  //插入一些随机数
        }
    }
}


void test_sort(int size) {
    int* a = new int[size];
    RandomArray_Generator(a, size);

    //test_Insert( size);
    //test_Shell( size);
    //test_Heap(size);
    //test_hoare(size);
    //test_hoare_small(size);
    test_hoare2(size);
    test_partition(size);
    //test_towpoint( size);
    test_Merge(size);
    test_std_sort(size);
    //test_std_heap( size);

}

int main() {
    //std::cout<<std::scientific<<std::left; //科学计数法
    std::cout << std::fixed << std::setprecision(8) << std::left;        //保留小数,精度8位
    test_sort(1000000);

    return 0;
}

#else

#endif

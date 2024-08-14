
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
void tow_point(int *a, int begin,int end) {
    if(begin>=end) return ;
    int mid = getMidIndex(a,begin,end);
    Swap(&a[begin], &a[mid]);
    if (end - begin + 1 < 16) {
        InsertSort(a,end-begin+1);
    }
    else {
        int cur = begin+1;
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
                Swap(&a[cur],&a[prev]);
            }
            cur++; 
        }
        Swap(&a[prev], &a[keyi]);
        keyi = prev;

        // [begin,keyi-1] keyi [keyi+1,end]
        tow_point(a,begin,keyi-1);
        tow_point(a,keyi+1,end);
    }
}

void test_Insert(int* a, int size) {
    int* a1 = new int[size];
    memmove(a1, a, size * sizeof(int));
    //for (int i = 0; i < size; i++) {
    //    std::cout<<a1[i] <<" ";
    //}
    //std::cout<<"\n";
    //std::cout<<"\n";
    std::cout << std::setw(15) << "Insert:" << " ";
    auto begin1 = std::chrono::steady_clock::now();
    ShellSort(a1, size);
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<long double> cost1 = end1 - begin1;
    std::cout << cost1.count() << "秒" << std::endl;
    delete[] a1;
}

void test_Shell(int* a, int size) {
    int* a1 = new int[size];
    memmove(a1, a, size * sizeof(int));
    //for (int i = 0; i < size; i++) {
    //    std::cout<<a1[i] <<" ";
    //}
    //std::cout<<"\n";
    //std::cout<<"\n";
    std::cout << std::setw(15) << "Shell:" << " ";
    auto begin1 = std::chrono::steady_clock::now();
    ShellSort(a1, size);
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost1 = end1 - begin1;
    std::cout << cost1.count() << "秒" << std::endl;
    delete[] a1;

}

void test_Heap(int* a, int size) {

    int* a2 = new int[size];
    //memcpy(a2,a,size);
    memmove(a2, a, size * sizeof(int));
    std::cout << std::setw(15) << "Heap:" << " ";
    auto begin2 = std::chrono::steady_clock::now();
    HeapSort(a2, size);
    auto end2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost2 = end2 - begin2;
    std::cout << cost2.count() << "秒" << std::endl;
    delete[] a2;
}

void test_hoare(int* a, int size) {

    int* a3 = new int[size];
    //memcpy(a3,a,size);
    memmove(a3, a, size * sizeof(int));
    std::cout << std::setw(15) << "hoare:" << " ";
    auto begin3 = std::chrono::steady_clock::now();
    hoare(a3, 0, size - 1);
    //_HoareQuickSort(a3,0,size-1);
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost3 = end3 - begin3;
    std::cout << cost3.count() << "秒" << std::endl;
    //std::cout<<std::boolalpha<< (a3[0] == a2[0] &&a3[0]==a1[0]&&a3[size-1]==a2[size-1]&&a3[size-1] == a1[size-1])<<std::endl;
    //std::cout << std::boolalpha << (a3[0] == a1[0] && a3[size - 1] == a1[size - 1]) << std::endl;
    delete[] a3;
}

void test_hoare_small(int* a, int size) {

    int* a3 = new int[size];
    //memcpy(a3,a,size);
    memmove(a3, a, size * sizeof(int));
    std::cout << std::setw(15) << "hoare_small:" << " ";
    auto begin3 = std::chrono::steady_clock::now();
    hoare_small(a3, 0, size - 1);
    //_HoareQuickSort(a3,0,size-1);
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost3 = end3 - begin3;
    std::cout << cost3.count() << "秒" << std::endl;
    //std::cout<<std::boolalpha<< (a3[0] == a2[0] &&a3[0]==a1[0]&&a3[size-1]==a2[size-1]&&a3[size-1] == a1[size-1])<<std::endl;
    //std::cout << std::boolalpha << (a3[0] == a1[0] && a3[size - 1] == a1[size - 1]) << std::endl;

    //for (int i = 0; i < size; i++) {
    //    std::cout << a3[i] << " ";
    //}
    //std::cout << std::endl;

    delete[] a3;
}

void test_hoare2(int* a, int size) {

    int* a3 = new int[size];
    //memcpy(a3,a,size);
    memmove(a3, a, size * sizeof(int));
    std::cout << std::setw(15) << "hoare2:" << " ";
    auto begin3 = std::chrono::steady_clock::now();
    hoare2(a3, 0, size - 1);
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost3 = end3 - begin3;
    std::cout << cost3.count() << "秒" << std::endl;
    //std::cout<<std::boolalpha<< (a3[0] == a2[0] &&a3[0]==a1[0]&&a3[size-1]==a2[size-1]&&a3[size-1] == a1[size-1])<<std::endl;
    //std::cout << std::boolalpha << (a3[0] == a[0] && a3[size - 1] == a[size - 1]) << std::endl;
    //for (int i = 0; i < size; i++) {
    //    std::cout << a3[i] << " ";
    //}
    //std::cout << std::endl;

    delete[] a3;
}


void test_towpoint(int* a, int size) {

    int* a3 = new int[size];
    //memcpy(a3,a,size);
    memmove(a3, a, size * sizeof(int));
    std::cout << std::setw(15) << "tow_point:" << " ";
    auto begin3 = std::chrono::steady_clock::now();
    tow_point(a3, 0, size - 1);
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost3 = end3 - begin3;
    std::cout << cost3.count() << "秒" << std::endl;
    //std::cout<<std::boolalpha<< (a3[0] == a2[0] &&a3[0]==a1[0]&&a3[size-1]==a2[size-1]&&a3[size-1] == a1[size-1])<<std::endl;
    //std::cout << std::boolalpha << (a3[0] == a[0] && a3[size - 1] == a[size - 1]) << std::endl;
    //for (int i = 0; i < size; i++) {
    //    std::cout << a3[i] << " ";
    //}
    //std::cout << std::endl;

    delete[] a3;
}

void test_std_sort(int* a, int size) {

    int* a5 = new int[size];
    //memcpy(a3,a,size);
    memmove(a5, a, size * sizeof(int));
    std::cout << std::setw(15) << "std::sort:" << " ";
    auto begin5 = std::chrono::steady_clock::now();
    std::sort(a5, a5 + size);
    auto end5 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost5 = end5 - begin5;
    std::cout << cost5.count() << "秒" << std::endl;
    //std::cout<<std::boolalpha<< (a5[0]==a1[0]&&a5[size-1] == a1[size-1])<<std::endl;
    delete[] a5;
}

void test_std_heap(int* a, int size) {
    int* a4 = new int[size];
    //memcpy(a3,a,size);
    memmove(a4, a, size * sizeof(int));
    std::cout << std::setw(15) << "std::heap:" << " ";
    auto begin4 = std::chrono::steady_clock::now();
    std::make_heap(a4, a4 + size);
    std::sort_heap(a4, a4 + size);
    auto end4 = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost4 = end4 - begin4;
    std::cout << cost4.count() << "秒" << std::endl;
    //std::cout<<std::boolalpha<< (a4[0]==a1[0]&&a4[size-1] == a1[size-1])<<std::endl;
    delete[] a4;
    //for (int i = 0; i < size; i++) {
    //    std::cout<<a4[i] <<" ";
    //}
}


void test_sort(int n) {
    std::random_device rnd;//random num device //效率低，只用于生成种子
    std::mt19937 rng(rnd()); //random num generator -- 生成随机数
    std::uniform_int_distribution<int> uni(0, 1000000000);//整型区间筛选
    //[0-N]有6成为不重复,4成重复 --若需要9成不重复需要扩大筛选范围为10倍的N,即插入N需筛选10N

    //int a[] = { 3,1,8,4,2,7,5,9,6,0 };
    //int size = 1000000;
    int size = n;
    int* a = new int[size];
    for (int i = 0; i < size; i++) {
        //a[i] = uni(rng); //随机数
        a[i] = size - i; //逆序
        //a[i] = i;         //正序
        //a[i] = size/2;     //重复数
    }
    //for (int i = 0; i < size; i++) {
    //    std::cout << a[i] << " ";
    //}
    //std::cout << std::endl;

    //test_Insert(a, size);
    //test_Shell(a, size);
    //test_Heap(a, size);
    test_hoare(a, size);
    test_hoare_small(a, size);
    test_hoare2(a, size);
    test_towpoint(a,size);
    test_std_sort(a, size);
    //test_std_heap(a, size);

}

int main() {
    //std::cout<<std::scientific<<std::left; //科学计数法
    std::cout << std::fixed << std::setprecision(8) << std::left;        //保留小数
    test_sort(1000);
    //int a[] = { 5,1,8,4,2,7,5,9,6,4 };
    //std::cout<<getMidIndex(a,0,9);

    return 0;
}

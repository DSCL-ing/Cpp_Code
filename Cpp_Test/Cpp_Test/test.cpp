
#include<iostream>
#include<mutex>
#include<atomic>
#include<queue>
#include<chrono>
#include<thread>

#include<cassert>
typedef int HeapDataType;

void Swap(HeapDataType* p1, HeapDataType* p2)
{
	HeapDataType tmp = 0;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

//向上调整算法：从0插入建堆 以及 在堆的前提下插入 //不适合直接建堆（把数组从1开始向下建堆）
void AdjustUp(HeapDataType* a, int child)
{
	assert(a);
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
	
}


void AdjustDown(HeapDataType* a, int size, int parent)
{
	//假设左孩子大
	int child = parent * 2 + 1;

	//调整到叶子就结束
	while (child < size) //左孩子不存在,右孩子一定不存在
	{
		//向下调整算法-大堆:选出最大孩子
		if (child + 1 < size && a[child] < a[child + 1]) {
			child++;
		}
		//我小于我最大的孩子,就要交换,让他来当父亲,我当儿子 --- 因为大堆要选出最大的,只要最大的  
		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(HeapDataType* a, int size)
{
	assert(a);
	// ---- 1. 向下调整算法建堆  ----
	//时间复杂度O(n)
	//int parent = (size - 1 - 1) / 2;
	//while (parent >= 0)
	//{
	//	AdjustDown(a, size, parent);
	//	parent--;
	//}
	
	int child = 1;
	while (child < size) {
		AdjustUp(a,child);
		child++;
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

int main() {
	srand(time(nullptr));
	
	int size = 100000000;
	//int *a = new int[size];
	int *a = (int*)malloc(size*4);
	//int a[] = {1,3,5,2,6,5,4,7,9,8};
	for (int i = 0; i < size; i++) {
		a[i] = rand()%100+i;
	}
	//clock_t start = clock();
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	HeapSort(a,size);
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	auto end = std::chrono::steady_clock::now();
	//for (int i = 0; i < size; i++) {
	//	std::cout<<a[i]<<" ";
	//}

	//clock_t end = clock();
	std::chrono::duration<double> cost = end - start;
	std::cout<<cost.count()<<std::endl;

	//int a[] = {1,3,5,2,6,5,4,7,9,8};
	//HeapSort(a,10);
	//for (auto it : a) {
	//	std::cout<<it<<" ";
	//}

	return  0;
}

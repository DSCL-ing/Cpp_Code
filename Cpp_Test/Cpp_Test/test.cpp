
#include<iostream>
#include<mutex>
#include<atomic>
#include<queue>

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
	while (parent >= 0 && child > 0 && a[child] > a[parent]) //小堆:a[child] < a[parent]
	{														  
		Swap(&a[child], &a[parent]);
		child = parent;
		parent = (child - 1) / 2;
	}
}


#include<iostream>
#include<mutex>
#include<atomic>
#include<queue>
#include<chrono>
#include<thread>
#include<functional>

#include<cassert>

bool greater(int a, int b){
	return a>b;
}

bool less(int a, int b) {
	return a<b;
}

bool compare(int a, int b) {
	return greater(a,b); //升序
	//return less(a,b);  //降序
}

void InsertSort(int* a, int n)
{
	assert(a && n); //a不能为空且n不能为0 (当n为0,则i为最大整型值,错误)

	for (int i = 0; i < n - 1; i++) {
		int end = i;
		int tmp = a[end + 1];

		while (end >= 0) {
			if (a[end]>tmp){      // >升序, <降序
				a[end + 1] = a[end];
				end--;
			}
			else {
				break;
			}
		}
	}
}

int main() {
	int a[] = {3,1,8,4,2,7,5,9,6,0};
	InsertSort(a,10);
	for (int it : a) {
		std::cout<<it<<" ";
	}

	return 0;
}

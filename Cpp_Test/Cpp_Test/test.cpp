#include<iostream>
#include<thread>
#include<chrono>
#include<cstdlib>
#include<mutex>
#include<queue>

template<class T>
class  TaskQueue{

    //Task Type == T
    //定长队列+自动管理增删
    //同步 == 独占互斥锁
    //生产者生产 == 增加 -- bool?生产成功返回true,放不下false --- (生产者绝对知道自己已生产)生产:通知消费者
    //消费者消费 == 删除 -- bool?消费成功返回true,没有了false --- (同理)                    消费:通知生产者
public:
    bool isEmpty() {
        return _bqueue.empty();
    }
    bool isFull() {
        return _bqueue.size() == _capacity;
    }
    //AddTask
    bool Push(const T&t) {
        std::unique_lock<std::mutex> ul(_mtx);
        std::lock_guard
    }
    //DelTask
    bool Pop() {

    }


private:
    std::queue<T> _bqueue;
    std::mutex _mtx;
    size_t _capacity; //队列定长大小
};


int main() {
    return 0;
}


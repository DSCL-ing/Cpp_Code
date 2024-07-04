#include<iostream> //std::cout 
#include<thread> //std::thread
#include<mutex> //std::mutex, std::unique_lock, std::lock_guard
#include<queue> //std::queue
#include<condition_variable> //std::condition_variable
#include<functional> //std::bind

//设计概要
/*
    //定长队列+自动管理增删
    //同步 == 独占互斥锁
    //生产者生产 == 增加 -- bool?生产成功返回true,放不下false --- (生产者绝对知道自己已生产)生产:通知消费者
    //消费者消费 == 删除 -- bool?消费成功返回true,没有了false --- (同理)                    消费:通知生产者
*/

//单条件变量版 --  简化逻辑
template<class T>
class  BlockQueue {

public:
    bool isEmpty() {
        return _bqueue.empty();
    }
    bool isFull() {
        return _bqueue.size() == _capacity;
    }
    //AddTask
    void Push(const T& t) {
        std::unique_lock<std::mutex> lck(_mtx);
        while (isFull()) {
            cv.wait(lck);
        }
        _bqueue.push(t);
        std::cout << "模拟插入数据..." << t << "\n";
        lck.unlock();
        cv.notify_all();
    }
    //DelTask
    void Pop() {
        std::unique_lock<std::mutex>lck(_mtx);
        cv.wait(lck, [this]() {
            bool flag = isEmpty(); //为空时休眠
            return !flag; //增加可读性的策略
            });
        T t = _bqueue.front();
        _bqueue.pop();
        std::cout << "模拟处理数据..." << t << "\n";
        lck.unlock();
        cv.notify_all();
    }

private:
    std::queue<T> _bqueue;
    std::mutex _mtx;
    std::condition_variable cv;  //必须搭配all
    size_t _capacity = 5; //队列定长大小
};


int main() {
    BlockQueue<int> tq;
    auto produce = std::bind(&BlockQueue<int>::Push, &tq, std::placeholders::_1);
    auto consume = std::bind(&BlockQueue<int>::Pop, &tq);
    std::thread t1[5];
    std::thread t2[5];
    for (int i = 0; i < 5; i++) {
        t1[i] = std::thread(produce, i);
        t2[i] = std::thread(consume);
    }

    for (int i = 0; i < 5; i++) {
        t1[i].join();
        t2[i].join();
    }

    return 0;
}


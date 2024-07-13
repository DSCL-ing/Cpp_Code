#include <iostream>
#include <thread>
#include<chrono>
#include<string>
#include<queue>
#include<mutex>

class BlockQueue {
public:
    BlockQueue(const BlockQueue& q) = delete;
    BlockQueue& operator=(const BlockQueue& q) = delete;

    void Push() {

    }

    void Pop() {

    }

    static BlockQueue& GetInstance() {
        if (_instance.load() == nullptr) {
            std::lock_guard<std::mutex>lg(_mtx);
            if (_instance.load() == nullptr) {
                _instance.store(new BlockQueue); //内存顺序不会打乱,安全
            }
        }
        return *(_instance.load());
    }

private:
    BlockQueue() {}
    std::queue<int> _q;
    int _capacity = 5;
    static std::mutex _mtx;
    static std::atomic<BlockQueue*> _instance;
};
std::atomic<BlockQueue*> BlockQueue::_instance = nullptr;
std::mutex BlockQueue::_mtx;


int main() {
    BlockQueue::GetInstance();

    return 0;
}

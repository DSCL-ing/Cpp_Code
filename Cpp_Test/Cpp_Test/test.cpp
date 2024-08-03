
#include<iostream>
#include<mutex>
#include<atomic>
#include<queue>

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
                //预防 先指向再实例化的情况;
                //如果先指向,此时还没实例化,但_instance就不为nullptr了,其他线程就能拿走_instance,又因为没实例化好,一使用就会发生野指针等相关bug.
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
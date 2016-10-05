#ifndef __SYNCQUEUE_
#define __SYNCQUEUE_

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class SyncQueue {
    private:
        std::queue<T> queue;
        std::mutex mtx;
        std::condition_variable cond;

    public:
        void push (const T& val) {
            std::unique_lock<std::mutex> lck(mtx);
            queue.push(val);
            cond.notify_one();
        }

        void push (T&& val) {
            std::unique_lock<std::mutex> lck(mtx);
            queue.push(std::forward<T>(val));
            cond.notify_one();
        }

        void pop() {
            std::unique_lock<std::mutex> lck(mtx);
            queue.pop();
        }

        T& front() {
            std::unique_lock<std::mutex> lck(mtx);
            if (queue.empty()) {
                cond.wait(lck);
            }
            return queue.front();
        }

        const T& front() const {
            return const_cast<SyncQueue<T>*>(this)->front();
        }
};

#endif //__SYNCQUEUE_


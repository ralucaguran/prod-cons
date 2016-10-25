#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <functional>

#include "SyncQueue.h"
#include "Util.h"


class Task {
    private:
        int info;

    public:
        Task(int inf=0):info(inf) {
        }

        int operator()() {
            std::cout << info << std::endl;
            return 0;
        }
};


SyncQueue<std::function<void(void)>> taskQ;
auto task = [](int type)->void { 
    std::lock_guard<std::mutex> lck(stdoutLock);
    std::cout << "Thread " << std::this_thread::get_id() << " processes task of type " << type <<  std::endl;
};

void doProd(int type) {
    while(true) {
        taskQ.push(std::bind(task, type));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void doCons() {
    while(true) {
        auto task = taskQ.pop();
        task();
    }
}


int main() {
    std::thread prod1(doProd, 1);
    std::thread prod2(doProd, 2);
    std::thread cons1(doCons);
    std::thread cons2(doCons);
    std::thread cons3(doCons);
    prod1.join();
    prod2.join();
    cons1.join();
    cons2.join();
    cons3.join();

    return 0;
}


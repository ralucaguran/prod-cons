#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <functional>

#include "SyncQueue.h"

using namespace std;


class Task {
    private:
        int info;

    public:
        Task(int inf=0):info(inf) {
        }

        int operator()() {
            cout << info << endl;
            return 0;
        }
};

mutex coutMutex;

SyncQueue<function<void(void)>> taskQ;
auto task = [](int type)->void { 
    std::lock_guard<mutex> lck(coutMutex);
    cout << "Thread " << std::this_thread::get_id() << " processes task of type " << type <<  endl;
};

void doProd(int type) {
    while(true) {
        taskQ.push(bind(task, type));
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void doCons() {
    while(true) {
        auto task = taskQ.pop();
        task();
    }
}


int main() {
    thread prod1(doProd, 1);
    thread prod2(doProd, 2);
    thread cons1(doCons);
    thread cons2(doCons);
    thread cons3(doCons);
    prod1.join();
    prod2.join();
    cons1.join();
    cons2.join();
    cons3.join();

    return 0;
}


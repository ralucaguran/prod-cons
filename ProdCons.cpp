#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

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

SyncQueue<std::function<int(void)>> taskQ;

void doProd(int val) {
    while(true) {
        taskQ.push(Task(val));
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void doCons() {
    while(true) {
        auto task = taskQ.front();
        task();
    }
}


int main() {
    thread prod1(doProd, 7);
    thread prod2(doProd, 5);
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


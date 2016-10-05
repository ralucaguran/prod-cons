#include <thread>
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

void doProd() {
    while(true) {
        taskQ.push(Task(5));
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void doCons() {
    while(true) {
        auto task = taskQ.front();
        taskQ.pop();
        task();
    }
}


int main() {
    thread prod(doProd);
    thread cons(doCons);
    prod.join();
    cons.join();

    return 0;
}


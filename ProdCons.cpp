#include <thread>
#include <iostream>
#include <chrono>

#include "SyncQueue.h"

using namespace std;


struct Foo {
    int info;
    Foo(int inf=0):info(inf) {
    }
};

SyncQueue<Foo> q;

void doProd() {
    while(true) {
        q.push(5);
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void process(const Foo& foo) {
    cout << foo.info << endl;
}

void doCons() {
    while(true) {
        Foo qElem = q.front();
        q.pop();
        process(qElem);
    }
}

void printFirstElem(const SyncQueue<int>& q) {
    cout << q.front() << endl;
}

int main() {
    SyncQueue<int> q;
    q.push(112);
    printFirstElem(q);
    thread prod(doProd);
    thread cons(doCons);
    prod.join();
    cons.join();

    return 0;
}


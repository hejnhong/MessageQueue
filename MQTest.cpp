#include "Handler.h"
#include "MyHandler.h"
#include <iostream>
#include <thread>
#include <chrono>

void looper1() {
    std::cout<<"looper1 thread:"<<std::this_thread::get_id()<<std::endl;
    Looper::prepare("looper1");
    Looper::loop();
}

void looper2() {
    std::cout<<"looper2 thread:"<<std::this_thread::get_id()<<std::endl;
    Looper::prepare("looper2", 30);
    // test repeat init
    Looper::prepare();
    Looper::loop();
}

void task() {
    std::cout<<"task thread:"<<std::this_thread::get_id()<<std::endl;
    Handler* handler1 = new MyHandler(Looper::getLooperByName("looper1"));
    Handler* handler2 = new MyHandler(Looper::getLooperByName("looper2"));
    while (true) {
        static int id = 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
        if (id%2) {
            handler2->sendMessage(id, nullptr);
        } else {
            handler1->sendMessage(id, nullptr);
        }
        id++;
    }
}

int main() {
    // create thread for looper1
    std::thread looper1Thread(looper1);

    // create thread for looper2 after 2 seconds
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::thread looper2Thread(looper2);

    // create thread for handler after 2 seconds
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::thread taskThread(task);

    looper1Thread.join();
    looper2Thread.join();
    taskThread.join();
}
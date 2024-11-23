#include "MyHandler.h"
#include <thread>
#include <iostream>

MyHandler::MyHandler() : Handler() {}

MyHandler::MyHandler(Looper* looper) : Handler(looper) {}

void MyHandler::handleMessage(int id, void* userDate) {
    std::cout<<"thread: "<<std::this_thread::get_id()<<", "
             <<"handleMessage:"<<id<<std::endl;
}
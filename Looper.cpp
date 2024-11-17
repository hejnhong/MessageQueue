#include <thread>
#include "Looper.h"
#include "Handler.h"
#include <iostream>
#include <chrono>

std::mutex Looper::mMutex;
std::unordered_map<std::thread::id, Looper*> Looper::threadLooper;

Looper::Looper(std::string name, int queSize) : mName(name){
    mMsgQueue.setSize(queSize);
}

void Looper::prepare(std::string name, int queSize) {
    std::unique_lock<std::mutex> lock;
    if (threadLooper.find(std::this_thread::get_id()) != threadLooper.end()) {
        printf("current thread already has one looper\n");
        return;
    }
    Looper* looper = new Looper(name, queSize);
    threadLooper.emplace(std::pair<std::thread::id, Looper*>(std::this_thread::get_id(), looper));
}

void Looper::loop() {
    getLooper()->dispatchMsg();
}

void Looper::dispatchMsg() {
    while (true) {
        auto msg = mMsgQueue.pop();
        printf("message id = %d, will be handled\n", msg->id);
        if (msg->mHandler) {
            msg->mHandler->handleMessage(msg->id, msg->userDate);
        }
        Message::releaseMessage(msg);
    }
}

Looper* Looper::getLooperByName(std::string name) {
    std::lock_guard<std::mutex> lock(mMutex);
    for (const auto& [id, looper] : threadLooper) {
        if (looper->mName == name) {
            return looper;
        }
    }
    return nullptr;
}

Looper* Looper::getLooper() {
    std::lock_guard<std::mutex> lock(mMutex);
    auto looperPair = threadLooper.find(std::this_thread::get_id());
    if (looperPair != threadLooper.end()) {
        return looperPair->second;
    }
    return nullptr;
}

void Looper::addMsg(Message* msg) {
    mMsgQueue.push(msg);
}

void Looper::onHandlerRelease(Handler* handler) {
    printf("the handler will release, address = %p\n", handler);
    mMsgQueue.invalidateMsgs(handler);
}
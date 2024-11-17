#include "MessageQueue.h"
#include "Message.h"
#include <iostream>
#include <algorithm>

MessageQueue::MessageQueue() : mSize(10){
}

MessageQueue::~MessageQueue() {
    std::lock_guard<std::mutex> lock(mMutex);
    std::for_each(mQueue.begin(), mQueue.end(), Message::releaseMessage);
}

void MessageQueue::setSize(int size) {
    mSize = size;
}

void MessageQueue::push(Message* msg) {
    std::lock_guard<std::mutex> lock(mMutex);
    if (mQueue.size() == mSize) {
        printf("the queue is full, drop front message : %d\n", mQueue.front()->id);
        Message::releaseMessage(mQueue.front());
        mQueue.pop_front();
    }
    mQueue.emplace_back(msg);
    mCondVar.notify_one();
}

Message* MessageQueue::pop() {
    std::unique_lock<std::mutex> lock(mMutex);
    mCondVar.wait(lock, [this]{ return !mQueue.empty(); });
    auto msg = mQueue.front();
    mQueue.pop_front();
    return msg;
}

void MessageQueue::invalidateMsgs(Handler* handler) {
    std::unique_lock<std::mutex> lock(mMutex);
    for (const auto& msg : mQueue) {
        if (msg->mHandler == handler) {
            msg->mHandler = nullptr;
        }
    }
}
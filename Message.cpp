#include "Message.h"
#include <iostream>

std::list<Message*> Message::msgPool;
int Message::poolSize = 20;
std::mutex Message::mMutex;

Message::Message() : free(true) {

}

Message* Message::obtainMessage() {
    std::lock_guard<std::mutex> lock(mMutex);
    for (auto it = msgPool.begin(); it != msgPool.end(); it++) {
        if ((*it)->free) {
            (*it)->free = false;
            return *it;
        }
    }
    if (msgPool.size() < poolSize) {
        Message *msg = new Message();
        msg->free = false;
        msgPool.emplace_back(msg);
        return msg;
    }
    printf("no free msg and no free pool space, obtain fail");
    return nullptr;
}

void Message::releaseMessage(Message* msg) {
    std::lock_guard<std::mutex> lock(mMutex);
    msg->free = true;
}
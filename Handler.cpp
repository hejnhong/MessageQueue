#include "Handler.h"
#include "Message.h"
#include <iostream>
#include <thread>

Handler::Handler() : mLooper(nullptr) {
    Looper* looper = Looper::getLooper();
    if (!looper) {
        printf("fail, cur thread dose not exist looper\n");
    } else {
        mLooper = looper;
    }
}

Handler::Handler(Looper* looper) : mLooper(looper) {

}

Handler::~Handler() {
    mLooper->onHandlerRelease(this);
}

void Handler::sendMessage(int id, void* userDate) {
    std::cout<<"sendMessage:"<<id
            <<", thread:"<<std::this_thread::get_id()<<std::endl;
    if (!mLooper) {
        printf("fail, no looper");
        return;
    }
    Message* msg = Message::obtainMessage();
    if (!msg) {
        printf("obtain message fail");
        return;
    }
    msg->id = id;
    msg->userDate = userDate;
    msg->mHandler = this;
    mLooper->addMsg(msg);
}
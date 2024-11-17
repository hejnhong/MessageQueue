/*
    the message dispatcher
    if a thread run one looper,
    it should not do anything else
*/
#ifndef LOOPER_H
#define LOOPER_H

#include "MessageQueue.h"
#include "Message.h"
#include <unordered_map>
#include <thread>
#include <mutex>
#include <string>

class Looper {
public:
    Looper(std::string name, int queSize);
    /*
        init a looper for current thread
    */
    static void prepare(std::string name = "default", int queSize = 20);
    /*
        run the looper
    */
    static void loop();
    /*
        find the looper default by thread id
    */
    static Looper* getLooper();
    static Looper* getLooperByName(std::string name);
    
    /*
        add a message to the looper
    */
    void addMsg(Message* msg);
    /*
        called when a handler will be destroyed
    */
    void onHandlerRelease(Handler* handler);

private:
    void dispatchMsg();

private:
    std::string mName;
    MessageQueue mMsgQueue;
    static std::mutex mMutex;
    static std::unordered_map<std::thread::id, Looper*> threadLooper;
};

#endif // LOOPER_H
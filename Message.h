#ifndef MESSAGE_H
#define MESSAGE_H

#include <list>
#include <mutex>

class Handler;
class Message {
public:
    Message();
    /*
        obtain a message from the message pool
    */
    static Message* obtainMessage();
    /*
        release a message back to the message pool
    */
    static void releaseMessage(Message* msg);

    int id;
    void* userDate;
    Handler* mHandler;
private:
    bool free;

    static std::list<Message*> msgPool;
    static int poolSize;
    static std::mutex mMutex;
};

#endif // MESSAGE_H
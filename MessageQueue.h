#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include "Message.h"
#include <deque>
#include <mutex>
#include <condition_variable>

class Handler;
class MessageQueue {
public:
    MessageQueue();
    ~MessageQueue();
    void setSize(int size);
    /*
        push one message to the queue
    */
    void push(Message* msg);
    /*
        get one message from the queue
    */
    Message* pop();
    /*
        invalidate messages own to a certain handler
    */
    void invalidateMsgs(Handler* handler);

private:
    std::deque<Message*> mQueue;
    std::mutex mMutex;
    std::condition_variable mCondVar;
    int mSize;
};

#endif // MESSAGE_QUEUE_H
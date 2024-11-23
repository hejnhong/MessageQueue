/*
    the message sender
    as well as the real handler
*/
#ifndef HANDLER_H
#define HANDLER_H

#include "looper/Looper.h"

class Handler {
public:
    Handler();
    Handler(Looper* looper);
    virtual ~Handler();
    void sendMessage(int id, void* userDate);
    virtual void handleMessage(int id, void* userDate) = 0;
private:
    Looper* mLooper;
};

#endif // HANDLER_H
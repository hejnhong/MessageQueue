#ifndef MYHANDLER_H
#define MYHANDLER_H

#include "Handler.h"

class MyHandler : public Handler {
public:
    MyHandler();
    MyHandler(Looper* looper);
    void handleMessage(int id, void* userDate) override;
};


#endif //MYHANDLER_H
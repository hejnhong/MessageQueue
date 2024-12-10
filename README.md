# MessageQueue
This implementation draws inspiration from the Looper-Handler model in Android, which is a classic example of the producer-consumer pattern. In this model, the Looper acts as the consumer, waiting for messages from the producer and processing them. It is guaranteed that there is only one instance of a Looper per thread, and once a thread starts running a Looper, it cannot perform any other tasks. The Handler serves as the producer, responsible for sending messages to the Looper. The Handler also handles the messages dispatched by the Looper.

Here is a simple example of how to use the messageQueue in C++:

**1. Create a Looper Thread:**

  1) Initialize the Looper by calling Looper::prepare("looperName").
  2) Enter the Looper's loop by calling Looper::loop().
  3) The looperName parameter is an identifier that distinguishes this Looper from others. It can be thought of as the name of the Looper's thread.

**2. Create a Handler Object:**

  1) Typically, you would create a subclass of Handler and override the handleMessage() method to define the logic for handling received messages.
  2) In my example, I implemented a MyHandler class that inherits from Handler and overrides the handleMessage() method to print out the received message.

This is the basic usage of this model. For a more detailed example, you can refer to MQTest.cpp.





#include<iostream>

#include "Queue.hpp"
#include "QueueNode.hpp"

class Request;

class FCFSQueue: public Queue {

public:
    FCFSQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request);

    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
  virtual int length();
    virtual ~FCFSQueue();

private:
    QueueNode *head, *tail;
};

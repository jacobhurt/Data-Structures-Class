#ifndef QUEUE_H
#define QUEUE_H
class Request;
#include "QueueNode.hpp"
class Queue {

public:
    virtual void addRequest(Request *request) = 0;
    virtual Request *getRequest() = 0;
    virtual bool isEmpty() = 0;
    virtual void print() = 0;
  virtual int length() = 0;
    virtual ~Queue() {}

private:
  QueueNode *head, *tail;

};
#endif

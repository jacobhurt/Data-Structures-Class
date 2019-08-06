#include<iostream>

#include "Queue.hpp"
#include "QueueNode.hpp"

class Request;

class PIKUPQueue: public Queue {

public:
  PIKUPQueue(): head(nullptr), tail(nullptr) , cur(nullptr){}

  virtual void addRequest(Request *request);

  virtual Request *getRequest();
  virtual bool isEmpty();
  virtual void print(); 
  virtual ~PIKUPQueue();
  virtual int length();

private:
  bool is_between(int first, int second, int req);
  QueueNode *head, *tail;
  Request *cur;
};

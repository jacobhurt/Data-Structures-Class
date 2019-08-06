#include<iostream>

#include "Queue.hpp"
#include "QueueNode.hpp"

class Request;

class STRACKQueue: public Queue {

public:
  STRACKQueue(): head(nullptr), tail(nullptr) , cur(nullptr){}

  virtual void addRequest(Request *request);

  virtual Request *getRequest();
  virtual bool isEmpty();
  virtual void print(); 
  virtual ~STRACKQueue();
  virtual int length();

private:
  QueueNode *head, *tail;
  Request *cur;
};

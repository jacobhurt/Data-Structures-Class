#include<iostream>

#include "Queue.hpp"
#include "QueueNode.hpp"

class Request;

class CLOOKQueue: public Queue {

public:
  CLOOKQueue(): head(nullptr), tail(nullptr) , cur(nullptr), up(true){}

  virtual void addRequest(Request *request);

  virtual Request *getRequest();
  virtual bool isEmpty();
  virtual void print(); 
  virtual ~CLOOKQueue();
  virtual int length();

private:
  bool is_between(int first, int second, int req);
  QueueNode *head, *tail;
  Request *cur;
  bool up;
};

#include "FCFSQueue.hpp"
#include "Request.hpp"

void FCFSQueue::addRequest(Request *request) {
  QueueNode *rNode = new QueueNode(request);
  rNode->next(nullptr);

  if( isEmpty() ) {
    head = tail = rNode;
    head->next(nullptr);
  } else {
    tail->next(rNode);
    tail = rNode;
  }
}

Request *FCFSQueue::getRequest() {

  if( isEmpty() ) {
    std::cout << "Calling QueueNode::getRequest() on empty queue. Terminating...\n";
    exit(1);
  }
  Request *req = head->request();
  auto temp  = head->next();

  delete head;
  head = temp;

  return req;
}

bool FCFSQueue::isEmpty() {
  return head == nullptr;
}

void FCFSQueue::print() {
  for(auto cur = head; cur; cur = cur->next() )
    std::cout << cur->request()->time() << " " << cur->request()->track() << " " << cur->request()->sector() << std::endl;
}

int FCFSQueue::length(){
  int len = 0;
  QueueNode *temp = head;
  while(temp != nullptr){
    len++;
    temp = temp->next();
  }
  return len;
}
FCFSQueue::~FCFSQueue() {
  while( head != nullptr ) {
    QueueNode *node = head;
    head = node->next();
    delete node;
  }
}



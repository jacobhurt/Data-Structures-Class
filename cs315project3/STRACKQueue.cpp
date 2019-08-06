#include "STRACKQueue.hpp"
#include "Request.hpp"
#include <iostream>

void STRACKQueue::addRequest(Request *request) {
  
  QueueNode *rNode = new QueueNode(request);
  rNode->next(nullptr);

  if( isEmpty() ) {
    
    head = tail = rNode;
    head->next(nullptr);
  }
  else {  
    if(cur == nullptr){
      tail->next(rNode);
      tail = rNode;
      return;
    }
    if(cur->track() == request->track()){
      
      if(head->request()->track() != request->track()){
	rNode->next(head);
	head = rNode;
	return;
      }

      QueueNode *temp = head;
      
      while(1){

	if(temp != tail){
	  if(temp->next()->request()->track() == request->track() ){
	    temp = temp->next();
	  }
	  else{
	    
	    rNode->next(temp->next());
	    temp->next(rNode);
	    return;
	  }
	}
	else{
	  
	  tail->next(rNode);
	  tail = rNode;
	  return;
	}
      }
    }

    else{
      tail->next(rNode);
      tail = rNode;
      return;
    }
  }
}

Request *STRACKQueue::getRequest() {
  
  if( isEmpty() ) {
    std::cout << "Calling QueueNode::getRequest() on empty queue. Terminating...\n";
    exit(1);
  }
  
  //  if(cur != nullptr)
  //delete cur;
  
  cur = head->request();

  auto temp  = head->next();

  delete head;
  head = temp;
    
  return cur;
}

bool STRACKQueue::isEmpty() { 
  return head == nullptr; 
}

void STRACKQueue::print() {
  for(auto cur = head; cur; cur = cur->next() ) 
    std::cout << cur->request()->time() << " " << cur->request()->track() << " " << cur->request()->sector() << std::endl;
}

STRACKQueue::~STRACKQueue() {
  while( head != nullptr ) {
    QueueNode *node = head;
    head = node->next();
    delete node;
  }        
}

int STRACKQueue::length(){
  int len = 0;
  QueueNode *temp = head;
  while(temp != nullptr){
    len++;
    temp = temp->next();
  }
  return len;
}

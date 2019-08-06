#include "PIKUPQueue.hpp"
#include "Request.hpp"
#include <iostream>

bool PIKUPQueue::is_between(int first, int second, int req){

  if(first <= second){
    if(req >= first && req <= second)
      return 1;
    else
      return 0;
  }

  else if(second <= first){
    if(req >= second && req <= first)
      return 1;
    else
      return 0;
    
  }

  return 0;
}
void PIKUPQueue::addRequest(Request *request) {

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
    
    Request *temp_req = cur;
    QueueNode *temp = head;
    QueueNode *prev = nullptr;
    
    while(1){
      
      if(temp_req->track() == request->track()){

	if(temp == head){
	  if(head->request()->track() != request->track()){
	    rNode->next(head);
	    head = rNode;
	    return;
	  }
	}
      
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
	if(!is_between(temp_req->track(), temp->request()->track(), request->track())){
	  temp_req = temp->request();
	  prev = temp;
	  if(temp == tail){
	    tail->next(rNode);
	    tail = rNode;
	    return;
	  }
	  temp = temp->next();
	}
	else{
	  if(prev == nullptr){
	    rNode->next(head);
	    head = rNode;
	    return;
	  }
	  rNode->next(prev->next());
	  prev->next(rNode);
	  return;
	}
      }

    }
  }
}

Request *PIKUPQueue::getRequest() {
  
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

bool PIKUPQueue::isEmpty() { 
  return head == nullptr; 
}

void PIKUPQueue::print() {
  for(auto cur = head; cur; cur = cur->next() ) 
    std::cout << cur->request()->time() << " " << cur->request()->track() << " " << cur->request()->sector() << std::endl;
}

PIKUPQueue::~PIKUPQueue() {
  while( head != nullptr ) {
    QueueNode *node = head;
    head = node->next();
    delete node;
  }        
}

int PIKUPQueue::length(){
  int len = 0;
  QueueNode *temp = head;
  while(temp != nullptr){
    len++;
    temp = temp->next();
  }
  return len;
}

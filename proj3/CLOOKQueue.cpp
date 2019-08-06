#include "CLOOKQueue.hpp"
#include "Request.hpp"
#include <iostream>

bool CLOOKQueue::is_between(int first, int second, int req){

  if(first <= second){
    if(req >= first && req <= second){
      return 1;
    }
    return 0;
  }
  
  return 0;

}

void CLOOKQueue::addRequest(Request *request) {

  bool init_state = up;
  
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
      up = init_state;
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
	    up = init_state;
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
	      up = init_state;
	      return;
	    }
	  }
	  else{
	  
	    tail->next(rNode);
	    tail = rNode;
	    up = init_state;
	    return;
	  }
	}
      }

      else{
	if(!is_between(temp_req->track(), temp->request()->track(), request->track())){


	  if(temp_req->track() > temp->request()->track() && temp_req->track() <  request->track()){
	    if(prev == nullptr){
	      rNode->next(head);
	      head = rNode;
	      up = init_state;
	      return;
	    }
	    rNode->next(prev->next());
	    prev->next(rNode);
	    up = init_state;
	    return;
	      
	  }
	  else if(temp_req->track() > temp->request()->track() && temp_req->track() >  request->track()){

	    if(is_between(0,temp->request()->track(), request->track())){
	      if(prev == nullptr){
		rNode->next(head);
		head = rNode;
		up = init_state;
		return;
	      }
	      rNode->next(prev->next());
	      prev->next(rNode);
	      up = init_state;
	      return;
	      
	    }

	  }
	  
	  temp_req = temp->request();
	  prev = temp;
	  if(temp == tail){
	    tail->next(rNode);
	    tail = rNode;
	    up = init_state;
	    return;
	  }
	  temp = temp->next();
	}
	else{
	  if(prev == nullptr){
	    rNode->next(head);
	    head = rNode;
	    up = init_state;
	    return;
	  }
	  rNode->next(prev->next());
	  prev->next(rNode);
	  up = init_state;
	  return;
	}
      }

    }
  }
}

Request *CLOOKQueue::getRequest() {
  
  if( isEmpty() ) {
    std::cout << "Calling QueueNode::getRequest() on empty queue. Terminating...\n";
    exit(1);
  }
  
  //delete cur;
  
  cur = head->request();
  
  auto temp  = head->next();

  delete head;
  head = temp;
    
  return cur;
}

bool CLOOKQueue::isEmpty() { 
  return head == nullptr; 
}

void CLOOKQueue::print() {
  for(auto cur = head; cur; cur = cur->next() ) 
    std::cout << cur->request()->time() << " " << cur->request()->track() << " " << cur->request()->sector() << std::endl;
}

CLOOKQueue::~CLOOKQueue() {
  while( head != nullptr ) {
    QueueNode *node = head;
    head = node->next();
    delete node;
  }        
}

int CLOOKQueue::length(){
  int len = 0;
  QueueNode *temp = head;
  while(temp != nullptr){
    len++;
    temp = temp->next();
  }
  return len;
}

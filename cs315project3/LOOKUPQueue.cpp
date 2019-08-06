#include "LOOKUPQueue.hpp"
#include "Request.hpp"
#include <iostream>

bool LOOKUPQueue::is_between(int first, int second, int req){

  //std::cout<<"BETWEEN: "<<first<<" "<<second<<" "<<req<<"\n";

  if(up){
    if(first <= second){
      if(req >= first && req <= second)
	return 1;
      else
	return 0;
    }
    else{
      return 0;
    }
  }
  else{
    if(second <= first){
      if(req >= second && req <= first)
	return 1;
      else
	return 0;      
    }
    return 0;
  }
}
void LOOKUPQueue::addRequest(Request *request) {

  //std::cout<<"CUR_DIR: "<<up<<"\n";
  //print();
 
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

	  if(up){

	    //std::cout<<"Not in between and dir is up!!\n";
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
	      up = false;
	      //std::cout<<"FLIP: "<<up<<"\n";
	   
	      if(is_between(99,temp->request()->track(), request->track())){
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

	  else{

	    if(temp_req->track() < temp->request()->track() && temp_req->track() >  request->track()){
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
	    else if(temp_req->track() < temp->request()->track() && temp_req->track() <  request->track()){
	      up = true;

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

Request *LOOKUPQueue::getRequest() {
  
  if( isEmpty() ) {
    std::cout << "Calling QueueNode::getRequest() on empty queue. Terminating...\n";
    exit(1);
  }
  
  if(cur != nullptr){
    if(head->request()->track() > cur->track())
      up = true;
    else if(head->request()->track() < cur->track())
      up = false;
  }
  //delete cur;
  
  cur = head->request();
  
  auto temp  = head->next();

  delete head;
  head = temp;
    
  return cur;
}

bool LOOKUPQueue::isEmpty() { 
  return head == nullptr; 
}

void LOOKUPQueue::print() {
  for(auto cur = head; cur; cur = cur->next() ) 
    std::cout << cur->request()->time() << " " << cur->request()->track() << " " << cur->request()->sector() << std::endl;
}

LOOKUPQueue::~LOOKUPQueue() {
  while( head != nullptr ) {
    QueueNode *node = head;
    head = node->next();
    delete node;
  }        
}

int LOOKUPQueue::length(){
  int len = 0;
  QueueNode *temp = head;
  while(temp != nullptr){
    len++;
    temp = temp->next();
  }
  return len;
}

#include "Request.hpp"
#include "Queue.hpp"
#include "FCFSQueue.hpp"
#include "STRACKQueue.hpp"
#include "PIKUPQueue.hpp"
#include "LOOKUPQueue.hpp"
#include "CLOOKQueue.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#define NUMDISKS 5

struct Disk{
  char *name;
  Queue *queue;
  ofstream file;
  Request *cur_req;
  int track;
  int sector;
  bool busy;
  int count;
  Disk(): queue(nullptr), cur_req(nullptr), busy(false), track(0), sector(-1), count(1){}
};

Disk disks[5];


struct _event{
  int type;   // 1 for request, 2 for done, 3 for timer
  double timer;  // for done and timer
  Request* request;   // for request (type = 1)
  Disk* disk;
  struct _event* next;
};

typedef _event event;
typedef _event* link;

link list = NULL;


void addEventQueue(int ctype, double ctimer, Request* cr, Disk* id){
  
  link temp = (link)malloc(sizeof(event));
 
  temp->type = ctype;
  temp->timer = ctimer;
  temp->disk = id;
  temp->request = cr;
  
  if(list == NULL){
    list = temp;
    list->next = NULL;
    return;
  }
  
  link curr = list;

  while(curr!=NULL){
    if(ctimer > curr->timer){
      if(curr->next == NULL){
	curr->next = temp;
	temp->next = NULL;
	return;
      }
      else{
	if(ctimer > curr->next->timer){
	  curr = curr->next;
	}
	else{
	  temp->next = curr->next;
	  curr->next = temp;
	  return;
	}
      }
    }
    else{
      temp->next = curr;
      list = temp;
      return;
    }
  }
}

void removeHeadEventQueue(void){

  auto temp = list;
  list = list->next;
  if(temp != NULL)
    delete temp;
}

int getProcessTime(Disk *disk, Request * req){
  int tot_time = 0;
  //cout<<"PROCESS: "<<req->track()<<" "<<disk->track<<" "<<req->sector()<<" "<<disk->sector<<endl;
  disk->cur_req = req;
  
  if(req->track() > disk->track)
    tot_time += (30 * (req->track() - disk->track));
  else
    tot_time += (-30 * (req->track() - disk->track));
  
  if(req->sector() < (disk->sector+1))
    tot_time += (30 + req->sector() - (disk->sector + 1));
  else
    tot_time += (req->sector() - (disk->sector + 1) );

  tot_time += 1;

  disk->sector = req->sector();
  disk->track = req->track();
  
  return tot_time;
} 

void simulate(int time_interval){

  // Initialize the event queues
  char filename[100];

  ofstream timer_file;
  timer_file.open("TIMER.txt");

  timer_file<<"TIMER REPORT\nTIME\t";
  
  disks[0].queue = new FCFSQueue();
  disks[1].queue = new STRACKQueue();
  disks[2].queue = new PIKUPQueue();
  disks[3].queue = new LOOKUPQueue();
  disks[4].queue = new CLOOKQueue();

  disks[0].name = strdup("FCFS");
  disks[1].name = strdup("STRACK");
  disks[2].name = strdup("PICKUP");
  disks[3].name = strdup("LOOKUP");
  disks[4].name = strdup("CLOOK");

  for(int i=0; i< NUMDISKS; i++){
    strcpy(filename, disks[i].name);
    strcat(filename, ".txt");
    disks[i].file.open(filename);
    disks[i].file<<disks[i].name<<" REPORT\n";
    timer_file<<disks[i].name<<"\t";
    disks[i].file<<"#\tTrac\tSec\tEntr\tInit\tComp\tWait\tServ\tTminSys\n";
  }

  timer_file<<endl;
  
  int sim_time = 0;
  int time_duration;
  
  while(list != NULL){

    while(list->timer == sim_time){

      if(list->type == 1){
	list->disk->queue->addRequest(list->request);
	
	if(list->disk->busy == false){

	  if(!list->disk->queue->isEmpty()){

	    time_duration = getProcessTime(list->disk, list->disk->queue->getRequest());
	    
	    list->disk->file<<list->disk->count<<"\t"<<list->disk->cur_req->track()<<"\t"<<list->disk->cur_req->sector()<<"\t"<<(list->disk->cur_req->time())/10.0<<"\t"<<sim_time/10.0<<"\t"<<(sim_time+time_duration)/10.0<<"\t"<<(sim_time-list->disk->cur_req->time())/10.0<<"\t"<<time_duration/10.0<<"\t"<<(sim_time+time_duration-list->disk->cur_req->time())/10.0<<"\n";
	    list->disk->count++;
	    
	    addEventQueue(2, sim_time + time_duration, NULL, list->disk);

	    list->disk->busy = true;
	  }
	}
      }
      if(list->type == 2){

	if(!list->disk->queue->isEmpty()){

	  time_duration = getProcessTime(list->disk, list->disk->queue->getRequest());
	  
	  list->disk->file<<list->disk->count<<"\t"<<list->disk->cur_req->track()<<"\t"<<list->disk->cur_req->sector()<<"\t"<<(list->disk->cur_req->time())/10.0<<"\t"<<sim_time/10.0<<"\t"<<(sim_time+time_duration)/10.0<<"\t"<<(sim_time-list->disk->cur_req->time())/10.0<<"\t"<<time_duration/10.0<<"\t"<<(sim_time+time_duration-list->disk->cur_req->time())/10.0<<"\n";
	    list->disk->count++;
	    
	  addEventQueue(2, sim_time + time_duration, NULL, list->disk);

	}

      }
      
      if(list != NULL)
	removeHeadEventQueue();
      
      if(list == NULL){

	for(int i=0; i< NUMDISKS; i++){
	  disks[i].file.close();
	}
	timer_file.close();
	break;
      }
    }

    // Timer Interrupt
    if(sim_time % time_interval == 0 && sim_time != 0){
      timer_file<<sim_time/10.0<<"\t";
      for(int i=0; i< NUMDISKS; i++){
	timer_file<<disks[i].queue->length()<<"\t";
	}
      timer_file<<endl;
    }
    sim_time++;
  }
}
int main() {

  ifstream myFile;
  myFile.open("inputRequests.txt");

  int track, sector, rno = 0;
  double aTime;

  Request* array[100];
  int len_req = 0;
  
  if(myFile.is_open()){
    while(1){
      
      myFile >> aTime >> track >> sector;
      
      if(myFile.eof())
	break;
      
      Request *r = new Request(aTime, track, sector);
      for(int i=0; i<NUMDISKS; i++)
	addEventQueue(1, aTime, r, &disks[i]);
      array[len_req] = r;
      len_req++;
    }
  }

  myFile.close();
  simulate(500);

  for(int i=0; i<len_req; i++){
    delete array[i];
  }
}

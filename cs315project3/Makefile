
CFLAGS=-std=c++11 -g

OBJECTS=QueueNode.o FCFSQueue.o STRACKQueue.o PIKUPQueue.o LOOKUPQueue.o CLOOKQueue.o main.o

all: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o out

QueueNode.o: QueueNode.cpp QueueNode.hpp
	g++ $(CFLAGS) -c QueueNode.cpp -o QueueNode.o

%Queue.o: %Queue.cpp %Queue.hpp QueueNode.hpp 
	g++ $(CFLAGS) -c $*Queue.cpp -o $*Queue.o

main.o: main.cpp FCFSQueue.hpp QueueNode.hpp STRACKQueue.hpp PIKUPQueue.hpp LOOKUPQueue.hpp CLOOKQueue.hpp
	g++ $(CFLAGS) -c main.cpp -o main.o

FCFSQueue.o: FCFSQueue.hpp FCFSQueue.cpp
	g++ $(CFLAGS) -c FCFSQueue.cpp -o FCFSQueue.o

STRACKQueue.o: STRACKQueue.hpp STRACKQueue.cpp
	g++ $(CFLAGS) -c STRACKQueue.cpp -o STRACKQueue.o

PIKUPQueue.o: PIKUPQueue.hpp PIKUPQueue.cpp
	g++ $(CFLAGS) -c PIKUPQueue.cpp -o PIKUPQueue.o

LOOKUPQueue.o: LOOKUPQueue.hpp LOOKUPQueue.cpp
	g++ $(CFLAGS) -c LOOKUPQueue.cpp -o LOOKUPQueue.o

CLOOKQueue.o: CLOOKQueue.hpp CLOOKQueue.cpp
	g++ $(CFLAGS) -c CLOOKQueue.cpp -o CLOOKQueue.o

clean:
	rm -fr *~ $(OBJECTS) out

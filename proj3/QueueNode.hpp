
#ifndef __QueueNode_hpp
#define __QueueNode_hpp

class Request;

class QueueNode {
public:
    QueueNode(Request *req, QueueNode *nextPtr);
    QueueNode(Request *req);
    QueueNode *next();
    void next(QueueNode *node);
    Request *request();

private:
    QueueNode *_next;
    Request *_request;
};

#endif

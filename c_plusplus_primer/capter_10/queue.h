#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <iostream>
#include "queue.h"


struct Node{
	Item item;
	struct Node *next;
};

class Queue{
	enum{QUEUE_SIZE = 10};
public:
	Queue(int qs=QUEUE_SIZE);
	Queue();
	~Queue();
	bool isEmpty() const;
	bool isFull() const;
	int queuecount() const;
	bool enqueue(const Item &item);
	bool dequeue(Item &item);
private:
	Queue(const Queue &) =delete;
	Queue &operator=(const Queue &) =delete;
	Node *front;
	Node *rear;
	int item_num;
	const int qs_size;
};

#endif
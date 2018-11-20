#include "queue.h"
using namespace std;

Queue::Queue():qs_size(QUEUE_SIZE){
	front = nullptr;
	rear = nullptr;
	item_num = 0;
}

Queue::Queue(int qs):qs_size(qs){
	front = nullptr;
	rear = nullptr;
	item_num = 0;
	qs_size = qs;
}

Queue::~Queue(){
	Node *cur_ptr = front;
	while (front != nullptr){
		cur_ptr = front;
		front = front->next;
		delete front;
	}
	rear = nullptr;
}

bool Queue::isEmpty() const{
	if (item_num == 0){
		return true;
	}
	return false;
}

bool Queue::isFull() const{
	if (item_num == qs_size){
		return true;
	}
	return false;
}

int queuecount() const{
	return item_num;
}

bool enqueue(const Item &item){
	if (isFull()){
		cout << "the queue is full!" << endl;
		return false;
	}
	Node *node = new Node;
	node.item = item;
	node.next = nullptr;
	if (isEmpty()){
		front = node;
	}else{
		rear->next = note;
	}
	rear = node;
	item_num++;
	return true;
}

bool dequeue(Item &item){
	if (isEmpty()){
		return false;
	}
	item = front->item;
	if (front == rear){
		rear = nullptr;
	}
	front = front->next;
	item_num--;
	return true;
}




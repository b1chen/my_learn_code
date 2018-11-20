#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_
#include <iostream>
class Customer{
public:
	Customer(int arrive){arrived_time=0; process_time=0;}
	~Customer(){};
	void set(long when){
		arrived_time = when;
		process_time = std::rand() % 3 + 1;
	}
	long when() const {return arrived_time;}
	int ptime() const {return process_time;}
private:
	int arrived_time;
	int process_time;
};

typedef Customer Item;
#endif
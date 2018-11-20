#include "queue.h"
#include <ctime>
#include <cstdlib>
using namespace std;
#define average_customers_by_hour 60

bool new_customer(double avg_num){
	return ((avg_num*rand()/RAND_MAX) < 1);
}
int main(){
	srand(time(0));
	cout << "input simulation: queue_size alltime_by_hour num_of_customers_by_hour" << endl;
	int queue_size;
	int alltime;
	int num_of_customers_by_hour;
	cin >> queue_size >> alltime >> num_of_customers_by_hour;
	Queue *queue = new Queue(queue_size);
	
	Item temp;
	long turnaways = 0;
	long customers = 0;
	long served = 0;
	long sum_line = 0;
	int wait_time =0;
	long line_wait = 0;
	
	for (int minute = 0; minute < alltime * 60; minute++){
		if (new_customer(average_customers_by_hour)){
			if (queue.isFull()){
				turnaways++;
			}else{
				customers++;
				temp.set(minute);
				queue.enqueue(temp);
			}
		}
		if (wait_time <= 0 && !queue.isEmpty()){
			queue.dequeue(temp);
			wait_time = temp.ptime();
			line_wait += minute - temp.when();//this use wait time(inqueue ----- outqueue)
			served++;
		}
		if (wait_time > 0){
			wait_time--;
		}
		sum_line += queue.queuecount();
	}
	
	if (customers > 0){
		cout << "customers accepted: " << customers << endl;
		cout << "  customers served: " << served << endl;
		cout << "         turnaways: " << turnaways << endl;
		cout << "average queue size: " ;
		cout.precision(2);
		cout.setf(ios_base::fixed, ios_base::floatfield);
		cout << (double)sum_line / (alltime * 60) << endl;
		cout << " average wait time: "
			<< (double) line_wait / served << "minutes\n";
	}else{
		cout << "No customer!\n";
	}
	cout << "Done!\n"
	return 0;
}
#ifndef STACK00_H_
#define STACK00_H_
#include <string>

class Stack{
private:
	std::string company;
	long shares;//股票数量
	double share_val;
	double total_val;
	void set_tot(){total = shares * share_val;}
public:
	void acquire(const std::string &company_name, long number_of_shares, double price);
	void buy(long num, double price);
	void sell(long num, double price);
	void update(double price);
	void show();
};

#endif
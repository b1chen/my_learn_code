#include <iostream>
#include "stock00.h"

void Stock::acquire(const std::string &company_name, long number_of_shares, double price){
	company = company_name;
	if (number_of_shares < 0){
		std::cout << "Number of share can't be negative;"
			<< company_name << " shares set to 0.\n";
		shares = 0;
	}
	else
		shares = number_of_shares;
	share_val = price;
	set_tot();
}

void Stock::buy(long num, double price){
	if (num < 0){
		std::cout << "Number of share purchased can't be negative. "
			<< "Transaction is aborted.\n";
	}else{
		shares += num;
		share_val = price;
		set_tot();
	}
}

void Stock::sell(long num, double price){
	using std::cout;
	if (num < 0){
		cout << "Number of share sold can't be negative. "
			<< "Transaction is aborted.\n";
	}else if (num > shares){
		cout << "you can't sell more than you have"
			<< "Transaction is aborted.\n";
	}else{
		shares -= num;
		share_val = price;
		set_tot();
	}
}

void Stock::update(double price){
	share_val = price;
	set_tot();
}

void Stock::show(){
	using std::cout;
	cout << "Company: " << company
		 << "	Shares:" << shares << '\n'
		 << "	Share Price: $" << share_val
		 << "	Total Worth: $" << total_val << '\n';
}

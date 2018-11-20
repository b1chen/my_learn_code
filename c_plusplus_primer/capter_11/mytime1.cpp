#include <iostream>
#include "mytime1.h"

Time::Time(){
	hours = minutes = 0;
}

Time::Time(int h, int m){
	hours = h;
	minutes = m;
}

void Time::AddMin(int m){
	hours += (minutes + m) / 60;
	minutes = (minutes + m) % 60; 
}

void Time::AddHr(int h){
	hours += h;
}

void Time::Reset(int h, int m){
	hours = h;
	minutes = m;
}

Time Time::operator+(const Time &t) const{
	Time sum;
	sum.hours = hours + t.hours + (minutes + t.minutes)/60;
	sum.minutes = (minutes + t.minutes)%60;
	return sum;
}

void Show() const{
	std::cout << hours << " hours, " << minutes << " minutes";
}


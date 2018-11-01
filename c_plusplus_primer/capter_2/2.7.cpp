#include <iostream>

using namespace std;
class AllMonth{
public:
	AllMonth(unsigned int year):year(year)
	{}
	bool is_spec_years(unsigned int year){
		if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)){
			return true;
		}
		return false;
	}

	unsigned int feb_month_days(unsigned int year){
		return is_spec_years(year) ? 29 : 28;
	}

	unsigned int month_days(unsigned int year, unsigned month){
		if (month < 1 || month > 12){
			cout << "wrong month number" << endl;
			return 0xffff;
		}
		unsigned days = 0xffff;
		switch (month){
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				days = 31;
				break;
			case 2:
				days = feb_month_days(year);
				break;
			default:
				days = 30;
				break;
		}

		return days;
	}
	unsigned int all_month(){
		unsigned int all_days = 0;
		for (int year_idx = 0; year_idx <= year; year_idx++){
			for (int month_idx = 1; month_idx <= 12; month_idx++){
				all_days += month_days(year_idx, month_idx);
			cout << "year:month -- "<< year_idx << " : " << month_idx << " days:" << month_days(year_idx, month_idx) << endl;
			}
		}
		return all_days;
	}
private:
	unsigned int year;
};

int main(){
	unsigned int year;
	cin >> year;
	AllMonth all(year);
	cout << all.all_month() << endl;
}

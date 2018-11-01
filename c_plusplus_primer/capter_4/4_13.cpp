#include <iostream>
#include <string>
#include <cstring>
int func_4_13_2(){
	using namespace std;
	cout << "What is your first name?";
	string first_name;
	getline(cin, first_name);
	cout << "What is your last name?";
	string last_name;
	getline(cin, last_name);
	cout << "What letter grade do you deserve?";
	string grade;
	cin >> grade;
	cout << "What is your age?";
	string age;
	cin >> age;
	
	cout << "Name: " << last_name << ", " << first_name << endl;
	cout << "Grade: " << grade << endl;
	cout << "Age: " << age << endl;
	return 0;
}

int func_4_13_1(){
        using namespace std;
        cout << "What is your first name?";
        char first_name[20];
        cin.getline(first_name, 20);
        cout << "What is your last name?";
        char last_name[20];
        cin.getline(last_name, 20);
        cout << "What letter grade do you deserve?";
        char grade[20];
        cin >> grade;
        cout << "What is your age?";
        char age[20];
        cin >> age;

        cout << "Name: " << last_name << ", " << first_name << endl;
        cout << "Grade: " << grade << endl;
        cout << "Age: " << age << endl;
        return 0;
}

int func_4_13_3(){
	using namespace std;
	cout << "in funciton:" << __func__ << endl;
	cout << "Enter your first name:";
	char first_name[20];
	cin.getline(first_name, 20);
	cout << "Enter your last name:";
	char last_name[20];
	cin.getline(last_name, 20);
	char all_name[40];
	strcpy(all_name, last_name);
	strcat(all_name, ", ");
	strcat(all_name, first_name);
	cout << "Here's the information in a single string: " << all_name << endl;
	return 0;
}

int func_4_13_4(){
	return 0;
}

int func_4_13_5(){
	return 0;
}

int func_4_13_6(){
	return 0;
}

typedef int (*func_ptr)();
func_ptr func_ptrs[10] = {
	func_4_13_1,
	func_4_13_2,
	func_4_13_3,
	func_4_13_4,
	func_4_13_5,
	func_4_13_6,
};



int main(){
	func_ptrs[2]();
}

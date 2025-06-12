#include <iostream>
#include <vector>

using namespace std; 



int main() {
	vector <int> hours; 
	vector <double> payRate; 
	int numEmployee, index; 
	cout << "How many Employees?";
	cin >> numEmployee; 

	for (index = 0; index < numEmployee; index++) {
		int tempHours, double tempRate; 
		cout << "Hours worked by Employee: ";
		cin >> tempHours;
		hours.push_back(tempHours);
		cout << "Hourly payRate for employee: ";
		cin >> tempRate;;
		payRate.push_back(tempRate);
	}
	for (index = 0; index < numEmployee; index++) {
		double grossPay = hours[index] * payRate[index];
		cout << grossPay;
	}
	return 0;
}
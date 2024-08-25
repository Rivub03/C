#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include <strstream>
#include <sstream>
#include <cstdlib>
#include <array>
#include <iomanip>
#include <cmath>
using namespace std;

#define PI 3.14159265358979323846 // this is a macro with macro_name and macro_definition

struct Circle { // structure declaration 
	double radius; // member declaration 
	double diameter;
	double area;
};

struct CityInfo {
	string cityName;
	string state; 
	long population; 
	int distance; 
};

struct BookInfo {
	string title; 
	string author;
	string publisher; 
	double price;
};

//Nested structures
struct Costs {
	double wholesale;
	double retail;
};
struct Item {
	string partNumber; 
	string description;
	Costs pricing; // this is a nested structure 
};


int main() {
	
	Circle c; // defining structure variable or instance
	cout << "Enter diameter of circle" << endl;
	cin >> c.diameter; // dot operator allows for the access of structure members
	c.radius = c.diameter / 2; //allows us to use member variables like normal variables
	c.area = PI * pow(c.radius, 2.0);
	cout << "The radius and area of the circle are: Radius - " << c.radius << " Area - " << c.area << endl; 

	CityInfo location = { "Toronto" ,  "Ontario" , 750000, 100}; // initializing the cityinfo structure 

	//array of structures
	BookInfo booklist[5];// declaring an array of structures, where the booklist array will have 20 elements, each element having its members
	booklist[0] = { "Harry Potter", "JK Rowling", "Bloomsburry", 30 };
	booklist[1] = { "Beyond Order", "Jordan Peterson", "Penguin", 25 };
	booklist[2] = { "The Prince", "Niccolo Machiavelli", "Finger Publishing", 10 };
	booklist[3] = { "The Art of War", "Sun Tzu", "RR publishing", 15 };
	for (int i = 0; i < 5; i++) { // loop for array of structures
		cout << i + 1 << ". Title: " << booklist[i].title; 
		cout << " Author: " << booklist[i].author;
		cout << " Publisher: " << booklist[i].publisher;
		cout << " Price: " << booklist[i].price << endl; 
	}

	//Nested structures
	Item widget;
	widget.partNumber = "IDK";
	widget.description = "Does something";
	widget.pricing.retail = 100.0; //nested structure where cost structure is client of item structure
	widget.pricing.wholesale = 76.95; 


		

	return 0;
}

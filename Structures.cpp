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

struct PayInfo { // to demonstrate dynamic structure allocation 
	double hours; 
	double PayRate; 
	double gross;
};

struct Rectangle {
	double length;
	double width; 
	double area; 
};

struct GradeInfo { // to demonstrate pointers as structure members
	string name;
	int* testScores; // testscores is a pointer (i.e., a memory location) because we might want to dynamically allocate this array since we might not known the length of the data
	float average; 
};

double multiply(double, double); //simple function to accept structure members
void showRect(Rectangle); // simple function that accepts a whole structure as argument
void getItem(Item&); //gets item structure and modifies it using a reference parameter 
void ShowItem(Item); // same as showrect
Circle getCircleData(); // returns circle structure from the function
void getCircleData(Circle*); // overloading

int main() {

	Circle c; // defining structure variable or instance
	cout << "Enter diameter of circle" << endl;
	cin >> c.diameter; // dot operator allows for the access of structure members
	c.radius = c.diameter / 2; //allows us to use member variables like normal variables
	c.area = PI * pow(c.radius, 2.0);
	cout << "The radius and area of the circle are: Radius - " << c.radius << " Area - " << c.area << endl;

	CityInfo location = { "Toronto" ,  "Ontario" , 750000, 100 }; // initializing the cityinfo structure 

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

	//structures as function arguments
	Rectangle box;
	box.length = 10.5;
	box.width = 12.82;
	box.area = multiply(box.length, box.width);
	showRect(box);

	Item part;
	getItem(part);
	ShowItem(part);

	//returning circle structure
	Circle myCircle;
	myCircle = getCircleData();

	//pointers to structures 
	Circle* cirPtr; // a pointer of circle type
	cirPtr = &myCircle; //points to myCircle variable of circle type
	cout << "Radius: " << (*cirPtr).radius << endl; //this is how to use deferencing to show value of member of structure variable
	cout << "Diameter: " << (*cirPtr).diameter << endl; // because dot operator has higher precedence than the indirection operator, so the indirection operator tries to dereference cirPtr.radius, not cirPtr
	cout << "Area: " << cirPtr->area << endl; // a more convenient notation called structure pointer operator 

	Circle c2;
	getCircleData(&c2);
	cout << "Here is the data of the new circle: " << endl;
	cout << "Radius: " << c2.radius << endl;
	cout << "Diameter: " << c2.diameter << endl;
	cout << "Area: " << c2.area << endl;

	//Dynamically Allocating structures
	int n;
	cout << "How many workers? " << endl;
	cin >> n;
	PayInfo* workers = new PayInfo[n];
	for (int i = 0; i < n; i++) {
		cout << "Enter the hours worked by worker[" << i + 1 << "]";
		cin >> workers[i].hours;
		cout << endl << "Enter the pay rate of worker[" << i + 1 << "]";
		cin >> workers[i].PayRate;
		workers[i].gross = multiply(workers[i].hours , workers[i].PayRate); 
		cout << endl << "The gross pay for worker [" << i + 1 << "] is: " << workers[i].gross << endl;
	}

	//pointers as structure members
	GradeInfo student1;
	student1.name = "Rivu"; 
	student1.testScores = new int[10]; // pointer stores memory location 
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		student1.testScores[i] = i + 1;
		sum += student1.testScores[i];
	}
	student1.average = sum / 10; 
	cout << student1.name << endl; 
	cout << student1.testScores << endl; // will give memory location
	cout << *student1.testScores << endl;
	for (int i = 0; i < 10; i++) {
		cout <<  *student1.testScores++ << ", ";
	}
	cout << endl <<"The Average is: " << student1.average << endl;

	return 0;
}

double multiply(double x, double y) { 
	return x * y;
}

void showRect(Rectangle r) { 
	cout << "Length is: " << r.length << endl;
	cout << "Width is: " << r.width << endl;
	cout << "Area is: " << r.area << endl;
}

void getItem(Item &p){ 
	p.partNumber = "A random number";
	p.description = "Some part that does something";
	p.pricing.retail = 100;
	p.pricing.wholesale = 85.95;
}

void ShowItem(Item p) { 
	cout << "PartNumber: " << p.partNumber << endl;
	cout << "Part Description: " << p.description << endl;
	cout << "Retail price " << p.pricing.retail << endl;
	cout << "Wholesale price " << p.pricing.wholesale << endl;

}

Circle getCircleData() {
	Circle temp; 
	temp.radius = 10.0;
	temp.area = PI*multiply(temp.radius,temp.radius);
	temp.diameter = temp.radius * 2;
	return temp;
}

void getCircleData(Circle *c) {
	cout << "Enter diameter: ";
	cin >> c->diameter; // using structure pointer operator since we're passing memory location captured by a pointer to structure
	c->radius = c->diameter / 2;
	c->area = PI * c->radius * c->radius;

}

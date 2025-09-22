#include<iostream>
#include<queue>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stack>
#include <iomanip> // For std::setw
#include <vector>

#define Max = 10;
using namespace std;

struct Node{
  int count; 
  int value[Max +1]
  struct Node* child[Max+1];
};

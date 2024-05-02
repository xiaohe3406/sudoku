#ifndef WORKSHOP_GLOBAL_H
#define WORKSHOP_GLOBAL_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <iterator>
#include <map>
#include <unordered_map>

using namespace std;
#define TRUE 1
#define FALSE 0
#define NoAnwser -1
#define EMPTY 0
typedef int status;

// store the literal
typedef struct DataNode {
    int data = 0;
    DataNode *next{};
}DataNode;

// store the clause
typedef struct HeadNode {
    int Num = 0;
    DataNode *right{};
    HeadNode *down{};
}HeadNode;

struct consequence {
    int value = -1;     // true - 1  false - 0
};

struct conse {
    int num = 0;
    int value = -1;     // true - 1  false - 0 
};

// a cellular of the hanidoku
typedef struct {
    int num;    
    int row;    // row
    int left_slash;     // the cellular is in the left_slash-th left slash
    int right_slash;    // the cellular is in the right_slash-th right slash
}Cellular;


void Start();



#endif //WORKSHOP_GLOBAL_H

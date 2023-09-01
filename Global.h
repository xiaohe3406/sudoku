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

using namespace std;
#define TRUE 1
#define FALSE 0
#define NoAnwser -1
#define EMPTY 0
typedef int status;

typedef struct DataNode {
    int data = 0;
    DataNode *next{};
}DataNode;

typedef struct HeadNode {
    int Num = 0;
    DataNode *right{};
    HeadNode *down{};
}HeadNode;

struct consequence {
    int value = -1;//存真值 真时为true-1，假时为false-0
};

struct conse {
    int num = 0;
    int value = -1;//存真值 真时为true-1，假时为false-0
};

typedef struct {
    int num;    // 蜂窝数字
    int row;    // 蜂窝行数
    int left_slash;     // 蜂窝在第left_slash条左斜线
    int right_slash;    // 蜂窝在第right_slash条右斜线
}Cellular;

void Start();



#endif //WORKSHOP_GLOBAL_H

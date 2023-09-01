#pragma once
#include "Global.h"
#include "DPLLSolover.h"

class Hanidoku {
public:
    Hanidoku()
    {
        InitRow();
        InitLeftSlash();
        InitRightSlash();
        Init_hanidoku(hanidoku);
    }

    bool CreateRandomHanidoku(int);
    void CreateRandomHanidoku();
    void PrintHanidoku();    
    bool SolveHanidoku();
    
private:
    // 将约束条件转化为cnf
    void ToCnf();
    // 得到初盘
    void GetBoard(string filename);

    void AddHeadcontent();
    // 提示数字约束
    void GenerateSingleClause(ofstream& ofs);
    // 格约束
    void GenerateGridClause(ofstream& ofs);
    // 线约束
    void GenerateRowClause(ofstream& ofs);
    void GenerateLeftSlashClause(ofstream& ofs);
    void GenerateRightSlashClause(ofstream& ofs);

    // 从solution.txt文件中读取结果
    bool GetResult(string filename);

    // 初始化一些数组
    void InitRow();
    void InitLeftSlash();
    void InitRightSlash();

    // 将hanidoku的元素设置正确
    void Init_hanidoku(std::vector<std::vector<Cellular>>& Hanidoku);   
    
    bool check(int value, int row, int col);
    bool IsContinuous(int row, int col, int value);
    bool dfs(bool Row[9][10], bool Left[9][10], bool Right[9][10]);


private:

    int ClauseNum;

    int holes;    // 洞的个数

    int size[9] = { 5, 6, 7, 8, 9, 8, 7, 6, 5 }; // 蜂窝每行的蜂窝数
    
    std::vector<std::vector<Cellular>> hanidoku;    //蜂窝数独盘

    std::vector<std::vector<std::pair<int, int>>> Row;// 左->右

    std::vector<std::vector<std::pair<int, int>>> LeftSlash;// 左上->右上   left_slash

    std::vector<std::vector<std::pair<int, int>>> RightSlash;// 左下->右上   right_slash 

    // 用于生成数独检查
    bool rows[9][10] = { false };
    bool left_slash[9][10] = { false };
    bool right_slash[9][10] = { false };
};
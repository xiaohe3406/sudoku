#pragma once
#include "Global.h"
#include "DPLLSolover.h"

class Hanidoku {
public:
    Hanidoku(int holes)
    {
        InitRow();
        InitLeftSlash();
        InitRightSlash();
        Init_hanidoku(hanidoku);
        Init_hanidoku(FinishedHanidoku);

        CreateRandomHanidoku(holes);
        SolveHanidoku();   // generate a completed hanidoku
    }

    // generate hanidoku
    bool CreateRandomHanidoku(int,int);
    void CreateRandomHanidoku(int );
    // choice==0 print uncompleted hanidoku ,  choice==1 print completed hanidoku 
    void PrintHanidoku(int choice);
    // interact with the user
    void Interact();
    // if num is the right answer , return 1
    // if num is the wrong answer, return 0
    // if hanidoku is completed, return -1
    int Interact(int row, int col, int num);          
    // solve hanidoku
    bool SolveHanidoku();
    
private:
    // generate cnf from hanidoku
    void ToCnf();
    // get the umcompleted hanidoku
    void GetBoard();
    // dig the holes
    void Dig(int holes);

    void AddHeadcontent();
    // 提示数字约束
    void GenerateSingleClause(ofstream& ofs);
    // 格约束
    void GenerateGridClause(ofstream& ofs);
    // 线约束
    void GenerateRowClause(ofstream& ofs);
    void GenerateLeftSlashClause(ofstream& ofs);
    void GenerateRightSlashClause(ofstream& ofs);

    // get the result from file solution.txt
    bool GetResult(string filename);

    // initialize some vector
    void InitRow();
    void InitLeftSlash();
    void InitRightSlash();
  
    // set the right element for every cellular of the hanidoku
    void Init_hanidoku(std::vector<std::vector<Cellular>>& Hanidoku);   
    
    bool check(int value, int row, int col);
    bool IsContinuous(int row, int col, int value);
    bool dfs(bool Row[9][10], bool Left[9][10], bool Right[9][10]);


private:

    // the number of clauses that generated from the hanidoku
    int ClauseNum;   
    // the number of holes in hanidoku
    int holes;    
    // size of every row 
    int size[9] = { 5, 6, 7, 8, 9, 8, 7, 6, 5 }; 
    
    // hanidoku
    std::vector<std::vector<Cellular>> hanidoku;    
    // completed hanidoku
    std::vector<std::vector<Cellular>> FinishedHanidoku;    

    std::vector<std::vector<std::pair<int, int>>> Row;// 左->右

    std::vector<std::vector<std::pair<int, int>>> LeftSlash;// 左上->右上   left_slash

    std::vector<std::vector<std::pair<int, int>>> RightSlash;// 左下->右上   right_slash 

    // 用于生成数独检查
    bool rows[9][10] = { false };
    bool left_slash[9][10] = { false };
    bool right_slash[9][10] = { false };
};
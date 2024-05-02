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
    // ��ʾ����Լ��
    void GenerateSingleClause(ofstream& ofs);
    // ��Լ��
    void GenerateGridClause(ofstream& ofs);
    // ��Լ��
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

    std::vector<std::vector<std::pair<int, int>>> Row;// ��->��

    std::vector<std::vector<std::pair<int, int>>> LeftSlash;// ����->����   left_slash

    std::vector<std::vector<std::pair<int, int>>> RightSlash;// ����->����   right_slash 

    // ���������������
    bool rows[9][10] = { false };
    bool left_slash[9][10] = { false };
    bool right_slash[9][10] = { false };
};
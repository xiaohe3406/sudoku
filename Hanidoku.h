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
    // ��Լ������ת��Ϊcnf
    void ToCnf();
    // �õ�����
    void GetBoard(string filename);

    void AddHeadcontent();
    // ��ʾ����Լ��
    void GenerateSingleClause(ofstream& ofs);
    // ��Լ��
    void GenerateGridClause(ofstream& ofs);
    // ��Լ��
    void GenerateRowClause(ofstream& ofs);
    void GenerateLeftSlashClause(ofstream& ofs);
    void GenerateRightSlashClause(ofstream& ofs);

    // ��solution.txt�ļ��ж�ȡ���
    bool GetResult(string filename);

    // ��ʼ��һЩ����
    void InitRow();
    void InitLeftSlash();
    void InitRightSlash();

    // ��hanidoku��Ԫ��������ȷ
    void Init_hanidoku(std::vector<std::vector<Cellular>>& Hanidoku);   
    
    bool check(int value, int row, int col);
    bool IsContinuous(int row, int col, int value);
    bool dfs(bool Row[9][10], bool Left[9][10], bool Right[9][10]);


private:

    int ClauseNum;

    int holes;    // ���ĸ���

    int size[9] = { 5, 6, 7, 8, 9, 8, 7, 6, 5 }; // ����ÿ�еķ�����
    
    std::vector<std::vector<Cellular>> hanidoku;    //����������

    std::vector<std::vector<std::pair<int, int>>> Row;// ��->��

    std::vector<std::vector<std::pair<int, int>>> LeftSlash;// ����->����   left_slash

    std::vector<std::vector<std::pair<int, int>>> RightSlash;// ����->����   right_slash 

    // ���������������
    bool rows[9][10] = { false };
    bool left_slash[9][10] = { false };
    bool right_slash[9][10] = { false };
};
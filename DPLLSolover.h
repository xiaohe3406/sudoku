#pragma once
#include "Global.h"

class DPLLSolover {

public:
	DPLLSolover(string filename)
	{
		LIST = CreateClause(VarNum, filename);
		result = new consequence[VarNum];
		value = DPLL(LIST, result);
	}

	void show();
	void SaveToFile(string filename);
	void ShowHanidokuResult();

private:
	bool DPLL(HeadNode* LIST, consequence* result);
	HeadNode* CreateClause(int& VARNUM, string& filename);
	HeadNode* IsSingleClause(HeadNode*);
	bool IsEmptyClause(HeadNode*);
	HeadNode* AddSingleClause(HeadNode*, int);
	HeadNode* Copy(HeadNode*);
	void DeleteHeadNode(HeadNode*, HeadNode*&);
	void DeleteDataNode(int, HeadNode*&);


private:
	int VarNum;		// 变量的个数
	bool value;		// 储存是否有answer
	HeadNode* LIST;		// 储存clause的链表
	consequence* result;	// 记录最终的真假值
};

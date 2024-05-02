#pragma once
#include "Global.h"

class DPLLSolover {

public:
	// choice == 1  choose oldDPLL
	// choice == 2	choose BetterDPLL
	DPLLSolover(string filename, int choice)
	{
		LIST = CreateClause(filename);
		this->result = new consequence[this->VarNum];
		if(choice == 1)
			value = DPLL(LIST, this->result);
		else if (choice == 2)
			value = BetterDPLL(LIST, this->result);
	}

	~DPLLSolover()
	{
		if (result != NULL)
		{
			delete[] result;
		}
	}

	// 展示结果
	void show();
	// 保存结果到文件
	void SaveToFile(string filename);
	// 
	void ShowHanidokuResult();

private:
    // 选择变元
	int chooseVarible(HeadNode* LIST);
	// DPLL
	bool DPLL(HeadNode* LIST, consequence* result);
	bool BetterDPLL(HeadNode* LIST, consequence* result);
	// 生成CNF
	HeadNode* CreateClause(string& filename);
	// 判断是否是单子句
	HeadNode* IsSingleClause(HeadNode*);
	// 判断是不是空子句
	bool IsEmptyClause(HeadNode*);
	// 添加单子句
	HeadNode* AddSingleClause(HeadNode*, int);
	// 复制
	HeadNode* Copy(HeadNode*);
	
	void DeleteHeadNode(HeadNode*&, HeadNode*&);
	void DeleteDataNode(int, HeadNode*&);


private:
	int VarNum;		// 变量的个数
	bool value;		// 储存是否有answer
	HeadNode* LIST;		// 储存clause的链表
	consequence* result;	// 记录最终的真假值
};



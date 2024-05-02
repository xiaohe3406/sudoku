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

	// չʾ���
	void show();
	// ���������ļ�
	void SaveToFile(string filename);
	// 
	void ShowHanidokuResult();

private:
    // ѡ���Ԫ
	int chooseVarible(HeadNode* LIST);
	// DPLL
	bool DPLL(HeadNode* LIST, consequence* result);
	bool BetterDPLL(HeadNode* LIST, consequence* result);
	// ����CNF
	HeadNode* CreateClause(string& filename);
	// �ж��Ƿ��ǵ��Ӿ�
	HeadNode* IsSingleClause(HeadNode*);
	// �ж��ǲ��ǿ��Ӿ�
	bool IsEmptyClause(HeadNode*);
	// ��ӵ��Ӿ�
	HeadNode* AddSingleClause(HeadNode*, int);
	// ����
	HeadNode* Copy(HeadNode*);
	
	void DeleteHeadNode(HeadNode*&, HeadNode*&);
	void DeleteDataNode(int, HeadNode*&);


private:
	int VarNum;		// �����ĸ���
	bool value;		// �����Ƿ���answer
	HeadNode* LIST;		// ����clause������
	consequence* result;	// ��¼���յ����ֵ
};



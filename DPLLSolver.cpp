#include "Global.h"
#include "DPLLSolover.h"

bool DPLLSolover::IsEmptyClause(HeadNode* LIST)
{
    HeadNode* PHead = LIST;
    while (PHead != nullptr) 
    {
        if(PHead->Num == 0)
            return true;
        PHead = PHead->down;
    }
    return false;
}

HeadNode* DPLLSolover::IsSingleClause(HeadNode* Pfind)
{
    while (Pfind != nullptr ) 
    {
        if(Pfind->Num == 1)
            return Pfind;
        Pfind = Pfind->down;
    }
    return nullptr;
}

HeadNode* DPLLSolover::Copy(HeadNode* LIST)
{ 
    // 此处检验传参正常，开始检查复制有无逻辑错误
    HeadNode* SrcHead = LIST;
    HeadNode* ReHead = new HeadNode;    // 新链表的头节点
    ReHead->Num = SrcHead->Num;     // 复制第一个头节点
    HeadNode* Phead = ReHead;       // Phead创建头节点
    DataNode* ReData = new DataNode;    // 新链表的数据节点
    DataNode* FirstSrcData = SrcHead->right;    // 用于创建第一行的第一个数据节点
    ReData->data = FirstSrcData->data;  // 新链表的第一个数据节点的数值
    Phead->right = ReData;

    for (FirstSrcData = FirstSrcData->next; FirstSrcData != nullptr; FirstSrcData = FirstSrcData->next)
    {
        // 第一行链表复制
        DataNode* NewDataNode = new DataNode;
        NewDataNode->data = FirstSrcData->data;
        ReData->next = NewDataNode;
        ReData = ReData->next;
    }

    // 此下行数节点的复制 >=2th
    for(SrcHead = SrcHead->down; SrcHead != nullptr ; SrcHead = SrcHead->down)
    {
        HeadNode* NewHead = new HeadNode;
        DataNode* NewData = new DataNode;

        NewHead->Num = SrcHead->Num;

        Phead->down = NewHead;
        Phead = Phead->down;

        DataNode* SrcData = SrcHead->right;
        NewData->data = SrcData->data;
        Phead->right = NewData;     // 第一个数据节点
        for (SrcData = SrcData->next;SrcData != nullptr; SrcData = SrcData->next) 
        {
            // 此行剩下的数据节点
            DataNode* node = new DataNode;
            node->data = SrcData->data;
            NewData->next = node;
            NewData = NewData->next;
        }
        NewData->next = nullptr;
    }
    Phead->down = nullptr;

    return ReHead;
}

HeadNode* DPLLSolover::AddSingleClause(HeadNode* LIST,int Var)
{ 
    // 所加的单子句位于链表的头
    HeadNode* AddHead = new HeadNode;
    DataNode* AddData = new DataNode;

    AddData->data = Var;
    AddData->next = nullptr;

    AddHead->right = AddData;
    AddHead->Num = 1;
    AddHead->down = LIST;
    LIST = AddHead;

    return LIST;
}

void DPLLSolover::DeleteDataNode(int temp, HeadNode* &LIST)
{
    HeadNode* pHeadNode = LIST;
    while (pHeadNode != nullptr)
    {
        int flag1 = 0;
        DataNode* rear = pHeadNode->right;
        while (rear != nullptr)
        {
            int flag2 = 0;
            if (rear->data == temp)     // 相等删除整行
            {
                DeleteHeadNode(pHeadNode, LIST);
                flag1 = 1;
                break;
            }
            else if (rear->data == -temp)      // 互为相反数则删除单个Data
            {
                if (rear == pHeadNode->right)
                {
                    //cout << "delete " << rear->data << endl;
                    DataNode* DeleteData = rear;
                    rear = rear->next;
                    flag2 = 1;
                    pHeadNode->right = DeleteData->next;
                    pHeadNode->Num--;
                    free(DeleteData);
                }
                else
                {
                    for (DataNode* front = pHeadNode->right; front != nullptr; front = front->next)
                        if (front->next == rear)
                        {
                            DataNode* DeleteData = rear;
                            front->next = rear->next;
                            rear = rear->next;
                            flag2 = 1;
                            pHeadNode->Num--;
                            free(DeleteData);
                            break;
                        }
                }
            }
            if(flag2 != 1)
               rear = rear->next;
        }
        if(flag1 != 1)
           pHeadNode = pHeadNode->down;
    }

    //for (HeadNode* pHeadNode = LIST; pHeadNode != nullptr ; pHeadNode = pHeadNode->down)
    //    for (DataNode* rear = pHeadNode->right; rear != nullptr ; rear = rear->next) 
    //    {
    //        if (rear->data == temp)  // 相等删除整行
    //        {
    //            DeleteHeadNode(pHeadNode, LIST);
    //            break;
    //        }
    //        else if (rear->data == -temp)  // 互为相反数则删除单个Data
    //        { 
    //            if(rear == pHeadNode->right) 
    //            {
    //                // 头节点删除
    //                //DataNode* DeleteData = rear;
    //                pHeadNode->right = rear->next;
    //                pHeadNode->Num--;
    //                //free(DeleteData);
    //            }
    //            else
    //            { 
    //                // 删除普通节点
    //                for (DataNode* front = pHeadNode->right; front != nullptr; front= front->next)
    //                    if(front->next == rear)
    //                    {
    //                        //DataNode* DeleteData = rear;
    //                        front->next = rear->next;
    //                        pHeadNode->Num--;
    //                        //free(DeleteData);
    //                    }
    //            }
    //        }
    //    }
}

void DPLLSolover::DeleteHeadNode(HeadNode *&Clause,HeadNode* &LIST)
{
    if (!Clause) return;
    if (Clause == LIST)
    {    
        LIST = Clause->down;
    }
    else 
    {
        for (HeadNode* front = LIST; front != nullptr; front = front->down)
            if (front->down == Clause)
            {
                front->down = Clause->down;
            }
    }

    HeadNode* tempHeadNode = Clause;
    Clause = Clause->down;

    // free链表Clause内存
    DataNode* temp = tempHeadNode->right;
    while (temp)
    {
        DataNode* temp1 = temp;
        temp = temp->next;
        free(temp1);
    }
    free(tempHeadNode);
}

void DPLLSolover::show() 
{
    if (value == false)
    {
        cout << "S " << NoAnwser << endl;
        cout << "V ";
        cout << endl;
        return;
    }

    // value == true
    cout << "S " << true << endl;
    cout << "V ";
    for(int i = 0; i < VarNum; i++) 
    {
        if (result[i].value == TRUE)
            cout << i + 1 << " ";
        else if(result[i].value == FALSE)
            cout << -( i + 1 ) << " ";
        else
            cout << ( i + 1 ) << " ";    //剩下的可true可false，直接输出false
    }
    cout << endl;
}

void DPLLSolover::SaveToFile(string filename)
{
    ofstream ofs(filename);
    if (!ofs.is_open())
    {
        cout << "Fail to open file " << filename << "." << endl;
        return;
    }

    if (value == false)
    {
        ofs << "0 " << endl;
        return;
    }

    // value == true
    ofs << 1 << endl;
    for (int i = 0; i < VarNum; i++)
    {
        if (result[i].value == TRUE)
            ofs << i + 1 << " ";
        /* else if (result[i].value == FALSE)
             cout << -(i + 1) << " ";*/
             /*else
                 cout << (i + 1) << " ";    *///剩下的可true可false，直接输出false
    }
    ofs << endl;

    ofs.close();
}

void DPLLSolover::ShowHanidokuResult()
{
    if (value == false)
    {
        cout << "S " << NoAnwser << endl;
        cout << "V ";
        cout << endl;
        return;
    }

    // value == true
    cout << "S " << true << endl;
    cout << "V ";
    for (int i = 0; i < VarNum; i++)
    {
        if (result[i].value == TRUE)
            cout << i + 1 << " ";
       /* else if (result[i].value == FALSE)
            cout << -(i + 1) << " ";*/
        /*else
            cout << (i + 1) << " ";    *///剩下的可true可false，直接输出false
    }
    cout << endl;
}

int DPLLSolover::chooseVarible(HeadNode* LIST)
{
    int min = INT16_MAX;
    // MOM  最短子句的出现次数最多的文字
    for (HeadNode* pHead = LIST; pHead != nullptr; pHead = pHead->down)
    {
        if (pHead->Num < min)
        {
            min = pHead->Num;
        }
    }

    std::unordered_map<int, int> count;
    for (HeadNode* pHead = LIST; pHead != nullptr; pHead = pHead->down)
    {
        // 最短子句
        if (pHead->Num == min)
        {
            for (DataNode* rear = pHead->right; rear != nullptr; rear = rear->next)
            {
                count[rear->data]++;
            }
            break;
        }
    }

    int maxCount = 0;
    int selectValue = 0;
    for (const auto& entry : count)
    {
        if (entry.second > maxCount) 
        {
            maxCount = entry.second;
            selectValue = entry.first;
        }
    }
    return selectValue;
}

bool DPLLSolover::DPLL(HeadNode *LIST,consequence *result)
{
    //单子句规则
    HeadNode* Pfind = LIST;
    HeadNode* SingleClause = IsSingleClause(Pfind);
    while (SingleClause != nullptr) // 找到单子句
    {
        SingleClause->right->data > 0 ? result[abs(SingleClause->right->data)-1].value = TRUE : result[abs(SingleClause->right->data)-1].value = FALSE;

        int temp = SingleClause->right->data;
        
        DeleteHeadNode(SingleClause, LIST);      // 删除单子句这一行
        DeleteDataNode(temp, LIST);      // 删除相等或相反数的节点
        
        if(!LIST) return true;
        else if(IsEmptyClause(LIST)) return false;
        
        Pfind = LIST;
        SingleClause = IsSingleClause(Pfind);   // 回到头节点继续进行检测是否有单子句
    }

    //cout << "DPLL work" << endl;
    
    // 分裂策略
    // int Var = chooseVarible(LIST);    // 选取变元
    int Var = LIST->right->data;
    HeadNode* replica = Copy(LIST);     // 存放LIST的副本replica
    HeadNode* temp1 = AddSingleClause(LIST, Var);    // 装载变元成为单子句
    if(DPLL(temp1, result)) return TRUE;
    else 
    {
        HeadNode *temp2 = AddSingleClause(replica, -Var);
        return DPLL(temp2, result);
    }
}

bool DPLLSolover::BetterDPLL(HeadNode* LIST, consequence* result)
{
    //单子句规则
    HeadNode* Pfind = LIST;
    HeadNode* SingleClause = IsSingleClause(Pfind);
    while (SingleClause != nullptr) // 找到单子句
    {
        SingleClause->right->data > 0 ? result[abs(SingleClause->right->data) - 1].value = TRUE : result[abs(SingleClause->right->data) - 1].value = FALSE;

        int temp = SingleClause->right->data;

        //cout << "deal with " << temp << endl;
        DeleteHeadNode(SingleClause, LIST);      // 删除单子句这一行
        DeleteDataNode(temp, LIST);      // 删除相等或相反数的节点

        if (!LIST) return true;
        else if (IsEmptyClause(LIST)) return false;

        Pfind = LIST;
        SingleClause = IsSingleClause(Pfind);   // 回到头节点继续进行检测是否有单子句
    }


    // 分裂策略
    int Var = chooseVarible(LIST);    // 选取变元
    // int Var = LIST->right->data;
    HeadNode* replica = Copy(LIST);     // 存放LIST的副本replica
    HeadNode* temp1 = AddSingleClause(LIST, Var);    // 装载变元成为单子句
    if (BetterDPLL(temp1, result)) return TRUE;
    else
    {
        HeadNode* temp2 = AddSingleClause(replica, -Var);
        return BetterDPLL(temp2, result);
    }
}
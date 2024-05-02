#include "Global.h"
#include "DPLLSolover.h"


HeadNode* DPLLSolover::CreateClause(string &filename)
{
    //FileOpen
    string path = filename;
    ifstream ifs;
    ifs.open(path, ios::in);
    if(!ifs)
    {
        cout<<"File can not open.";
        return nullptr;
    }

    char ch;
    char buf[100];
    ifs >> ch;
    while (ch != 'p')
    {
        ifs.getline(buf, 200);
        ifs >> ch;
    }
    string cnf;
    int VarNum, ClauseNum;
    ifs >> cnf >> VarNum >> ClauseNum;
    ifs.get();

    this->VarNum = VarNum;


    // write into 2 dimensional link lists
    // loading the initial node
    HeadNode* HEAD = new HeadNode;
    HeadNode* headRear = HEAD;
    HeadNode* END = new HeadNode;
    for (int i = 0 ; i < ClauseNum ; i++) 
    {
        // load on the data lists
        int temp;
        ifs >> temp;
        // load the first data node
        DataNode* cur = new DataNode;
        cur->data = temp;
        headRear->right = cur;
        headRear->Num++;
        //the >2th data loading
        ifs >> temp;
        while (temp != 0) 
        {
            DataNode* rear = new DataNode;
            cur->next = rear;
            rear->data = temp;
            cur = cur->next;
            headRear->Num++;
            ifs >> temp;
        }
        cur->next = nullptr;
        ifs.get();      //换行符
        HeadNode* tp = new HeadNode;
        headRear->down = tp;
        END = headRear;
        headRear = headRear->down;
    }
    END->down = nullptr;

    //output link lists
    /*HeadNode* Phead = HEAD;
    DataNode* front;
    cout << "CnfParser" << endl;
    while(Phead != nullptr)
    {
        front = Phead->right;
        while(front != nullptr)
        {
            cout<< front->data << " ";
            front = front->next;
        }
        cout << 0 << endl;
        Phead = Phead->down;
    }*/

    ifs.close();
    return HEAD;
}
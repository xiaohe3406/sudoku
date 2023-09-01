#include <iostream>
#include "Global.h"
#include "DPLLSolover.h"
#include "Hanidoku.h"


//int main()
//{
//	Hanidoku test;
//	cout << "开始 " << endl;
//	system("pause");
//	test.GenerateClause();
//	cout << "finish "  << endl;
//	
//	
//	return 0;
//}


int main(int argc, char* argv[]) {
    
    int choice = 0;
    
    while (true)
    {
        Start();
        cin >> choice;
        if (choice == 1) 
        {
            clock_t starttime, endtime;
            starttime = clock();
            Hanidoku hanidoku;
            hanidoku.CreateRandomHanidoku();
            hanidoku.PrintHanidoku();
            hanidoku.SolveHanidoku();
            hanidoku.PrintHanidoku();
            endtime = clock();
            cout << "t " << (double)(endtime - starttime) / CLOCKS_PER_SEC * 1000.0 << " ms" << endl;

        }
        else if (choice == 2)       //sat
        {   
            clock_t starttime, endtime;

            string filename;
            cout << "input the filename" << endl;
            cin >> filename;

            starttime = clock();

            DPLLSolover solover(filename);

            endtime = clock();

            solover.show();

            //测试
            //cout<<"result: \n";
            //starttime = clock();
            //int value = dpll(list,result);
            //endtime = clock();
            //if(value) {
            //    cout << "s " << true << endl;
            //    show(result, varnum);//输出解
            //}
            //else {
            //    cout << "s " << noanwser << endl;
            //    cout<<"v "<<endl;
            //}
            //cout<<"t "<<(double)(endtime-starttime)/clocks_per_sec*1000.0<<" ms\n";

             //写到文件
            /*string suffix = ".txt";
            string name = "solution";
            string outputfile = name + suffix;
            ofstream fos;
            fos.open(outputfile, ios::out);
            if (!fos.is_open()) 
            {
                cout << "can not open a new file.\n";
                exit(1);
            }*/

            // 时间
            cout << "t " << (double)(endtime - starttime) / CLOCKS_PER_SEC * 1000.0 << " ms" << endl;
            // fos.close();
        }
        else if (choice == 0) // quit
        {
            break;
        }
        else 
        { 
            cout << "please input the right num! " << endl;
        }

        system("pause");
        system("cls");
    }
    return 0;
}
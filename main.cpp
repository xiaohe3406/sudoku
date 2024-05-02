#include <iostream>
#include "Global.h"
#include "DPLLSolover.h"
#include "Hanidoku.h"
#include "cnfParser.h"
#include "DPLL_CDCL.h"
#include "common.h"


int main(int argc, char* argv[]) 
{
	int choice = 0;

	while (true)
	{
		Start();
		cin >> choice;
		if (choice == 1)
		{
			int i = 0;
			clock_t starttime, endtime;
			starttime = clock();
			cout << "Please input the number of holes" << endl;
			int holes;
			cin >> holes;
			Hanidoku hanidoku(holes);
			hanidoku.PrintHanidoku(0);
			cout << "Please input your choice." << endl;
			cout << " 1) Interact     2) Get the result    0) quit" << endl;
			cin >> i;
			if (i == 1)
			{
				hanidoku.Interact();
			}

			if (i == 2)
			{
				hanidoku.PrintHanidoku(1);
			}

			if (i == 0)
			{
				continue;
			}
				
			endtime = clock();
			//cout << "t " << (double)(endtime - starttime) / CLOCKS_PER_SEC * 1000.0 << " ms" << endl;

		}
		else if (choice == 2)       //sat
		{
			clock_t starttime, endtime;

			cout << "1) DPLL		2) DPLL_CDCL" << endl;
			cout << "Input your choice" << endl;
 			int k;
			cin >> k;

			string filename;
			cout << "input the filename" << endl;
			cin >> filename;

			string path = filename;
			ifstream ifs;
			ifs.open(path, ios::in);
			if (!ifs)
			{
				cout << "File can not open." << endl << endl;
				continue;
			}
			ifs.close();

			starttime = clock();

			if (k == 2)
			{
				formula phi = cnfParser::parse(filename);
				DPLL_CDCL solver(phi);
				bool sat = solver.check_sat();
				endtime = clock();
				solver.ShowResult(sat);
			}
			if (k == 1)
			{
				DPLLSolover solver(filename, 2);
				endtime = clock();
				solver.show();
			}

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
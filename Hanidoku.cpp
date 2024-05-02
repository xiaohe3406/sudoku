#include "Global.h"
#include "Hanidoku.h"

bool Hanidoku::CreateRandomHanidoku(int occupy, int occupy2)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			rows[i][j] = false;
			left_slash[i][j] = false;
			right_slash[i][j] = false;
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < size[i]; j++)
		{
			hanidoku[i][j].num = 0;
		}
	}
	
	int i, j, value;

	std::default_random_engine e;
	e.seed(time(0));

	int count = 61;
	while (count > 0)
	{
		std::uniform_int_distribution<int> u(0, 8);
		i = u(e);

		std::uniform_int_distribution<int> v(0, size[i]-1);		
		j = v(e);

		std::uniform_int_distribution<int> t(1, 9);

		
		if (hanidoku[i][j].num == 0)		// 没填
		{
			value = t(e);
			if (check(value, i+1, j+1))			// 检查是否合法
			{
				hanidoku[i][j].num = value;
				rows[i][value] = true;
				left_slash[hanidoku[i][j].left_slash][value] = true;
				right_slash[hanidoku[i][j].right_slash][value] = true;
				count--;
			}
		}

	}
	Dig(30);  // 挖洞
	return true;
}

// 用一行中最大和最小数的差来判断
// row col 从1开始
bool Hanidoku::IsContinuous(int row, int col, int value)
{
	int min = INT16_MAX, max = 0;
	// 行
	for (int i = 0; i < size[row - 1]; i++)
	{
		if (hanidoku[row-1][i].num != 0) // 已经填了
		{
			if (hanidoku[row-1][i].num < min)
			{
				min = hanidoku[row-1][i].num;
			}
			if (hanidoku[row-1][i].num > max)
			{
				max = hanidoku[row-1][i].num;
			}
		}
	}
	if (value <= min)	min = value;
	if (value >= max)	max = value;
	if ((max - min) >= size[row - 1])	return false;
	// 左斜线
	min = INT16_MAX, max = 0;
	int num = hanidoku[row - 1][col - 1].left_slash;
	for (int i = 0; i < size[num]; i++)
	{
		int tempRow = LeftSlash[num][i].first;
		int tempCol = LeftSlash[num][i].second;
		if (hanidoku[tempRow - 1][tempCol - 1].num != 0) // 已经填了
		{
			if (hanidoku[tempRow - 1][tempCol - 1].num < min)
			{
				min = hanidoku[tempRow - 1][tempCol - 1].num;
			}
			if (hanidoku[tempRow - 1][tempCol - 1].num > max)
			{
				max = hanidoku[tempRow - 1][tempCol - 1].num;
			}
		}
	}
	if (value <= min)	min = value;
	if (value >= max)	max = value;
	if (max - min >= size[num])	return false;
	// 右斜线
	min = INT16_MAX, max = 0;
	num = hanidoku[row - 1][col - 1].right_slash;
	for (int i = 0; i < size[num]; i++)
	{
		int tempRow = RightSlash[num][i].first;
		int tempCol = RightSlash[num][i].second;
		if (hanidoku[tempRow - 1][tempCol - 1].num != 0) // 已经填了
		{
			if (hanidoku[tempRow - 1][tempCol - 1].num < min)
			{
				min = hanidoku[tempRow - 1][tempCol - 1].num;
			}
			if (hanidoku[tempRow - 1][tempCol - 1].num > max)
			{
				max = hanidoku[tempRow - 1][tempCol - 1].num;
			}
		}
	}
	if (value <= min)	min = value;
	if (value >= max)	max = value;
	if (max - min >= size[num])	return false;

	return true;
}

bool Hanidoku::dfs(bool Row[9][10], bool Left[9][10], bool Right[9][10])
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < size[i]; j++)
		{
			if (hanidoku[i][j].num == 0)
			{
				for (int n = 1; n < 10; n++)
				{
					if (!Row[i][n] && !Left[hanidoku[i][j].left_slash][n] && !Right[hanidoku[i][j].right_slash][n])
					{
						// 尝试填入
						hanidoku[i][j].num = n;
						Row[i][n] = true;
						Left[hanidoku[i][j].left_slash][n] = true;
						Right[hanidoku[i][j].right_slash][n] = true;
						// 检查连续
						if (IsContinuous(i + 1, j + 1, n))
						{
							if (dfs(Row, Left, Right))
							{
								return true;
							}
						}
						Row[i][n] = false;
						Left[hanidoku[i][j].left_slash][n] = false;
						Right[hanidoku[i][j].right_slash][n] = false;
						hanidoku[i][j].num = 0;
					}
				}
				return false;
			}
		}

	return true;
}

bool Hanidoku::check(int value, int row, int col)
{
	// 先检查是否有相同的数字
	if (rows[row-1][value] == true || left_slash[hanidoku[row-1][col-1].left_slash][value] == true || right_slash[hanidoku[row-1][col-1].right_slash][value] == true)
	{
		return false;
	}

	// 再检查数字是否连续   
	// 行 左斜线 右斜线
	if (!IsContinuous(row, col, value))
	{
		return false;
	}
	return true;
}



void Hanidoku::CreateRandomHanidoku(int hole)
{
	this->holes = hole;
	GetBoard();
	Dig(hole);
}

void Hanidoku::PrintHanidoku(int choice)
{
	std::cout << "--------------------------------------" << endl;
	
	for (int i = 0; i < 5; i++)
	{
		// 输出上半部分格子
		// 输出空格 8 6 4 2 0
		for (int count = 0; count < 8 - 2 * i; count++)
			cout << " ";

		//  5 6 7 8 9
		for (int count = 0; count < 5 + i; count++)
			cout << " / \\";
		cout << endl;

		// 输出中间部分
		// 输出空格 8 6 4 2 0
		for (int count = 0; count < 8 - 2 * i; count++)
			cout << " ";
		cout << "|";
		for (int j = 0; j < size[i]; j++)
		{
			if (choice == 1)
			{
				if (FinishedHanidoku[i][j].num == 0)
					cout << " . |";
				else
					cout << " " << FinishedHanidoku[i][j].num << " |";
			}
			else
			{
				if (hanidoku[i][j].num == 0)
					cout << " . |";
				else
					cout << " " << hanidoku[i][j].num << " |";
			}
		}
		cout << endl;

	}
	cout << " \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ /" << endl;
	for (int i = 5; i < 9; i++)
	{
		// 输出中间部分
		// 输出空格 2 4 6 8
		for (int count = 0; count < 2 * (i - 4); count++)
			cout << " ";
		cout << "|";
		// 输出数字
		for (int j = 0; j < size[i]; j++)
		{
			if (choice == 1)
			{
				if (FinishedHanidoku[i][j].num == 0)
					cout << " . |";
				else
					cout << " " << FinishedHanidoku[i][j].num << " |";
			}
			else
			{
				if (hanidoku[i][j].num == 0)
					cout << " . |";
				else
					cout << " " << hanidoku[i][j].num << " |";
			}
		}
		cout << endl;

		// 输出下半部分
		// 输出空格 3 5 7 9
		for (int count = 0; count < 3 + 2 * (i - 5); count++)
			cout << " ";
		// 8 7 6 5
		for (int count = 0; count < 13 - i; count++)
			cout << "\\ / ";
		cout << endl;
	}

	std::cout << "--------------------------------------" << endl;
	std::cout << std::endl;


}

void Hanidoku::Interact()
{
	cout << "Input the index and the num like (row, col, num).  If you want to quit, input 0 0 0.  " ;
	cout << "If you want to get the result, input 9 9 9." << endl;
	int row, col, num;
	cin >> row >> col >> num;
	if (row == 0 && col == 0 && num == 0)
	{
		return ;
	}
	if (row == 9 && col == 9 && num == 9)
	{
		PrintHanidoku(1);
		return;
	}
	while (true)
	{
		int flag = Interact(row, col, num);
		if (flag == 1)
		{
			PrintHanidoku(0);
			cout << "Input the index and the num like (row, col, num).  If you want to quit, input 0 0 0.  ";
			cout << "If you want to get the result, input 9 9 9." << endl;
			cin >> row >> col >> num;
			if (row == 0 && col == 0 && num == 0)
			{
				return ;
			}
			if (row == 9 && col == 9 && num == 9)
			{
				PrintHanidoku(1);
				return;
			}
		}
		else if(flag == 0)
		{
			cout << "Input the index and the num like (row, col, num).  If you want to quit, input 0 0 0.  ";
			cout << "If you want to get the result, input 9 9 9." << endl;
			cin >> row >> col >> num;
			if (row == 0 && col == 0 && num == 0)
			{
				return ;
			}
			if (row == 9 && col == 9 && num == 9)
			{
				PrintHanidoku(1);
				return;
			}
		}
		else if(flag == -1)
		{
			PrintHanidoku(1);
			cout << "You have finished it." << endl;
			break;
		}
	}
	return ;
}

int Hanidoku::Interact(int row, int col, int num)
{
	// 处理错误行列输入
	if (row < 1 || row > 9)
	{
		cout << "Input the right num." << endl;
		return 0;
	}
	else if (col < 1 || col > size[row - 1])
	{
		cout << "Input the right col." << endl;
		return 0;
	}
	if (hanidoku[row - 1][col - 1].num != 0)
	{
		// 已经填了
		cout << "This one has been completed." << endl;
		return 0;
	}

	if (FinishedHanidoku[row - 1][col - 1].num != num)
	{
		cout << "The number is wrong." << endl;
		return 0;
	}
	else
	{
		cout << "The number is right." << endl;
		hanidoku[row - 1][col - 1].num = num;
		this->holes--;
		if (this->holes == 0)
		{
			return -1;
		}
		return 1;
	}

	

	return 0;
}

void Hanidoku::ToCnf()
{
	ClauseNum = 0;
	string Outputfile = "sudoku.cnf";
	ofstream ofs;
	ofs.open(Outputfile, ios::out | ios::in);
	if (!ofs.is_open())
	{
		cout << "Fail to open file" << Outputfile <<  endl;
		return;
	}

	GenerateGridClause(ofs);
	GenerateSingleClause(ofs);
	GenerateRowClause(ofs);
	GenerateLeftSlashClause(ofs);
	GenerateRightSlashClause(ofs);

	ofs.close();

	AddHeadcontent();

}

void Hanidoku::GetBoard()
{
	std::default_random_engine e;
	e.seed(time(0));
	std::uniform_int_distribution<int> u(1, 18);
	
	string filename = "Hanidoku\\Hanidoku" + to_string(u(e)) + ".txt";

	ifstream ifs(filename);
	if (!ifs.is_open())
	{
		cout << "fail to open file " << filename << endl;
	}

	int temp;
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < size[row]; col++)
		{
			ifs >> temp;
			hanidoku[row][col].num = temp;
			FinishedHanidoku[row][col].num = temp;
		}
	}
}

void Hanidoku::Dig(int holes)
{
	std::default_random_engine e;
	e.seed(time(0));

	int i, j;

	while (holes)
	{
		std::uniform_int_distribution<int> u(0, 8);
		i = u(e);
		std::uniform_int_distribution<int> v(0, size[i] - 1);
		j = v(e);

		if (this->hanidoku[i][j].num != 0)
		{
			hanidoku[i][j].num = 0;
			FinishedHanidoku[i][j].num = 0;
			holes--;
		}
	}

}

bool Hanidoku::GetResult(string filename)
{
	ifstream ifs(filename);
	if (!ifs.is_open())
	{
		cout << "Fail to open file " << filename << endl;
		return false;
	}

	int IsComplete;
	ifs >> IsComplete;

	if (IsComplete == 0)
	{
		cout << "No Answer" << endl;
		return false;
	}

	// IsComplete == 1
	int tempNum = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < size[i]; j++)
		{
			ifs >> tempNum;
			tempNum = tempNum % 10;
			FinishedHanidoku[i][j].num = tempNum;
		}
	}

	ifs.close();
	return true;
}

bool Hanidoku::SolveHanidoku()
{
	ToCnf();
	DPLLSolover solver("sudoku.cnf", 2);
	string filename = "solution.txt";
	solver.SaveToFile(filename);
	bool i = GetResult(filename);
	if (i) return true;
	else return false;
}



void Hanidoku::AddHeadcontent()
{
	string Outputfile = "sudoku.cnf";
	ifstream ifs;
	ifs.open(Outputfile, ios::in);
	if (!ifs.is_open())
	{
		cout << "Fail to open file" << Outputfile <<  endl;
		return;
	}

	std::istreambuf_iterator<char> begin(ifs);
	std::istreambuf_iterator<char> end;
	std::string originalContent(begin, end);

	ifs.close();

	ofstream ofs;
	ofs.open(Outputfile, ios::out);
	if (!ofs.is_open())
	{
		cout << "fail to open file" << endl;
		return;
	}

	ofs << "p cnf 960 " << to_string(ClauseNum) << endl;
	ofs << originalContent;

	ofs.close();
}

void Hanidoku::GenerateSingleClause(ofstream& ofs)
{
	
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < size[i]; j++)
		{
			if (hanidoku[i][j].num != 0)
			{
				ofs << (i+1) * 100 + (j+1) * 10 + hanidoku[i][j].num << " 0" << endl;
				ClauseNum++;
			}
		}
	}
}

void Hanidoku::GenerateGridClause(ofstream& ofs)
{
	// 填入至少一个数字
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < size[i]; j++)
		{
			for (int num = 1; num <= 9; num++)
			{
				ofs << (i + 1) * 100 + (j + 1) * 10 + num << " ";
			}
			ofs << 0 << endl;
			ClauseNum++;
		}
	}

	// 不能同时填入两个数字
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < size[i]; j++)
		{
			for (int first = 1; first < 9; first++)
			{
				for (int second = first + 1; second <= 9; second++)
				{
					ofs << -((i + 1) * 100 + (j + 1) * 10 + first) << " ";
					ofs << -((i + 1) * 100 + (j + 1) * 10 + second) << " ";
					ofs << 0 << endl;
					ClauseNum++;
				}
			}
		}
	}
}

void Hanidoku::GenerateRowClause(ofstream& ofs)
{
	for (int i = 0; i < 9; i++)
	{
		// 5蜂窝
		if (i == 0 || i == 8)
		{
			// 必选元素5
			for (int k = 1; k <= size[i]; k++)
			{
				ofs << (i+1) * 100 + k * 10 + 5 << " ";
			}
			ofs << 0 << endl;
			ClauseNum++;

			// 1,6  2,6  2,7  3,6  3,7  3,8  4,6  4,7  4,8  4,9
			for (int first = 1; first <= 4; first++)
			{
				for (int second = 6, count = 0; count < first; count++, second++)
				{
					for (int k = 1; k <= 2 * size[i]; k++)
					{
						if (k <= size[i])
						{
							ofs << (i + 1) * 100 + k * 10 + first << " ";
						}
						if (k > size[i] && k <= size[i] * 2)
						{
							ofs << (i + 1) * 100 + (k - size[i]) * 10 + second << " ";
						}
					}
					ofs << 0 << endl;
					ClauseNum++;
				}
			}
		}

		// 6
		if (i == 1 || i == 7)
		{
			// 必选456
			for (int num = 4; num <= 6; num++)
			{
				for (int k = 1; k <= size[i]; k++)
				{
					ofs << (i + 1) * 100 + k * 10 + num << " ";
				}
				ofs << 0 << endl;
				ClauseNum++;
			}
			
			//1,7  2,7  2,8  3,7  3,8  3,9
			for (int first = 1; first <= 3; first++)
			{
				for (int second = 7, count = 0; count < first; count++, second++)
				{
					for (int k = 1; k <= 2 * size[i]; k++)
					{
						if (k <= size[i])
						{
							ofs << (i + 1) * 100 + k * 10 + first << " ";
						}
						if (k > size[i] && k <= size[i] * 2)
						{
							ofs << (i + 1) * 100 + (k - size[i]) * 10 + second << " ";
						}
					}
					ofs << 0 << endl;
					ClauseNum++;
				}
			}
		}

		// 7
		if (i == 2 || i == 6)
		{
			// 必选34567
			for (int num = 3; num <= 7; num++)
			{
				for (int k = 1; k <= size[i]; k++)
				{
					ofs << (i + 1) * 100 + k * 10 + num << " ";
				}
				ofs << 0 << endl;
				ClauseNum++;
			}

			// 1,8  2,8  2,9
			for (int first = 1; first <= 2; first++)
			{
				for (int second = 8,  count = 0; count < first; count++, second++)
				{
					for (int k = 1; k <= 2 * size[i]; k++)
					{
						if (k <= size[i])
						{
							ofs << (i + 1) * 100 + k * 10 + first << " ";
						}
						if (k > size[i] && k <= size[i] * 2)
						{
							ofs << (i + 1) * 100 + (k - size[i]) * 10 + second << " ";
						}
					}
					ofs << 0 << endl;
					ClauseNum++;
				}
			}
		}

		// 8
		if (i == 3 || i == 5)
		{
			// 必选2345678
			for (int num = 2; num <= 8; num++)
			{
				for (int k = 1; k <= size[i]; k++)
				{
					ofs << (i + 1) * 100 + k * 10 + num << " ";
				}
				ofs << 0 << endl;
				ClauseNum++;
			}

			// 1,9
			for (int k = 1; k <= 2 * size[i]; k++)
			{
				if (k <= size[i])
				{
					ofs << (i + 1) * 100 + k * 10 + 1 << " ";
				}
				if (k > size[i] && k <= size[i] * 2)
				{
					ofs << (i + 1) * 100 + (k - size[i]) * 10 + 9 << " ";
				}
			}
			ofs << 0 << endl;
			ClauseNum++;
		}

		// 9
		if (i == 4)
		{
			// 必选12345678
			for (int num = 1; num <= 9; num++)
			{
				for (int k = 1; k <= size[i]; k++)
				{
					ofs << (i + 1) * 100 + k * 10 + num << " ";
				}
				ofs << 0 << endl;
				ClauseNum++;
			}
		}
	}


	for (int i = 1; i <= 9; i++)
	{
		for (int first = 1; first <= size[i - 1]; first++)
		{
			for (int second = first + 1; second <= size[i - 1]; second++)
			{
				for (int n = 1; n <= 9; n++)
				{
					ofs << -(i * 100 + first * 10 + n) << " ";
					ofs << -(i * 100 + second * 10 + n) << " ";
					ofs << 0 << endl;
					ClauseNum++;
				}
			}
		}
	}
}

void Hanidoku::GenerateLeftSlashClause(ofstream& ofs)
{
	for (int i = 0; i < 9; i++)
	{
		// 5蜂窝
		if (i == 0 || i == 8)
		{
			// 必选元素5
			for (int k = 0; k < size[i]; k++)
			{
				ofs << LeftSlash[i][k].first * 100 + LeftSlash[i][k].second * 10 + 5 << " ";
			}
			ofs << 0 << endl;
			ClauseNum++;

			// 1,6  2,6  2,7  3,6  3,7  3,8  4,6  4,7  4,8  4,9
			for (int first = 1; first <= 4; first++)
			{
				for (int second = 6, count = 0; count < first; count++, second++)
				{
					for (int k = 0; k < 2 * size[i]; k++)
					{
						if (k < size[i])
						{
							ofs << LeftSlash[i][k].first * 100 + LeftSlash[i][k].second * 10 + first << " ";
						}
						if (k >= size[i] && k < size[i] * 2)
						{
							ofs << LeftSlash[i][k - size[i]].first * 100 + LeftSlash[i][k - size[i]].second * 10 + second << " ";
						}
					}
					ofs << 0 << endl;
					ClauseNum++;
				}
			}
		}

		// 6
		if (i == 1 || i == 7)
		{
			// 必选456
			for (int num = 4; num <= 6; num++)
			{
				for (int k = 0; k < size[i]; k++)
				{
					ofs << LeftSlash[i][k].first * 100 + LeftSlash[i][k].second * 10 + num << " ";
				}
				ofs << 0 << endl;
				ClauseNum++;
			}
			
			//1,7  2,7  2,8  3,7  3,8  3,9
			for (int first = 1; first <= 3; first++)
			{
				for (int second = 7, count = 0; count < first; count++, second++)
				{
					for (int k = 0; k < 2 * size[i]; k++)
					{
						if (k < size[i])
						{
							ofs << LeftSlash[i][k].first * 100 + LeftSlash[i][k].second * 10 + first << " ";
						}
						if (k >= size[i] && k < size[i] * 2)
						{
							ofs << LeftSlash[i][k - size[i]].first * 100 + LeftSlash[i][k - size[i]].second * 10 + second << " ";
						}
					}
					ofs << 0 << endl;
					ClauseNum++;
				}
			}
		}

		// 7
		if (i == 2 || i == 6)
		{
			// 必选34567
			for (int num = 3; num <= 7; num++)
			{
				for (int k = 0; k < size[i]; k++)
				{
					ofs << LeftSlash[i][k].first * 100 + LeftSlash[i][k].second * 10 + num << " ";
				}
				ofs << 0 << endl;
				ClauseNum++;
			}

			// 1,8  2,8  2,9
			for (int first = 1; first <= 2; first++)
			{
				for (int second = 8,  count = 0; count < first; count++, second++)
				{
					for (int k = 0; k < 2 * size[i]; k++)
					{
						if (k < size[i])
						{
							ofs << LeftSlash[i][k].first * 100 + LeftSlash[i][k].second * 10 + first << " ";
						}
						if (k >= size[i] && k < size[i] * 2)
						{
							ofs << LeftSlash[i][k - size[i]].first * 100 + LeftSlash[i][k - size[i]].second * 10 + second << " ";
						}
					}
					ofs << 0 << endl;
					ClauseNum++;
				}
			}
		}

		// 8
		if (i == 3 || i == 5)
		{
			// 必选2345678
			for (int num = 2; num <= 8; num++)
			{
				for (int k = 0; k < size[i]; k++)
				{
					ofs << LeftSlash[i][k].first * 100 + LeftSlash[i][k].second * 10 + num << " ";
				}
				ofs << 0 << endl;
				ClauseNum++;
			}

			// 1,9
			for (int k = 1; k <= 2 * size[i]; k++)
			{
				if (k < size[i])
				{
					ofs << LeftSlash[i][k].first * 100 + LeftSlash[i][k].second * 10 + 1 << " ";
				}
				if (k >= size[i] && k < size[i] * 2)
				{
					ofs << LeftSlash[i][k - size[i]].first * 100 + LeftSlash[i][k - size[i]].second * 10 + 9 << " ";
				}
			}
			ofs << 0 << endl;
			ClauseNum++;
		}

		// 9
		if (i == 4)
		{
			// 必选12345678
			for (int num = 1; num <= 9; num++)
			{
				for (int k = 0; k < size[i]; k++)
				{
					ofs << LeftSlash[i][k].first * 100 + LeftSlash[i][k].second * 10 + num << " ";
				}
				ofs << 0 << endl;
				ClauseNum++;
			}
		}
	}


	for (int i = 0; i < 9; i++)
	{
		for (int first = 0; first < size[i]; first++)
		{
			for (int second = first + 1; second < size[i]; second++)
			{
				for (int n = 1; n <= 9; n++)
				{
					ofs << -(LeftSlash[i][first].first * 100 + LeftSlash[i][first].second * 10 + n) << " ";
					ofs << -(LeftSlash[i][second].first * 100 + LeftSlash[i][second].second * 10 + n) << " ";
					ofs << 0 << endl;
					ClauseNum++;
				}
			}
		}
	}
}

void Hanidoku::GenerateRightSlashClause(ofstream& ofs)
{
	for (int i = 0; i < 9; i++)
	{
		// 5蜂窝
		if (i == 0 || i == 8)
		{
			// 必选元素5
			for (int k = 0; k < size[i]; k++)
			{
				ofs << RightSlash[i][k].first * 100 + RightSlash[i][k].second * 10 + 5 << " ";
			}
			ofs << 0 << endl;
			ClauseNum++;

			// 1,6  2,6  2,7  3,6  3,7  3,8  4,6  4,7  4,8  4,9
			for (int first = 1; first <= 4; first++)
			{
				for (int second = 6, count = 0; count < first; count++, second++)
				{
					for (int k = 0; k < 2 * size[i]; k++)
					{
						if (k < size[i])
						{
							ofs << RightSlash[i][k].first * 100 + RightSlash[i][k].second * 10 + first << " ";
						}
						if (k >= size[i] && k < size[i] * 2)
						{
							ofs << RightSlash[i][k - size[i]].first * 100 + RightSlash[i][k - size[i]].second * 10 + second << " ";
						}
					}
					ofs << 0 << endl;
					ClauseNum++;
				}
			}
		}

		// 6
		if (i == 1 || i == 7)
		{
			// 必选456
			for (int num = 4; num <= 6; num++)
			{
				for (int k = 0; k < size[i]; k++)
				{
					ofs << RightSlash[i][k].first * 100 + RightSlash[i][k].second * 10 + num << " ";
				}
				ofs << 0 << endl;
				ClauseNum++;
			}

			//1,7  2,7  2,8  3,7  3,8  3,9
			for (int first = 1; first <= 3; first++)
			{
				for (int second = 7, count = 0; count < first; count++, second++)
				{
					for (int k = 0; k < 2 * size[i]; k++)
					{
						if (k < size[i])
						{
							ofs << RightSlash[i][k].first * 100 + RightSlash[i][k].second * 10 + first << " ";
						}
						if (k >= size[i] && k < size[i] * 2)
						{
							ofs << RightSlash[i][k - size[i]].first * 100 + RightSlash[i][k - size[i]].second * 10 + second << " ";
						}
					}
					ofs << 0 << endl;
					ClauseNum++;
				}
			}
		}

		// 7
		if (i == 2 || i == 6)
		{
			// 必选34567
			for (int num = 3; num <= 7; num++)
			{
				for (int k = 0; k < size[i]; k++)
				{
					ofs << RightSlash[i][k].first * 100 + RightSlash[i][k].second * 10 + num << " ";
				}
				ofs << 0 << endl;
				ClauseNum++;
			}

			// 1,8  2,8  2,9
			for (int first = 1; first <= 2; first++)
			{
				for (int second = 8, count = 0; count < first; count++, second++)
				{
					for (int k = 0; k < 2 * size[i]; k++)
					{
						if (k < size[i])
						{
							ofs << RightSlash[i][k].first * 100 + RightSlash[i][k].second * 10 + first << " ";
						}
						if (k >= size[i] && k < size[i] * 2)
						{
							ofs << RightSlash[i][k - size[i]].first * 100 + RightSlash[i][k - size[i]].second * 10 + second << " ";
						}
					}
					ofs << 0 << endl;
					ClauseNum++;
				}
			}
		}

		// 8
		if (i == 3 || i == 5)
		{
			// 必选2345678
			for (int num = 2; num <= 8; num++)
			{
				for (int k = 0; k < size[i]; k++)
				{
					ofs << RightSlash[i][k].first * 100 + RightSlash[i][k].second * 10 + num << " ";
				}
				ofs << 0 << endl;
				ClauseNum++;
			}

			// 1,9
			for (int k = 1; k <= 2 * size[i]; k++)
			{
				if (k < size[i])
				{
					ofs << RightSlash[i][k].first * 100 + RightSlash[i][k].second * 10 + 1 << " ";
				}
				if (k >= size[i] && k < size[i] * 2)
				{
					ofs << RightSlash[i][k - size[i]].first * 100 + RightSlash[i][k - size[i]].second * 10 + 9 << " ";
				}
			}
			ofs << 0 << endl;
			ClauseNum++;
		}

		// 9
		if (i == 4)
		{
			// 必选12345678
			for (int num = 1; num <= 9; num++)
			{
				for (int k = 0; k < size[i]; k++)
				{
					ofs << RightSlash[i][k].first * 100 + RightSlash[i][k].second * 10 + num << " ";
				}
				ofs << 0 << endl;
				ClauseNum++;
			}
		}
	}


	for (int i = 0; i < 9; i++)
	{
		for (int first = 0; first < size[i]; first++)
		{
			for (int second = first + 1; second < size[i]; second++)
			{
				for (int n = 1; n <= 9; n++)
				{
					ofs << -(RightSlash[i][first].first * 100 + RightSlash[i][first].second * 10 + n) << " ";
					ofs << -(RightSlash[i][second].first * 100 + RightSlash[i][second].second * 10 + n) << " ";
					ofs << 0 << endl;
					ClauseNum++;
				}
			}
		}
	}
}



void Hanidoku::InitRow()
{
	Row.push_back({ {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5} });
	Row.push_back({ {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6} });
	Row.push_back({ {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7} });
	Row.push_back({ {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}, {4, 8} });
	Row.push_back({ {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {5, 7}, {5, 8}, {5, 9} });
	Row.push_back({ {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}, {6, 7}, {6, 8} });
	Row.push_back({ {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5}, {7, 6}, {7, 7} });
	Row.push_back({ {8, 1}, {8, 2}, {8, 3}, {8, 4}, {8, 5}, {8, 6} });
	Row.push_back({ {9, 1}, {9, 2}, {9, 3}, {9, 4}, {9, 5} });
}

void Hanidoku::InitLeftSlash()
{
	LeftSlash.push_back({ {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1} });
	LeftSlash.push_back({ {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 1} });
	LeftSlash.push_back({ {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 2}, {7, 1} });
	LeftSlash.push_back({ {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 3}, {7, 2}, {8, 1} });
	LeftSlash.push_back({ {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 4}, {7, 3}, {8, 2}, {9, 1} });
	LeftSlash.push_back({ {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 5}, {7, 4}, {8, 3}, {9, 2} });
	LeftSlash.push_back({ {3, 7}, {4, 7}, {5, 7}, {6, 6}, {7, 5}, {8, 4}, {9, 3} });
	LeftSlash.push_back({ {4, 8}, {5, 8}, {6, 7}, {7, 6}, {8, 5}, {9, 4} });
	LeftSlash.push_back({ {5, 9}, {6, 8}, {7, 7}, {8, 6}, {9, 5} });
}

void Hanidoku::InitRightSlash()
{
	RightSlash.push_back({ {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1} });
	RightSlash.push_back({ {4, 1}, {5, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 2} });
	RightSlash.push_back({ {3, 1}, {4, 2}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 3} });
	RightSlash.push_back({ {2, 1}, {3, 2}, {4, 3}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4} });
	RightSlash.push_back({ {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 5}, {7, 5}, {8, 5}, {9, 5} });
	RightSlash.push_back({ {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 6}, {7, 6}, {8, 6} });
	RightSlash.push_back({ {1, 3}, {2, 4}, {3, 5}, {4, 6}, {5, 7}, {6, 7}, {7, 7} });
	RightSlash.push_back({ {1, 4}, {2, 5}, {3, 6}, {4, 7}, {5, 8}, {6, 8} });
	RightSlash.push_back({ {1, 5}, {2, 6}, {3, 7}, {4, 8}, {5, 9} });
}

void Hanidoku::Init_hanidoku(std::vector<std::vector<Cellular>>& Hanidoku)
{ 
	for (int i = 0; i < 9; i++)
	{
		std::vector<Cellular> innerVector;
		for (int j = 0; j < size[i]; j++)
		{
			innerVector.push_back({ 0, 0, 0, 0 });
		}
		Hanidoku.push_back(innerVector);
	}
	// 设置行数以及将数字设置成0
	for (int row = 0; row < 9; row++)
	{
		for (int i = 0; i < size[row]; i++)
		{
			Hanidoku[row][i].num = 0;
			Hanidoku[row][i].row = row;
		}
	}

	// 设置left_slash
	for (int left_slash = 0; left_slash < 9; left_slash++)
	{
		for (int i = 0; i < size[left_slash]; i++) 
		{
			Hanidoku[LeftSlash[left_slash][i].first - 1][LeftSlash[left_slash][i].second - 1].left_slash = left_slash;
		}
	}

	// 设置right_slash
	for (int right_slash = 0; right_slash < 9; right_slash++)
	{
		for (int i = 0; i < size[right_slash]; i++)
		{
			Hanidoku[RightSlash[right_slash][i].first - 1][RightSlash[right_slash][i].second - 1].right_slash = right_slash;
		}
	}
}


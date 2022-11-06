#include <iostream>
#include <vector>
using namespace std;

int sudoku[9][9] = {
		{5,3,0,0,7,0,0,0,0},
		{6,0,0,1,9,5,0,0,0},
		{0,9,8,0,0,0,0,6,0},
		{8,0,0,0,6,0,0,0,3},
		{4,0,0,8,0,3,0,0,1},
		{7,0,0,0,2,0,0,0,6},
		{0,6,0,0,0,0,2,8,0},
		{0,0,0,4,1,9,0,0,5},
		{0,0,0,0,8,0,0,7,9}
};

bool possible(int arr[9][9], int row, int col, int num)
{
	if (arr[row][col] != 0) { return false; }
	int sq_r = (row / 3) * 3;
	int sq_c = (col / 3) * 3;

	for (int i = 0; i < 9; i++)
	{
		if (arr[i][col] == num) { return false; break; }
		if (arr[row][i] == num) { return false; break; }
		if (arr[sq_r + i / 3][sq_c + i % 3] == num) { return false; break; }

	}
	return true;
}

//подразбери еще этот механизм
void next_RandC(int arr[9][9],int row, int col,int& next_row,int& next_col)
{
	int indexNext = 9 * 9 + 1;
	for (int i = row * 9 + col + 1; i < 9 * 9; i++)
	{
		if (arr[i / 9][i % 9] == 0)
		{
			indexNext = i;
			break;
		}
	}
	next_row = indexNext / 9;
	next_col = indexNext % 9;
}

std::vector<int> possible_solutions(int arr[9][9], int row, int col)
{
	std::vector<int> cps = {};
	for (int i = 0; i < 10; i++)
	{
		if (possible(arr, row, col, i))
			cps.push_back(i);
	}
	return cps;
}
//Возможно так не сработает
void copy(int arr[9][9], int arr_cpy[9][9])
{
	for (int y = 0; y < 9; y++)
		for (int x = 0; x < 9; x++)
			arr_cpy[y][x] = arr[y][x];
}

bool solve(int arr[9][9], int row, int col)
{
	if (row > 8) { return true; }

	if (arr[row][col] != 0) 
	{ 
		int next_r, next_c;  
		next_RandC(arr, row, col,next_r,next_c);
		return solve(arr, next_r, next_c);
	}

	std::vector <int> Nums = possible_solutions(arr,row,col);

	if (Nums.size() == 0) { return false;}

	bool status = false;

	for (int i = 0; i < Nums.size(); i++)
	{
		int Arr_copy[9][9];
		copy(arr, Arr_copy);
		int n = Nums[i];
		Arr_copy[row][col] = n;
		int next_r, next_c;
		next_r = row;
		next_c = col;
		next_RandC(arr, row, col,next_r, next_c);
		if (solve(Arr_copy, next_r, next_c))
		{
			copy(Arr_copy, arr);
			status = true;
			break;
		}
	}
	return status;
}

void sud_cout(int sudoku[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		if (i == 0)
		{
			cout << " -----------------------";
			cout << endl;
		}
		for (int j = 0; j < 9; j++)
		{
			if (j == 0)
			{
				cout << "| ";
			}
			cout << sudoku[i][j] << " ";
			if ((j + 1) % 3 == 0)
			{
				cout << "|" << " ";
			}
		}
		cout << endl;
		if ((i + 1) % 3 == 0)
		{
			cout << " -----------------------";
			cout << endl;
		}
	}
	cout << endl;
}


int main()
{
	cout << "    Sudoku for solve  " << endl;
	sud_cout(sudoku);
	if (solve(sudoku, 0, 0))
	{
		cout << "       resolved" << std::endl;
		sud_cout(sudoku);
	}
	else cout << " error ";


	return 0;

}


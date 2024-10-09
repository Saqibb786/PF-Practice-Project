#include <iostream>

using namespace std;

// prototypes
int **dynamic_2d(int, int);
void display_whole(int **, int, int);
void insert_new(int **, int, int, int);
void total_results(int **, int, int);
void del_value(int **, int, int);
void first_max(int **, int, int);
void cal_avg(int **, int);
float cal_sum(int *, int, int &);
void max_field(int **, int, int);

// main
int main()
{
	int row = 0, col = 0;
	cout << "Please enter number of feilds: ";
	cin >> row;
	cout << "\nPlease enter no. of tests conducted for each feild: ";
	cin >> col;
	cout << endl;
	if (row <= 0 || col <= 0)
	{
		cout << "Please Enter valid values for fields & tests conducted...\n";
		cout << "Please enter no. of feilds: ";
		cin >> row;
		cout << "\nPlease enter no. of tests conducted for each feild: ";
		cin >> col;
		cout << endl;
	}
	if (row > 0 && col > 0)
	{
		int **arr = dynamic_2d(row, col);

		bool again = true;
		do
		{
			int option = 0; // For handling cases for
			cout << "Press 1 to insert new test result.\n";
			cout << "Press 2 to display total number of results in table.\n";
			cout << "Press 3 to delete any test value from table.\n";
			cout << "Press 4 to display the 2 most frequent values in table.\n";
			cout << "Press 5 to display average scores of each field.\n";
			cout << "Press 6 to display field having maximum success score.\n";
			cout << "Press 7 to display table.\n";
			cout << "Press 0 to Exit.\n";
			cout << "You choosed: ";
			cin >> option;
			cout << endl;

			switch (option)
			{
			case 1:
			{
				int value = 0;
				cout << "Please enter the new value: ";
				cin >> value;
				insert_new(arr, row, col, value);
				display_whole(arr, row, col);

				cout << endl;
				break;
			}
			case 2:
			{
				total_results(arr, row, col);

				cout << endl;
				break;
			}
			case 3:
			{
				int value = 0;
				cout << "Please enter the value to delete: ";
				cin >> value;
				del_value(arr, col, value);

				cout << endl;
				break;
			}
			case 4:
			{
				first_max(arr, row, col);

				cout << endl;
				break;
			}
			case 5:
			{
				cal_avg(arr, col);

				cout << endl;
				break;
			}
			case 6:
			{
				max_field(arr, row, col);

				cout << endl;
				break;
			}
			case 7:
			{
				display_whole(arr, row, col);

				cout << endl;
				break;
			}
			case 0:
			{
				again = false;
				cout << "Thanks....\n";
			}
			}
		} while (again);
	}

	system("pause");
	return 0;
}

// functions
int **dynamic_2d(int row, int col)
{
	int **temp = new int *[row];
	for (int r = 0; r < row; r++)
		temp[r] = new int[col];

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			temp[r][c] = -1;
		}
	}

	return temp;
}
void display_whole(int **arr, int row, int col)
{
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			cout << arr[r][c] << "\t";
		}
		cout << endl;
	}
}
void insert_new(int **arr, int row, int col, int value)
{
	int rowNo = 0;
	cout << "Please enter field-no: ";
	cin >> rowNo;
	cout << endl;
	if (rowNo > row || rowNo < 0)
		cout << "The field-no you entered does'nt exist.\n";
	else
	{
		bool empty = false;
		for (int c = 0; c < col; c++)
		{
			if (arr[rowNo][c] == -1)
			{
				arr[rowNo][c] = value;
				cout << value << " is entered at given location\n";
				empty = true;
				break;
			}
		}
		if (!empty)
			cout << "The given field is full\n";
	}
}
void total_results(int **arr, int row, int col)
{
	int count = 0;
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			if (arr[r][c] != -1)
				count++;
		}
	}
	cout << "There are total " << count << " values entered in table.\n";
}
void del_value(int **arr, int col, int value)
{
	int rowNo = 0;
	bool found = false;
	cout << "Please enter field-no: ";
	cin >> rowNo;
	cout << endl;
	for (int c = 0; c < col; c++)
	{
		if (arr[rowNo][c] == value)
		{
			arr[rowNo][c] = -1;
			found = true;
		}
	}
	if (found)
		cout << value << " is deleted from field-" << rowNo << endl;
	else
	{
		cout << "Value not found\n";
	}
}
void first_max(int **arr, int row, int col)
{
	int max = 0, temp = 0, indexR = 0, indexC = 0, mcount = 0, tcount = 0;
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			if (arr[r][c] != -1)
			{
				temp = arr[r][c];
				indexR = r;
				indexC = c;
				for (int innerR = 0; innerR < row; innerR++)
				{
					for (int innerC = 0; innerC < col; innerC++)
					{
						if (arr[innerR][innerC] == temp)
						{
							tcount++;
						}
					}
				}
				if (tcount > mcount)
					max = temp;
				mcount = tcount - 1;
			}
		}
	}
	if (mcount > 0)
		cout << max << " has max occurrance of " << mcount << " times.\n";

	else
		cout << "Table is empty\n";
}
void cal_avg(int **arr, int col)
{
	int rowNo = 0, skips = 0, no = 0;
	cout << "Please enter field-no: ";
	cin >> rowNo;
	cout << endl;
	float sum = cal_sum(arr[rowNo], col, skips);
	no = col - skips;
	float avg = sum / no;
	cout << "The average test score of field no-" << rowNo << " values is " << avg << "%.\n";
}
float cal_sum(int *arr, int size, int &skips)
{
	float sum = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == -1)
		{
			skips++;
			continue;
		}
		else
			sum = sum + arr[i];
	}
	return sum;
}
void max_field(int **arr, int row, int col)
{
	int sum = 0, index = 0, skips = 0;
	int max = cal_sum(arr[0], col, skips);
	for (int r = 1; r < row; r++)
	{
		sum = cal_sum(arr[r], col, skips);
		if (sum > max)
		{
			max = sum;
			index = r;
		}
	}
	cout << "Feild no " << index << " has greatest score of: " << max;
	cout << endl;
}
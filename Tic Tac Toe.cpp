#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
using namespace std;
const int rows = 3, cols = 3;
class TicTacToe
{
private:
	char check[rows][cols];
	int i, row, col;
	int c_row = 0, c_col = 0;
	bool win, draw, done;
public:
	void checkVertically(char player)
	{
		int count = 0;
		for (int i = 0; i < rows; i++)
		{
			if (check[i][col] == player)
				count++;
		}
		if (count == rows)
			win = true;
	}
	void checkHorizantally(char player)
	{
		int count = 0;
		for (int i = 0; i < cols; i++)
		{
			if (check[row][i] == player)
				count++;
		}
		if (count == cols)
			win = true;
	}
	void checkDiagonally(char player)
	{
		/*Left diagonal*/
		int count = 0, j = 0;
		for (int i = 0; i < rows; i++)
		{
			if (check[i][j] == player)
				count++;
			j++;
		}
		if (count == rows)
			win = true;
		count = 0, j = cols - 1;
		/*Right diagonal*/
		for (int i = 0; i < rows; i++)
		{
			if (check[i][j] == player)
				count++;
			j--;
		}
		if (count == rows)
			win = true;
	}
	void checkdraw()
	{
		int count = 0;
		for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			if (check[i][j] != '_')
				count++;
		}
		if (count == rows*cols)
			draw = true;
	}
	void display()
	{
		cout << "\n\n\n     ";
		for (int i = 0; i < cols; i++)
			cout << setw(3) << i;
		cout << endl << endl;
		for (int i = 0; i < rows; i++)
		{
			cout << setw(5) << i << "  ";
			for (int j = 0; j < cols; j++)
			{
				cout << check[i][j] << "| ";
			}
			cout << endl << endl;
		}
	}
	void computermove()
	{
		ComputerAI('C');
		if (!done)
			ComputerAI('P');
		if (!done)
		{
			row = rand() % rows, col = rand() % cols;
			while (check[row][col] != '_')
			{
				row = rand() % rows; col = rand() % cols;
			}
			check[row][col] = 'C';
		}
	}
	void ComputerAI(char player)
	{
		done = false;
		int Ncount = 0, Scount = 0;
		//Horizontal
		int i = 0, j, x;
		while (i < rows&&!done)
		{
			j = 0;
			Ncount = 0, Scount = 0;
			while (j < cols)
			{
				if (check[i][j] == '_')
				{
					Scount++;
					x = j;
				}
				else if (check[i][j] == player)
					Ncount++;
				j++;
			}
			if (Ncount == 2 && Scount == 1)
			{
				check[i][x] = 'C';
				row = i;
				col = x;
				done = true;
			}
			i++;
		}
		//Vertical
		if (!done)
		{
			i = 0, x;
			while (i < cols&&!done)
			{
				j = 0;
				Ncount = 0, Scount = 0;
				while (j < rows)
				{
					if (check[j][i] == '_')
					{
						Scount++;
						x = j;
					}
					else if (check[j][i] == player)
						Ncount++;
					j++;
				}
				if (Ncount == 2 && Scount == 1)
				{
					check[x][i] = 'C';
					row = x;
					col = i;
					done = true;
				}
				i++;
			}
		}
		//Leftdiagonal
		if (!done)
		{
			i = 0, x;
			Ncount = 0, Scount = 0;
			while (i < rows)
			{
				if (check[i][i] == '_')
				{
					Scount++;
					x = i;
				}
				else if (check[i][i] == player)
					Ncount++;
				i++;
			}
			if (Ncount == 2 && Scount == 1)
			{
				check[x][x] = 'C';
				row = col = x;
				done = true;
			}
		}
		//Rightdiagonal
		if (!done)
		{
			i = rows - 1, x;
			Ncount = 0, Scount = 0;
			while (i >= 0)
			{
				if (check[i][cols - i - 1] == '_')
				{
					Scount++;
					x = i;
				}
				else if (check[i][cols - i - 1] == player)
					Ncount++;
				i--;
			}
			if (Ncount == 2 && Scount == 1)
			{
				check[x][cols - x - 1] = 'C';
				row = x;
				col = cols - x - 1;
				done = true;
			}
		}
	}
	void gameprocessing()
	{
		while (win == false && draw == false)
		{
			if (i % 2 == 0)
			{
				system("cls");
				display();
				cout << "Player P's turn\n\n";
				TakeInput('P');
				checkVertically('P');
				checkHorizantally('P');
				checkDiagonally('P');
				checkdraw();
				system("cls");
				display();
				if (win == true)
					cout << "\nPlayer P wins\n";
			}
			else
			{
				system("cls");
				display();
				cout << "Player C's turn\n\n";
				Sleep(3000);
				done = false;
				computermove();
				checkVertically('C');
				checkHorizantally('C');
				checkDiagonally('C');
				checkdraw();
				system("cls");
				display();
				if (win == true)
					cout << "\nPlayer C wins\n";
			}
			i++;
		}
		if (draw == true)
			cout << "Game draws\n";
	}
	void TakeInput(char player)
	{
		cout << "Enter row and column(0..2): ";
		cin >> row >> col;
		while (check[row][col] != '_' || row < 0 || row >= rows || col < 0 || col >= cols)
		{
			cout << "Not a valid input\n Please input again: ";
			cin >> row >> col;
		}
		check[row][col] = player;
	}
	TicTacToe()
	{
		win = draw = done = false;
		i = 0;
		for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			check[i][j] = '_';
	}

};
int main()
{
	srand(time(NULL));
	TicTacToe obj;
	obj.gameprocessing();
	system("pause");
}
//Name: Gabriel Ball
//Date: 06/06/2026
//Desc: This program uses Backtracking to solve the N-Queens problem

#include <iostream>
#include <vector>
using namespace std;

void printBoard(const vector<vector<char>>& board) {
    const int cellWidth = 3; //For formatting as square
    for (int r = 0; r < board.size(); r++) {
        //Top border
        for (int c = 0; c < board[r].size(); c++) {
            cout << "+";
            for (int i = 0; i < cellWidth; i++)
                cout << "-";
        }
        cout << "+\n";

        //Cell content
        for (int c = 0; c < board[r].size(); c++)
            cout << "| " << board[r][c] << " ";
        cout << "|\n";
    }

    //Bottom border
    for (int c = 0; c < board[0].size(); c++) {
        cout << "+";
        for (int i = 0; i < cellWidth; i++)
            cout << "-";
    }
    cout << "+\n";
}

bool isPromising(const vector<vector<char>>& board, int row, int col) {
    //Check column
    for (int i = 0; i < board.size(); i++)
        if (board[i][col] == 'Q') return false; //Unsafe

    //Check upper-left diagonal
    for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; r--, c--)
        if (board[r][c] == 'Q') return false; //Unsafe

    //Check upper-right diagonal
    for (int r = row - 1, c = col + 1; r >= 0 && c < board.size(); r--, c++)
        if (board[r][c] == 'Q') return false; //Unsafe

    return true; //Safe
}

bool tryCell(vector<vector<char>>& board, int curRow) {
    if (curRow == board.size())
        return true; //Base case: All rows filled - solution found

    //Try every column in the current row
    for (int c = 0; c < board[curRow].size(); c++) {
        //Only test cell if it's promising (cannot attack existing queens)
        if (isPromising(board, curRow, c)) {
            board[curRow][c] = 'Q'; //Place queen

            //Try the next row
            if (tryCell(board, curRow + 1))
                return true; //If the solution was found, we finish

            board[curRow][c] = ' '; //No solution down this path, remove queen and try next column
        }
    }
    
    //No solution
    return false;
}

int main() {
	vector<vector<char>> board;

    //Get n
	int n;
	cout << "Enter the size of the board: ";
	cin >> n;

    //Initialize n x n size board
	for (int i = 0; i < n; i++) {
		board.push_back(vector<char>(n, ' '));
	}

    //Start algorithm
    if (tryCell(board, 0)) { //Solution found
        printBoard(board);
    }
    else { //No solution
        cout << "No solution found\n";
    }
}
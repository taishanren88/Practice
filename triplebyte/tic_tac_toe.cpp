#include <iostream>
#include <vector>
#include <sstream>
#include <stdlib.h>
using namespace std;

class Board {
public:
Board()
:m_board(vector<vector<char>>(3, vector<char>(3, '-'))) {

}
void print() {
	for (int i = 0; i < m_board.size(); i++) {
		for (int j = 0; j < m_board[i].size(); j++) {
			cout << m_board[i][j];
			if (j < 2)
				cout << "|";
		}
		cout << endl;
	}
}
bool addToken(char token, int r, int c) {
	if (isFull())
		return false;

	m_board[r][c] = token;
	return true;
}
bool isFull() const {
	for (int i = 0; i < m_board.size(); i++) {
		for (int j = 0; j < m_board[i].size(); j++) {
			if (m_board[i][j] == '-')
				return false;
		}
	}
	return true;
}

vector<vector<char>> getGrid() const {
	return m_board;
}

private:
vector<vector<char>> m_board;

};

bool getAIMove(const vector<vector<char>> &grid, int& oPosR, int& oPosC) {
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			if (grid[i][j] == '-') {
				oPosR = i;
				oPosC = j;
				return true;
			}
		}
	}
	return false;
}

bool isValidString(string input, int& oPosR, int& oPosC) {
	// Expecting a string with 2 numbers and a space in the middle
    stringstream check1(input); 
    string intermediate; 
    vector<string> tokens;
    // Tokenizing w.r.t. space ' ' 
    while(getline(check1, intermediate, ' ')) 
    { 
        tokens.push_back(intermediate); 
    }
    if (tokens.size() != 2)
    	return false;
    auto check= [](long val) {
	 if ( (errno == ERANGE &&
	     		(val == LONG_MAX || val == LONG_MIN))
	     		|| (errno != 0 && val == 0))
	     	return false;
	     return true;
    };
     long resultR = strtol(tokens[0].c_str(), nullptr, 10);
    	if (!check(resultR))
    		return false;
     long resultC = strtol(tokens[1].c_str(), nullptr, 10);
     if (!check(resultC))
     	return false;

     oPosR = resultR;
     oPosC = resultC;
	return true;
}
void play() {
	Board board;
	bool isPlayerTurn = true;
	// input : r c 
	board.print();

	while (true) {
		if (isPlayerTurn) {
			string input;
			int playerR, playerC;
			do
			{
				cout << "Player, please enter position";
				getline(cin,input);

			}while (!isValidString(input, playerR, playerC));
			board.addToken('X', playerR, playerC);

		} else {
			int posR, posC;
			getAIMove(board.getGrid(), posR, posC);
			bool success = board.addToken('O', posR, posC);
			if (!success) {
				throw "Invalid move";
			}
		}
		board.print();

		isPlayerTurn = !isPlayerTurn;
	}
}
int main() {
	// 
	// tictactoe.print();
	// tictactoe.addToken('X', 2, 0);
	// tictactoe.print();
	play();
}
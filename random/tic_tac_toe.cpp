#include <iostream>
#include <string>
#include <ctype.h>
#include <sstream>
#include <vector>
#include <iomanip>      // std::setw
using namespace std;

void display(vector<vector<char> >& grid, string& player) {

	cout << "Player " << player << " needs to make a turn " << endl;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			cout << setw (5) << grid[i][j];
		}
		cout << endl;
	}

}
bool validMove(vector<vector<char>> & grid, int r, int c) {
	if ( (r < 0 && r >= grid.size()) 
		|| 
		 (c < 0 && c >= grid[r].size())
		|| grid[r][c] != '.') {
		return false;
	}
	else return true;

}
// Returns true, if game is not over, false otherwise
// If player has one, oPlayer will be
bool gameContinues(vector<vector<char>> & grid) {
	// Returns true if we have a 3 in a row somewhere (in other words, we won)
	auto checkHorizontal=[&](int r) {
		if (grid[r][0] != '.' && grid[r][0] == grid[r][1] && grid[r][0] == grid[r][2]) {
			return true;
		}
		return false;
	};
	auto checkVertical=[&](int c){
		if (grid[0][c] != '.' && grid[0][c] == grid[1][c] && grid[0][c] == grid[2][c]) {
			return true;
		}
		return false;
	};
	auto checkDiagonals=[&](){
		if  ( (grid[0][0] != '.' && grid[0][0] == grid[1][1] && grid[2][2] == grid[0][0]) 
			|| (grid[0][2] != '.'  && grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0]))  {
			return true;
		}
		else
			return false;
	};
	if (checkHorizontal(0)
		|| checkHorizontal(1)
		|| checkHorizontal(2)
		|| checkVertical(0)
		|| checkVertical(1)
		|| checkVertical(2)
		|| checkDiagonals())
	return false;

	return true; // more to play
}
void play() {
	// Let first player to choose 'X' or 'O'
	// At each point show the grid
	// make a move, check if it's valid
	// while the player hasn't won yet
	string player = "\0";
	do {
		 cout << "Pick a player, either 'O' or 'X' ";
 		 getline (cin, player);
 		 auto cleanup =[&]() {
 		 	for (char& c : player) {
 		 		c = tolower(c);
 		 	}
 		 };
 		 cleanup();
	}while (player != "x" && player != "o");

	vector<vector<char>> grid(3, vector<char>(3, '.'));
	bool gameInProgress = true;
	string move;
	do {
		display(grid, player);
		cout << "Player " << player << " enter a move in the form: r,c" << endl;
		getline (cin, move);
		auto validInput =[&](pair<int, int>& oPos){
			vector <int> tokens; 
			// stringstream class check1 
		    stringstream check1(move); 
		    string intermediate; 
		    // Tokenizing w.r.t. space ' ' 
		    while(getline(check1, intermediate, ' ')) 
		    { 
		        tokens.push_back(strtol(intermediate.c_str(), nullptr, 10));
		        if (tokens.back() == 0 && errno == EINVAL)
		        	return false;
		    }
		    if (tokens.size() != 2)
		    	return false;
		    oPos= make_pair(tokens[0], tokens[1]);
		    // also check for validity of the move itself
		    return true;
		};
		pair<int, int> pos;
		if (!validInput(pos) 
			|| !validMove(grid, pos.first, pos.second)) {
				cout << "Invalid move...try again" << endl;
		} else {
			grid[pos.first][pos.second] = player[0];
			gameInProgress = gameContinues(grid);
			if (gameInProgress) {
				player = player == "o" ? "x" : "o";
			}
		}

	}while(gameInProgress);
	cout << "Player " << player << " has won " << endl;

}
int main() {
	play();

}
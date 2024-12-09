#include <iostream>
#include <vector>

using namespace std;

static const int DEAD = 0;
static const int LIVE = 1;
static const int WAS_LIVE = -1;
static const int BECAME_LIVE = 2;

void helper(vector<vector<int>>& board, int r, int c ) {
     // Live -> 1, -1
    // Dead -> 0, 2
    // Live to Dead -> -1
    // Dead to Live -> 2
    
    // Check if num of Neighbors(1 or -1) < 2 or  > 3 .=> -1
    // Check if num of Neighbors(1 or -1) == 

    int count = 0;
    auto appendLiveCount =[&](int r, int c) {
          if (r < 0 || r >= board.size() 
                || c < 0 || c >= board[r].size()) {
                return;
            }
        if (board[r][c] == LIVE || board[r][c] == WAS_LIVE) {
            count++;
        }
    };
    appendLiveCount(r, c-1);
    appendLiveCount(r-1, c-1);
    appendLiveCount(r-1, c);
    appendLiveCount(r-1, c+1);
    appendLiveCount(r, c+1);
    appendLiveCount(r+1, c+1);
    appendLiveCount(r+1, c );
    appendLiveCount(r+1, c -1);
    if (board[r][c] == LIVE) {
        if (count < 2 ||  count > 3) {
            board[r][c] = WAS_LIVE;
        }
    } else {
        if (count == 3) {
            board[r][c] = BECAME_LIVE;
        }
    }
}
void gameOfLife(vector<vector<int>>& board) {
    for (int i = 0;i  < board.size(); i++ ){
        for (int j = 0; j < board[i].size(); j++){
            helper(board, i, j);
        }
    }

    for (int i = 0;i  < board.size(); i++ ){
        for (int j = 0; j < board[i].size(); j++){
            if (board[i][j] == WAS_LIVE) {
                board[i][j] = DEAD;
            } else if (board[i][j] == BECAME_LIVE) {
                board[i][j] = LIVE;
            }
        }
    }

}

int main() {

    vector<vector<int>> board =   {{0,1,0},
  {0,0,1},
  {1,1,1},
  {0,0,0}};
  gameOfLife(board);
  for (int i = 0; i < board.size() ; i++ ){
    for (int j =0; j <board[i].size(); j++) {
        cout << board[i][j] << ",";
    }
    cout << endl;
  }
}
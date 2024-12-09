// Grid game (pacman)

// Part 1: initializing and printing board
// n: board dimension, int, n*n
// row: initial row of player, int
// col: initial column of player, int
// orientation: initial orientation of player, (N, E, S, W)

// printBoard()
// - v -
// - - -
// - - -

// n = 3, row = 0, col = 1, orientation = 'S'

// - is an empty space
// ^ is player facing north
// > is player facing east
// v is player facing south
// < is player facing west

// Part 2: move method
// move("FFLFR")

// F: step forward 1 grid position in whatever direction player is facing
// L: rotation 90 degrees in place to the left (counterclockwise)
// R: rotation 90 degrees in place to the right (clockwise)

// Part 3: boundary handling

// start
// - - - 
// - - >
// - - -

// move(“F”)

// end
// - - - 
// > - -
// - - -

// Part 4: add enemies
// nEnemies, we will add nEnemies to the board randomly with following rules:
// they don't overlap with the player initial posiiton
// they don't overlap with each other
// print them as "E"

// Part 5:

// start
// - v - 
// - E -
// E - -

// move(“FF”)

// GAME OVER
// - - - 
// - X -
// E - -


#include <iostream>
#include <unordered_map>

using namespace std;

// struct Object {

// };

struct Enemy {
int row, col;
};

struct Player {
  Player(int r, int c, char aOrient) : row(r), col(c), orientation(aOrient) {
    alive = true;
  }
  int row, col;
  char orientation;

  bool alive;
};

class Game {

public:
  Game(int N, int playerRow, int playerCol, char orientation, int aEnemies)
      : player(playerRow, playerCol, orientation), board_size(N) {
            // Seed the random number generator with the current time
    srand(time(0));

          for (int i = 0; i < aEnemies; i++) {
              auto enemy = generateEnemy();
              enemies[getEnemyHashForPosition(enemy.row, enemy.col)] = enemy;
                    // printf("entered at :%d,%d\n", enemy.row, enemy.col);
          }

      }

  Enemy generateEnemy() {
    int randRow = -1;
    int randCol = -1;
    do {
      // cout << "Generated" << endl;
     randRow = rand() % board_size; // generate 0 -> to N - 1
    randCol = rand() % board_size;
    }while (randRow == player.row && randCol == player.col &&
          enemies.find(getEnemyHashForPosition(randRow, randCol)) == enemies.end());
    Enemy e;
    e.row = randRow;
    e.col = randCol;

    return e;
  }

  string getEnemyHashForPosition( int row, int col)  {
   return to_string(row) + "," + to_string(col) ;
  }

  void printBoard() {
    for (int i = 0; i < board_size; i++) {
      for (int j = 0; j < board_size; j++) {
        if (i == player.row && j == player.col) {
          cout << getOrientationMapping(player.orientation) << ' ';
        } else {
          if (enemies.find(getEnemyHashForPosition(i,j)) != enemies.end()) {
            cout << "E ";
          } else {
            cout << "- ";
          }
        }
      }
      cout << endl;
    }

  }

/* 
// Part 2: move method
// move("FFLFR")

// F: step forward 1 grid position in whatever direction player is facing
// L: rotation 90 degrees in place to the left (counterclockwise)
// R: rotation 90 degrees in place to the right (clockwise)
*/
  void move(string commands ) {
    for (char c : commands ) {
      if (c == 'F') {
        updatePositionForNextForwardPosition();
      } else if (c == 'L') {
        updateOrientationForCounterClockwise();
      } else if (c == 'R') {
        updateOrientationForClockwise();
      } else {
        // not supported
      }
    }
  }

private:
// Orientation -> direction
char getOrientationMapping(char direction) {
 switch (direction) {
    case 'S' :
      return 'V';
    case 'E': 
    return '>';
    case 'W':
    return '<';
    case 'N':
    return '^';
    default:
     return 'N' ;// should not happen n
 }
}

 void updatePositionForNextForwardPosition() {
  if (player.orientation == 'S') {
      player.row++;
      if (player.row == board_size) {
        player.row = 0;
      }
  } else if (player.orientation == 'E') {
    player.col++;
    if (player.col == board_size ){
      player.col = 0;
    }
  } else if (player.orientation == 'W') {
      player.col--;
      if (player.col == -1 ) {
        player.col = board_size - 1;
      }
  } else if (player.orientation == 'N') {
    player.row--;
    if (player.row == -1 ) {
      player.row = board_size - 1;
    }
  }
}

void updateOrientationForCounterClockwise(){
    if (player.orientation == 'S') {
      player.orientation = 'E';
  } else if (player.orientation == 'E') {
    player.orientation = 'N';
  } else if (player.orientation == 'W') {
    player.orientation = 'S';
  } else if (player.orientation == 'N') {
      player.orientation ='W';
  }
}

void updateOrientationForClockwise(){
    if (player.orientation == 'S') {
      player.orientation = 'W';
  } else if (player.orientation == 'E') {
    player.orientation = 'S';
  } else if (player.orientation == 'W') {
    player.orientation = 'N';
  } else if (player.orientation == 'N') {
      player.orientation ='E';
  }
}

  Player player;
  int board_size;
  unordered_map<string, Enemy> enemies;
};
// To execute C++, please define "int main()"
int main() {
  // auto words = { "Hello, ", "World!", "\n" };
  // for (const char* const& word : words) {
  //   cout << word;
  // }

  /*
// - v -
// - - -
// - - -

// n = 3, row = 0, col = 1, orientation = 'S'
  */
  Game game(3, 0, 1, 'S', 2);
  game.printBoard();

cout << endl;
  // game.move("F");
  // game.printBoard();

  // cout << endl;
  // game.move("FLFR");
  // game.printBoard();

  cout << endl;


    cout << endl;
  // game.move("LFFF");
    // game.printBoard();

  // game.move("FFF");
  // game.printBoard();
  //   cout << endl;
  // Game game2(2, 0, 1, 'N');
  // game2.printBoard();

  // cout << endl;
  // Game game3(1, 0, 0, 'N');
  // game3.printBoard();

  return 0;
  
}

// Your previous Plain Text content is preserved below:

// This is just a simple shared plaintext pad, with no execution capabilities.

// When you know what language you'd like to use for your interview,
// simply choose it from the dots menu on the tab, or add a new language
// tab using the Languages button on the left.

// You can also change the default language your pads are created with
// in your account settings: https://app.coderpad.io/settings

// Enjoy your interview!
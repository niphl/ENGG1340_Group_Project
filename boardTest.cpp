//Main Game

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <time.h>

using namespace std;

int strToX(string s, int max);
int strToY(string s, int max);

struct Board{
    int * mineBoard; //stores where the mines are
    char * playerBoard; //stores where the player has checked and flagged,'U' for uncovered, 'F' for flagged 'X' for unchecked
    int difficulty;
    int sizeX;
    int sizeY;
    int numMines;
    int date;
    //Uncovers a cell.
    void uncover(int x, int y){
        playerBoard[y*sizeX + x] = 'U';
        if (numAdjacentMines(x,y) == 0) {   //Autouncover
            for (int i=0; i<sizeX * sizeY;i++) {
                if (adjacent(i%sizeX, i/sizeX, x, y) && (playerBoard[i] != 'U')) {
                    uncover(i%sizeX, i/sizeX);
                }
            }
        }
    }
    //Checks if two cells are adjaceent, with the given rules.
    bool adjacent (int x1, int y1, int x2, int y2) {
        if (difficulty != 5) { //Normal adjacency rules
            if ((x2-2 < x1) && (x1 < x2+2) && (y2-2 < y1) && (y1 < y2+2)) {
                return true;
            }
        }
        else { //Knightsweeper adjacency rules.
            if ((x1==x2)&&(y1==y2)) {
                return true;
            }
            if (((((x1 == x2-1) || (x1 == x2+1)) && ((y1 == y2-2) || (y1 == y2+2))) || (((y1 == y2-1) || (y1 == y2+1)) && ((x1 == x2-2) || (x1 == x2+2))))) {
                return true;
            }
        }
        return false;
    }
    //Initializes the board by setting it up.
    //ARGUMENTS: The coordinates of the first move the player makes (The set up happens after the first move)
    //Effect: Places mines randomly on the board, except adjacent to the first move.
    void initialize(int x, int y) { //Input parameters are where the first move is made.
        mineBoard = new int [sizeX * sizeY];
        playerBoard = new char [sizeX * sizeY];
        //Initialize the playerBoard;
        for (int i=0; i<sizeX * sizeY;i++){
            playerBoard[i] = 'X';
            mineBoard[i] = 0;
        }
        //We add mines repeatedly.
        int placedMines = 0, newMinePos = 0;
        while (placedMines < numMines) {
            newMinePos = rand()%(sizeX*sizeY);
            //We check if it is too close to the initial move.
            //X coordinate of mine position is newMinePos%sizeX
            //Y coordinate of mine position is newMinePos/sizeX
            if (adjacent(newMinePos%sizeX, newMinePos/sizeX, x, y)) {
                continue;
            }
            //Check if the position is already occupied by a mine.
            else if (mineBoard[newMinePos] == 1) {
                continue;
            }
            mineBoard[newMinePos] = 1;
            placedMines++;
        }
    }
    //Counts the number of mines next to an adjacenet square.
    //Loops through the whole board. Not very scalable, but our game doesn't support massive board sizes anyway.
    int numAdjacentMines(int x, int y) {
        int count = 0;
        for (int i=0; i<sizeX * sizeY;i++){ //Loop accross all cells
            if (adjacent(i%sizeX, i/sizeX, x, y) && mineBoard[i] == 1) {
                count++;
            }
        }
        return count;
    }
    //Prints the board.
    void print_board(){
        //Header that shows a to z and then a line of ----
        cout << "    ";
        for(int i=0;i<sizeX;i++){
            cout << setw(2) << (char)('a'+i);
        }
        cout << endl << "     ";
        for(int i=0;i<sizeX-1;i++){
            cout << "--";
        }
        cout << "-" << endl;
        // Shows the row count.
        for(int j=0;j<sizeY;j++){
            cout << setw(3) << j << '|';
            // Shows the board.
            for (int i=0; i<sizeX;i++){
                char insertedLetter = '0';
                if (playerBoard == NULL) {
                    insertedLetter = '.';
                }
                else if (playerBoard[sizeX*j+i] == 'X'){
                    insertedLetter = '.';
                }
                else if (playerBoard[sizeX*j+i] == 'F'){
                    insertedLetter = 'F';
                }
                else if (playerBoard[sizeX*j+i] == 'U') {
                    insertedLetter = '0' + numAdjacentMines(i,j);
                    if (mineBoard[sizeX*j+i] == 1){
                        insertedLetter = 'M';
                    }
                }
                cout << setw(2) << insertedLetter;
            }
            cout << " |" << j << endl;
        }
        //Shows the --- line and then a to z footer.
        cout << "     ";
        for(int i=0;i<sizeX-1;i++){
            cout << "--";
        }
        cout << "-" << endl << "    ";
        for(int i=0;i<sizeX;i++){
            cout << setw(2) << (char)('a'+i);
        }
        cout << endl;
    }
    void prompt_move(){
        int moveX = -1, moveY = -1;
        string userInput;
        cout << "Please insert a move: " << endl;
        while (moveX == -1 || moveY == -1) {
            cin >> userInput;
            moveX = strToX(userInput, sizeX);
            moveY = strToY(userInput, sizeY);
            if (moveX == -1 || moveY == -1) {
                cout << "Invalid move! Please try again" << endl;
            }
        }
        //If board is not yet initialized, we use the move to initialize the board.
        if (mineBoard == NULL) {
            initialize(moveX, moveY);
        }
        uncover(moveX, moveY);
        print_board();
        prompt_move(); //If game not ended, we prompt.
    }
};

// Takes a user string and returns the X coordinate indicated by the user. If error, return -1.
int strToX(string s, int max){
    int output;
    output = (int) (toupper(s[0])) - (int)('A');
    if ((-1 < output) && (output < max)){
        return output;
    }
    else {
        return -1;
    }
}

// Takes a user string and returns the Y coordinate indicated by the user. If error, return -1.
int strToY(string s, int max){
    int output;
    if (s.length() == 2) {
        output = (int) ((s[1])) - (int)('0');
    }
    else if (s.length() == 3) {
        output = 10*((int) ((s[1])) - (int)('0')) + (int) ((s[2])) - (int)('0');
    }
    else {
        return -1;
    }
    if ((-1 < output) && (output < max)){
        return output;
    }
    return -1;
}

int main(){
    Board b = {
        NULL,
        NULL,
        1,
        16,
        16,
        40,
        0,
    };
    srand(112);
    b.print_board();
    b.prompt_move();
    return 0;
}

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <time.h>
#include <fstream>

using namespace std;

#ifndef main_h
#define main_h

int strToX(string s, int max);
int strToY(string s, int max);
void run_main_menu();

struct Board{
    int * mineBoard;    //stores where the mines are, 1 for cells that have a mine, 0 for cells with no mine.
    char * playerBoard; //stores where the player has checked and flagged,'U' for uncovered, 'F' for flagged 'X' for hidden
    int * moveHistory;
    bool flagMode;
    //Both arrays are stored such that we count the cells from left to right, from the top to bottom.
    //This means the i-th element of each array stores the element with x coordinate: i%sizeX and y coordinate i/sizeX.
    
    int difficulty;     //Int from 1 to 5 determined by game settings. 5 is a special game mode (Knight moves determin adjacency)
    int sizeX;          //The size of the board in the X direction
    int sizeY;          //The size of the board in the Y direction
    int numMines;       //The number of mines in total on the board.
    int seed;           //The seed for srand().
    
    //Function: Uncover
    //Uncovers a cell with coordinates equal to its argument.
    //If there are no adjacent mines, adjacent cells are also uncovered.
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
    //Function: Adjacent
    //Checks if two cells are adjacent. If difficulty is 5, the adjacency rule is cells that are a knight's move from another are adjacent.
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
    //Function: initalize
    //Initializes the board by setting it up both arrays.
    //ARGUMENTS: The coordinates of the first move the player makes (The set up happens after the first move)
    //Effect: Places mines randomly on the board, except adjacent to the first move, and fills the playerBoard with hidden cells.
    void initialize(int x, int y) { //Input parameters are where the first move is made.
        srand(seed);
        mineBoard = new int [sizeX * sizeY];
        playerBoard = new char [sizeX * sizeY];
        moveHistory = new int [32];
        moveHistory[0] = 2;
        moveHistory[1] = 32;
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
    //Function: numAdjacentMines
    //Counts the number of mines next to the cell specified by the argument.
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
    //Function: numAdjacentFlags
    //Counts the number of flags next to the cell specified by the argument.
    //Loops through the whole board. Not very scalable, but our game doesn't support massive board sizes anyway.
    int numAdjacentFlags(int x, int y) {
        int count = 0;
        for (int i=0; i<sizeX * sizeY;i++){ //Loop accross all cells
            if (adjacent(i%sizeX, i/sizeX, x, y) && playerBoard[i] == 'F') {
                count++;
            }
        }
        return count;
    }
    //Function: print_board
    //Prints the board. Still works even if the board is not yet initialized.
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
                //Some colours? May not work on some terminals.
                if (insertedLetter == '1') {
                    cout << "\033[;34m";
                }
                else if (insertedLetter == '2') {
                    cout << "\033[;32m";
                }
                else if (insertedLetter == '3') {
                    cout << "\033[;31m";
                }
                cout << setw(2) << insertedLetter;
                //Return colours back to normal
                if (insertedLetter == '1' || insertedLetter == '2' || insertedLetter == '3') {
                    cout << "\033[0m";
                }
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
    
    void end_game(char decision='n') { 
        string userInput;
        if (decision = 's') {
            saveGame(); //function yet to be defined
            cout << "The game has been saved, you can continue playing it later" << endl;
            cout << "You can finish your game from the main menu \"(2) Load Game\"" << endl;
            cout << "(Press any key to go to the main menu...)"<< endl;
            cin >> userInput;
            run_main_menu();
        
    }
        else {
            cout << "The game is lost... You can start a new game from the main menu!" << endl;
            cout << "(Press any key to go to the main menu...)" << endl;
            cin >> userInput;
            run_main_menu();
        
    }
}
    
    //function prompt_move
    //Prompts the player to make a move, then takes in the move as input.
    //If the move is valid, it sends a call to uncover the specified cell.
    //If the move is invalid, it prompts the user to try again.
    //Yet to be implemented: Flagging calls, fast uncover using flagged cells.
    void prompt_move(){
        int moveX = -1, moveY = -1;
        bool tempFlagMode = false;
        string userInput;
        if (flagMode == false) {
            cout << "Please uncover a cell or type 'q' to quit and save game: " << endl;
        }
        else {
            cout << "Please flag a cell: " << endl;
        }
        while ((moveX == -1 || moveY == -1)) {
            cin >> userInput;
            //Handle different cases now.
            //Toggling Flag Mode:
            if (userInput=="q"){
                end_game('s');
                break;
            }
            
            else if (userInput == "F" || userInput == "f") {
                if (mineBoard == NULL) {
                    cout << "Make a move first before using flag mode!";
                }
                else if (flagMode == false) {
                    cout << "Flag mode turned on!" << endl;
                    flagMode = true;
                }
                else {
                    cout << "Flag mode turned off!" << endl;
                    flagMode = false;
                }
            }
            //Short form flag move. Probably more complicated than it should be.
            else if ((userInput[0] == 'F' || userInput[0] == 'f') && (((toupper(userInput[1])-'A')<26) && ((toupper(userInput[1])-'A')>-1))) {
                //create a temporary string and copy the cell address into it.
                char moveCopy[4];
                for (int i=0; i < 3; i++){
                    moveCopy[i] = userInput[i+1];
                }
                moveCopy[3] = '\0';
                moveX = strToX(moveCopy, sizeX);
                moveY = strToY(moveCopy, sizeY);
                if (moveX == -1 || moveY == -1) {
                    cout << "Invalid move! Please try again" << endl;
                }
                else {
                    flagMode = true;
                    tempFlagMode = true;
                }
            }
            else {
                moveX = strToX(userInput, sizeX);
                moveY = strToY(userInput, sizeY);
                if (moveX == -1 || moveY == -1) {
                    cout << "Invalid move! Please try again" << endl;
                }
            }
        }
        //If board is not yet initialized, we use the move to initialize the board.
        if (mineBoard == NULL) {
            initialize(moveX, moveY);
            uncover(moveX, moveY);
            recordMove (moveX, moveY, false);
            print_board();
        }
        //Cell already uncovered
        else if (playerBoard[moveY*sizeX + moveX] == 'U') {
            //For uncovering cells where the number of adjacent flags is correct.
            if (numAdjacentMines(moveX, moveY) == numAdjacentFlags(moveX, moveY)) {
                int cellsUncovered = 0;
                for (int i=0; i<sizeX * sizeY;i++){ //Loop accross all cells
                    if (adjacent(i%sizeX, i/sizeX, moveX, moveY) && playerBoard[i] == 'X') {
                        uncover(i%sizeX, i/sizeX);
                        recordMove (i%sizeX, i/sizeX, false);
                        cellsUncovered++;
                    }
                }
                //If there's nothing to uncover, we give error message. Else, we print board.
                if (cellsUncovered == 0) {
                    cout << "Cell already uncovered! Please try again." << endl;
                }
                else {
                    print_board();
                }
            }
            else {
            cout << "Cell already uncovered! Please try again." << endl;
            }
        }
        //Regular move
        else if (flagMode == false) {
            if (playerBoard[moveY*sizeX + moveX] == 'F') {
                cout << "Cell is flagged, so can't be uncovered! Please Unflag first." << endl;
            }
            else {
                uncover(moveX, moveY);
                print_board();
                recordMove (moveX, moveY, false);
            }
        }
        //Flag Mode Handling
        else {
            flagMove(moveX, moveY);
            print_board();
            recordMove (moveX, moveY, true);
        }
        //For short-form flag, we turn off flag mode again
        if (tempFlagMode == true) {
            flagMode = false;
        }
        prompt_move(); //If game not ended, we prompt.
    }
    //Function: flagMove
    //Unflags a flagged cell, or flags an unflagged cell.
    void flagMove(int x, int y){
        //If it's flagged, unflag it.
        if (playerBoard[y*sizeX + x] == 'F') {
            playerBoard[y*sizeX + x] = 'X';
        }
        //Else, flag it.
        else if (playerBoard[y*sizeX + x] == 'X') {
            playerBoard[y*sizeX + x] = 'F';
        }
    }
    //Function: recordMove
    //Records the player's move into the array
    void recordMove (int x, int y, bool flag) {
        //0th cell of moveHistory states the cell num we will input the move into
        //1st cell of moveHistory states the size of the array
        //If they are the same, we must expand the array (Dynamic Memory)
        if (moveHistory[0] == moveHistory[1]) {
            int * temp = new int [moveHistory[1] + 32];
            for (int i = 0; i < moveHistory[1]; ++i){
                temp[i] = moveHistory[i];
            }
            delete [] moveHistory;
            moveHistory = temp;
            moveHistory[1] = moveHistory[1] + 32;
        }
        //We code it as follows: Move = 100 * x coordinate + y coordinate
        //If it is not a flag, we add 10,000. If it is a flag, we add 20,000.
        moveHistory[moveHistory[0]] = 10000 + 100*x + y;
        if (flag == true) {
            moveHistory[moveHistory[0]] += 10000;
        }
        moveHistory[0] += 1;
        saveGame(); //Autosave
    }
    //Function: saveGame
    //Saves the board state into a file.
    void saveGame(){
        ofstream fout;
        fout.open("savegame.txt");
        if (fout.fail()){
            cout << "Error writing to file." << endl;
            return;
        }
        fout << difficulty << endl;
        fout << sizeX << endl;
        fout << sizeY << endl;
        fout << numMines << endl;
        fout << seed << endl;
        for (int i=0;i<moveHistory[0];i++){
            fout << moveHistory[i] << endl;
        }
        fout.close();
    }
};


// Takes a user string and returns the X coordinate indicated by the user. If error, return -1.
/*
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
*/
#endif

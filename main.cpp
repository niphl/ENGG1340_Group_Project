//Main Game

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <time.h>
#include <fstream>
#include "main.h"
#include <stdlib.h>

using namespace std;

//Main Menu Functions
void start_new_game();
void run_new_game();
void run_load_game();
void run_rules();
void run_main_menu();

//Loads up the board and starts a new game.
void start_new_game(int difficulty, int SizeX, int SizeY, int numMines) {
    Board b = {
        NULL,       //Mineboard, int array
        NULL,       //Playerboard, char array
        NULL,       //MoveHistory, int array
        false,      //Flagmode, off by default at start
        difficulty, //Difficulty          
        SizeX,      //SizeX
        SizeY,      //SizeY
        numMines,   //Num of Mines
        int(time(0)),    //Seed: use time function
    };
    b.print_board();
    b.prompt_move();
}

//Lets the user pick some settings before starting a new game.
void run_new_game() {
    cout << string(50, '\n');
    cout << "Please choose a difficulty" << endl;
    cout << "Enter (1) for Beginner" << endl;
    cout << "Enter (2) for Intermediate" << endl;
    cout << "Enter (3) for Expert" << endl;
    cout << "Enter (4) for Custom" << endl;
    cout << "Enter (5) for Knight Sweeper special game mode" << endl;
    string userInput;
    bool validInput = false;
    while (validInput == false) {
        cin >> userInput;
        if (userInput == "1" || userInput == "(1)"){
            validInput = true;
            start_new_game(1, 8, 8, 10);
        }
        else if (userInput == "2" || userInput == "(2)"){
            validInput = true;
            start_new_game(2, 16, 16, 40);
        }
        else if (userInput == "3" || userInput == "(3)"){
            validInput = true;
            //We differ a bit from the normal miensweeper of 30x16 to make the display nicer
            start_new_game(3, 26, 18, 99);
        }
        else if (userInput == "4" || userInput == "(4)"){ 
            validInput = true;
            bool validInput2 = false;
            string userInput;
            int sizeX, sizeY, percentageMines;
            
            //input width of custom board, stored in sizeX
            cout << "Please enter the width of the board (6-26): " ;
            while (validInput2 == false){           //loop until we get a valid input
                validInput2 = true; 
                cin >> userInput;
                if (isdigit(userInput[0])) {        //check 1st digit for validity
                    sizeX = userInput[0]-'0';
                }
                else {
                    sizeX = -1;
                    validInput2 = false;
                }
                if (isdigit(userInput[1])) {        //check 2nd digit for validity
                    sizeX *= 10;
                    sizeX += userInput[1]-'0';
                }
                else if (userInput[1] != '\0') {
                    validInput2 = false;
                }
                if ((sizeX < 6) || (sizeX > 26)) {  //check if sizeX is in the right range
                    validInput2 = false;
                }
                if (!validInput2){                  //check if input valid
                    cout << "Invalid input. Please enter a value between 6 and 26: ";
                }
            }
            
            //Take user input and store it in sizeY
            validInput2 = false;
            cout << "Please enter the height of the board (6-30): ";
            while (validInput2 == false){           //loop until we get a valid input
                validInput2 = true; 
                cin >> userInput;
                if (isdigit(userInput[0])) {        //check 1st digit for validity
                    sizeY = userInput[0]-'0';
                }
                else {
                    sizeY = -1;
                    validInput2 = false;
                }
                if (isdigit(userInput[1])) {        //check 2nd digit for validity
                    sizeY *= 10;
                    sizeY += userInput[1]-'0';
                }
                else if (userInput[1] != '\0') {
                    validInput2 = false;
                }
                if ((sizeY < 6) || (sizeY > 26)) {  //check if sizeX is in the right range
                    validInput2 = false;
                }
                if (!validInput2){                  //check if input valid
                    cout << "Invalid input. Please enter a value between 6 and 26: ";
                }
            }
            
            //input percentage of custom board filled with mines, stored in percentageMines
            cout << "Please enter the difficulty of the board from 0 (easiest) to 10 (hardest): ";
            cin >> percentageMines;
            while (percentageMines < 0  || percentageMines > 10) {
                cout << "Incorrect input. Please enter an integer between 0 and 10: ";
                cin >> percentageMines;
            }
            
            int numMines;
            
            if (percentageMines == 0) {
                percentageMines = 5;
            }
            else if (percentageMines == 1) {
                percentageMines = 7;
            }
            else if (percentageMines == 2) {
                percentageMines = 10;
            }
            else if (percentageMines == 3) {
                percentageMines = 13;
            }
            else if (percentageMines == 4) {
                percentageMines = 15;
            }
            else if (percentageMines == 5) {
                percentageMines = 17;
            }
            else if (percentageMines == 6) {
                percentageMines = 20;
            }
            else if (percentageMines == 7) {
                percentageMines = 25;
            }
            else if (percentageMines == 8) {
                percentageMines = 30;
            }
            else if (percentageMines == 9) {
                percentageMines = 40;
            }
            else if (percentageMines == 10) {
                percentageMines = 50;
            }
            
            numMines = percentageMines * sizeY * sizeX  / 100;
            
            start_new_game(4, sizeX, sizeY, numMines);
                
        }
        else if (userInput == "5" || userInput == "(5)"){
            validInput = true;
            int sizeX, sizeY, numMines;
            start_new_game(5, 26, 18, 99);
        }
        else {
            cout << "Invalid User Input. Please try again." << endl;
            cout << "Please choose a difficulty" << endl;
            cout << "Enter (1) for Beginner" << endl;
            cout << "Enter (2) for Intermediate" << endl;
            cout << "Enter (3) for Expert" << endl;
            cout << "Enter (4) for Custom" << endl;
            cout << "Enter (5) for Knight Sweeper special game mode" << endl;
        }
    }
    
}

//Loads a game from our file of saved games
void run_load_game(){
    ifstream fin;
    fin.open("savegame.txt");
    int difficulty, SizeX, SizeY, numMines, Seed, moveHist0, moveHist1, moveHist2, x, count;
    fin >> difficulty >> SizeX >> SizeY >> numMines >> Seed >> moveHist0 >> moveHist1 >> moveHist2;
    if (fin.fail()){
        cout << "Game not found!" << endl;
    }
    else {
        Board b = {
            NULL,       //Mineboard, int array
            NULL,       //Playerboard, char array
            NULL,       //MoveHistory, int array
            false,      //Flagmode, off by default at start
            difficulty, //Difficulty          
            SizeX,      //SizeX
            SizeY,      //SizeY
            numMines,   //Num of Mines
            Seed,       //Seed
        };
        if (moveHist2 >= 20000) {
            moveHist2 -= 20000;
        }
        else {
            moveHist2 -= 10000;
        }
        b.initialize(moveHist2/100, moveHist2%100);
        b.uncover(moveHist2/100,moveHist2%100);
        b.moveHistory[0] = moveHist0;
        b.moveHistory[1] = moveHist1;
        b.moveHistory[2] = moveHist2 + 10000;
        count = 3;
        while (fin >> x) {
            b.moveHistory[count] = x;
            count++;
            if (x >= 20000) {
                x -= 20000;
                b.flagMove(x/100,x%100);
        }
            else {
                x -= 10000;
                b.uncover(x/100,x%100);
            }
        }
        b.print_board();
        b.prompt_move();
        cout << "Game Loaded." << endl;
    }
}

//Explains the rules of the game, via an interactive tutorial
void run_rules(){
    string userInput;
    Board tut = {
        NULL,       //Mineboard, int array
        NULL,       //Playerboard, char array
        NULL,       //MoveHistory, int array
        false,      //Flagmode, off by default at start
        1, //Difficulty          
        8,      //SizeX
        8,      //SizeY
        10,   //Num of Mines
        0,          //Seed
    };
    
    // Page 1
    //tut.print_board();
    cout << string(50, '\n') << "Welcome! Here is a short tutorial on how to play." << endl;
    cout << "(Press any key to continue...)"<< endl;
    cin >> userInput;
    
    // Page 2
    cout << string(50, '\n');
    tut.print_board();
    cout << "On this grid are many dangerous mines, which will explode when uncovered!" << endl;
    cout << "To win, you must uncover every cell of the grid which doesn't have a mine on it." << endl;
    cout << "(Press any key to continue...)"<< endl;
    cin >> userInput;
    
    // Page 3
    cout << string(50, '\n');
    tut.print_board();
    cout << "Let's learn how to uncover a cell."<< endl;    
    cout << "To uncover a cell, type the names of the co-ordinates of the cell, for example, c8."<< endl;
    cout << "Try uncovering the cell c3!"<< endl;
    cout << "(Uncover the cell c3 to continue...)"<< endl;
    userInput = "";
    cin >> userInput;
    while (userInput != "c3" && userInput != "C3") {
        cout << "Type 'c3' to uncover the cell c3."<< endl;
        cin >> userInput;
    }
    
    // Page 4
    tut.initialize(2,3);
    tut.uncover(2,3);
    cout << string(50, '\n');
    tut.print_board();
    cout << "When we uncover a cell, we can see how many mines are adjacent to it by the number on the board."<< endl;    
    cout << "If a cell has no mines are adjacent to it, all adjacent cells will be uncovered too."<< endl;
    cout << "There were no mines next to c4, so a big area has been uncovered!"<< endl;
    cout << "(Press any key to continue...)"<< endl;
    cin >> userInput;
    
    // Page 5
    cout << string(50, '\n');
    tut.print_board();
    cout << "Notice the cell b2. It has 1 mine next to it." << endl;
    cout << "There is only one cell next to b2 that hasn't been uncovered yet, so that one must have the mine." << endl;
    cout << "(Press any key to continue...)..."<< endl;
    cin >> userInput;
    
    // Page 6
    cout << string(50, '\n');
    tut.print_board();
    cout << "Let's flag the cell to remind ourselves there's a mine there." << endl;
    cout << "Type 'f' to change the input mode to flagging mode!" << endl;
    cout << "(Change to flagging mode to continue...)"<< endl;
    userInput = "";
    cin >> userInput;
    while (userInput != "f" && userInput != "F") {
        cout << "Type 'f' to toggle flagging mode."<< endl;
        cin >> userInput;
    }
    
    // Page 7
    cout << string(50, '\n');
    tut.print_board();
    cout << "Great! We are now in flagging mode." << endl;
    cout << "If we try to uncover a cell, it will flag it instead." << endl;
    cout << "Try flagging the cell adjacent to b2 which has a mine!" << endl;
    cout << "(Flag the cell next to b2 with a mine to continue...)"<< endl;
    userInput = "";
    cin >> userInput;
    while (userInput != "c1" && userInput != "C1") {
        if (userInput == "f" || userInput == "F") {
            cout << "Let's unflag the cell first before disabling flag mode." << endl;
        }
        else if ((strToX(userInput, 8) != -1) && (strToY(userInput, 8) != -1)) {
            cout << "Hint: The cell next to b2 with a mine is c1." << endl;
        }
        else {
            cout << "Uncovering a cell in flag mode will flag it instead." << endl;
        }
        cin >> userInput;
    }
    
    // Page 8
    tut.flagMove(2,1);
    cout << string(50, '\n');
    tut.print_board();
    cout << "Now that we have flagged the cell, let's exit flagging mode so we can uncover cells as normal." << endl;
    cout << "If we flag a cell by accident, flagging it again will unflag it." << endl;
    cout << "Type 'f' again to change the input mode back to normal." << endl;
    cout << "(Turn off flagging mode to continue...)"<< endl;
    userInput = "";
    cin >> userInput;
    while (userInput != "f" && userInput != "F") {
        cout << "Type 'f' to toggle flagging mode."<< endl;
        cin >> userInput;
    }
    
    //Page 9
    cout << string(50, '\n');
    cout << "There are 5 games mode: "<< endl;
    cout << "1. Beginner: The easiest level" << endl;
    cout << "The board will of size 8x8 and includes 10 mines" <<endl;
    cout << "(Press any key to continue...)"<< endl;
    cin >> userInput;
    
    //Page 10
    cout << string(50, '\n');
    cout << "2. Intermediate: For an intermediate board" << endl;
    cout << "The board will of size 16x16 and includes 40 mines" << endl;
    cout << "(Press any key to continue...)"<< endl;
    cin >> userInput;
    
    //Page 11
    cout << string(50, '\n');
    cout << "3. Expert: Only for the bravest" << endl;
    cout << "The board will of size 26x18 and includes 99 mines" << endl;
    cout << "(Press any key to continue...)"<< endl;
    cin >> userInput;
    
    //Page 12
    cout << string(50, '\n');
    cout << "4. Custom Board Mode" << endl;
    cout <<"You can define your own board: size and difficulty!" << endl;
    cout << "(Press any key to continue...)"<< endl;
    cin >> userInput;
    
    //Page 13
    cout << string(50, '\n');
    cout << "5. Knight Sweeper special game mode" << endl;
    cout << "Adjacent cells are one knight move away from choosen cell!" <<endl;
    cout << "(Press any key to continue...)"<< endl;
    cin >> userInput;
    
    //Page 14
    cout << string(50, '\n');
    cout << "Let's have a look at the main menu" << endl;
    cout << "The main menu allows you to:" << endl;
    cout << "\"Enter (1) for New Game\" to start a new game" << endl;
    cout << "\"Enter (2) for Load Game\" to play the last unfinished game" << endl; 
    cout << "\"Enter (3) for Tutorial\": You're looking at it now!" << endl;
    cout << "(Press any key to continue...)"<< endl;
    cin >> userInput;
    
    
    //Final Tutorial Page 
    cout << string(50, '\n');
    cout << "You are ready to play now!" << endl;
    cout << "(Press any key to play!)"<< endl;
    cin >> userInput;
    
    //back to main menu
    run_main_menu();
}


void run_main_menu(){
    cout << string(50, '\n');
    cout << "MINESWEEPER TEXT EDITION!!" << endl;
    cout << "Enter (1) for New Game" << endl;
    cout << "Enter (2) for Load Game" << endl;
    cout << "Enter (3) for Tutorial" << endl;
    cout << "Enter (q) to Quit"<< endl;
    string userInput;
    bool validInput = false;
    while (validInput == false) {
        cin >> userInput;
        if (userInput == "1" || userInput == "(1)"){
            validInput = true;
            run_new_game();
        }
        else if (userInput == "2" || userInput == "(2)"){
            validInput = true;
            run_load_game();
        }
        else if (userInput == "3" || userInput == "(3)"){
            validInput = true;
            run_rules();
        }
        else if (userInput == "q" || userInput == "(q)" || userInput == "Q"){
            exit(0);
        }
        else {
            cout << "Invalid User Input. Please try again." << endl;
            cout << "Enter (1) for New Game" << endl;
            cout << "Enter (2) for Load Game" << endl;
            cout << "Enter (3) for Rules/Help" << endl;
            cout << "Enter (q) to Quit"<< endl;
        }
    }
}    

int main(){
    run_main_menu();
}

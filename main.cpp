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
void run_stats();
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
        0,          //Seed
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
    cout << "Enter (4) for Custom (Game stats not saved)" << endl;
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
            string userInput;
            int sizeX, sizeY, numMines;
            cout << "Please enter the width of the board: (4-26)" << endl;
            //Code to take width of the board
            //Must be an int 4-30. Take user input and store it in sizeX. If invalid input, prompt user again.
            cout << "Please enter the height of the board: (4-30)" << endl;
            //Code to take height of the board
            cout << "Please enter the number of mines: (1-255)" << endl;
            //Code to take the number of mines
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
            cout << "Enter (4) for Custom (Game stats not saved)" << endl;
            cout << "Enter (5) for Knight Sweeper special game mode" << endl;
        }
    }
    
}

//Loads a game from our file of saved games
void run_load_game(){
    cout << "Please choose a game to load" << endl;
}

//Shows the stats of our player
void run_stats(){
    int diff1Games, diff2Games, diff3Games, diff5Games;
    int diff1Wins, diff2Wins, diff3Wins, diff5Wins;
    int diff1Cells, diff2Cells, diff3Cells, diff5Cells;
    string userInput;
    //Loading data into our variables
    ifstream fin;
    fin.open("stats.txt");
    if (fin.fail()) {
        cout << "Error: Unable to load stats." << endl;
        cout << "(Press any key to continue...)"<< endl;
        cin >> userInput;
        run_main_menu();
    }
    //Input stats into variables
    cout << string(50, '\n');
    cout << "Enter (R) to reset all stats" << endl;
    cout << "Enter (1) for Beginner stats" << endl;
    cout << "Enter (2) for Intermediate stats" << endl;
    cout << "Enter (3) for Expert stats" << endl;
    cout << "Enter (5) for Knight Sweeper special game mode stats" << endl;
    cout << "Enter (B) to return to main menu" << endl;
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
    //Tutorial not yet complete
    run_main_menu();
}

void run_main_menu(){
    cout << string(50, '\n');
    cout << "MINESWEEPER TEXT EDITION!!" << endl;
    cout << "Enter (1) for New Game" << endl;
    cout << "Enter (2) for Load Game" << endl;
    cout << "Enter (3) for Stats/Game History" << endl;
    cout << "Enter (4) for Tutorial" << endl;
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
            run_stats();
        }
        else if (userInput == "4" || userInput == "(4)"){
            validInput = true;
            run_rules();
        }
        else {
            cout << "Invalid User Input. Please try again." << endl;
            cout << "Enter (1) for New Game" << endl;
            cout << "Enter (2) for Load Game" << endl;
            cout << "Enter (3) for Stats/Game History" << endl;
            cout << "Enter (4) for Rules/Help" << endl;
        }
    }
}    

int main(){
    run_main_menu();
}
//Main Game

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <time.h>

using namespace std;

int strToX(string s, int max);
int strToY(string s, int max);

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

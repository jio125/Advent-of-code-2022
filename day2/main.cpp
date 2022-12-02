//
// Created by Jiovanni Ortiz-Anglero on 12/2/22.
//

#define MY_ROCK 'X'
#define MY_PAPER 'Y'
#define MY_SCISSORS 'Z'
#define OPPONENT_ROCK 'A'
#define OPPONENT_PAPER 'B'
#define OPPONENT_SCISSORS 'C'

#include <iostream>
using std::cout, std::cin, std::endl;
#include <fstream>

int main(){
    //Setup input file
    std::ifstream inFile("input.txt");
    if(inFile.bad()){
        cout << "Cannot open file" << endl;
        return -1;
    }

    char opponentMove, myMove;
    int totalScore = 0;

    inFile >> opponentMove;
    inFile >> myMove;

    while(!inFile.eof()){
        switch (myMove) { //Add points to score according to what I throw
            case MY_ROCK:
                totalScore += 1; //Add 1 to score for rock
                break;
            case MY_PAPER:
                totalScore +=2; //Add 2 to score for paper
                break;
            case MY_SCISSORS:
                totalScore += 3; //Add 3 to score for scissors
                break;
            default:
                break;
        }
        switch (opponentMove) {
            case OPPONENT_ROCK:
                if(myMove == MY_ROCK) totalScore += 3; //Draw case
                else if(myMove == MY_PAPER) totalScore += 6; //Win case
                break;
            case OPPONENT_PAPER:
                if(myMove == MY_PAPER) totalScore += 3; //Draw case
                else if(myMove == MY_SCISSORS) totalScore += 6; //Win case
                break;
            case OPPONENT_SCISSORS:
                if(myMove == MY_SCISSORS) totalScore += 3; //Draw case
                else if(myMove == MY_ROCK) totalScore += 6; //Win case
                break;
            default:
                break;
        }
        inFile >> opponentMove;
        inFile >> myMove;
    }

    cout << "My total score is: " << totalScore << endl;

    return 0;
}
//
// Created by Jiovanni Ortiz-Anglero on 12/2/22.
//

#define MY_ROCK 'X'
#define MY_PAPER 'Y'
#define MY_SCISSORS 'Z'
#define OPPONENT_ROCK 'A'
#define OPPONENT_PAPER 'B'
#define OPPONENT_SCISSORS 'C'
#define LOSE 'X'
#define DRAW 'Y'
#define WIN 'Z'
#define ROCK_SCORE 1
#define PAPER_SCORE 2
#define SCISSOR_SCORE 3
#define WIN_SCORE 6
#define DRAW_SCORE 3

#include <iostream>
using std::cout, std::cin, std::endl;
#include <fstream>
#include <chrono>

int main(){
    //Setup input file
    std::ifstream inFile("input.txt");
    if(!inFile.is_open()){
        cout << "Cannot open file" << endl;
        return -1;
    }

    char opponentMove, myMove;
    int totalScore = 0;

    //Time execution stuff
    auto start1 = std::chrono::steady_clock::now(); //start time

    inFile >> opponentMove;
    inFile >> myMove;

    //Go through the file using the assumed decoding (Puzzle 1)
    while(!inFile.eof()){
        switch (myMove) { //Add points to score according to what I throw
            case MY_ROCK:
                totalScore += ROCK_SCORE; //Add 1 to score for rock
                break;
            case MY_PAPER:
                totalScore +=PAPER_SCORE; //Add 2 to score for paper
                break;
            case MY_SCISSORS:
                totalScore += SCISSOR_SCORE; //Add 3 to score for scissors
                break;
            default:
                break;
        }
        switch (opponentMove) {
            case OPPONENT_ROCK:
                if(myMove == MY_ROCK) totalScore += DRAW_SCORE; //Draw case
                else if(myMove == MY_PAPER) totalScore += WIN_SCORE; //Win case
                break;
            case OPPONENT_PAPER:
                if(myMove == MY_PAPER) totalScore += DRAW_SCORE; //Draw case
                else if(myMove == MY_SCISSORS) totalScore += WIN_SCORE; //Win case
                break;
            case OPPONENT_SCISSORS:
                if(myMove == MY_SCISSORS) totalScore += DRAW_SCORE; //Draw case
                else if(myMove == MY_ROCK) totalScore += WIN_SCORE; //Win case
                break;
            default:
                break;
        }
        inFile >> opponentMove;
        inFile >> myMove;
    }

    auto end1 = std::chrono::steady_clock::now(); //end time
    auto diff1 = end1 - start1;

    cout << "My puzzle 1 total score is: " << totalScore << endl;
    cout << std::chrono::duration<double,std::milli>(diff1).count() << "ms to execute" << endl;

    //Go through the file again using the correct decoding method (Puzzle 2)
    inFile.close();
    inFile.open("input.txt");

    auto start2 = std::chrono::steady_clock::now(); //start time

    //reset variables
    totalScore = 0;
    opponentMove = '\0';
    char outcome;

    inFile >> opponentMove;
    inFile >> outcome;

    while (!inFile.eof()){
        switch (outcome) {
            case WIN:
                totalScore += WIN_SCORE;
                if(opponentMove == OPPONENT_ROCK){
                    totalScore += PAPER_SCORE; //Throw Paper to win
                }
                else if(opponentMove == OPPONENT_PAPER){
                    totalScore += SCISSOR_SCORE; //Throw scissors to win
                }
                else if(opponentMove == OPPONENT_SCISSORS){
                    totalScore += ROCK_SCORE; //Throw Rock to win
                }
                break;
            case DRAW:
                totalScore += DRAW_SCORE;
                if(opponentMove == OPPONENT_ROCK){
                    totalScore += ROCK_SCORE; //Throw Rock to tie
                }
                else if(opponentMove == OPPONENT_PAPER){
                    totalScore += PAPER_SCORE; //Throw paper to tie
                }
                else if(opponentMove == OPPONENT_SCISSORS){
                    totalScore += SCISSOR_SCORE; //Throw scissors to tie
                }
                break;
            case LOSE:
                if(opponentMove == OPPONENT_ROCK){
                    totalScore += SCISSOR_SCORE; //Throw scissors to lose
                }
                else if(opponentMove == OPPONENT_PAPER){
                    totalScore += ROCK_SCORE; //Throw rock to lose
                }
                else if(opponentMove == OPPONENT_SCISSORS){
                    totalScore += PAPER_SCORE; //Throw paper to lose
                }
                break;
            default:
                break;
        }
        inFile >> opponentMove;
        inFile >> outcome;
    }

    auto end2 = std::chrono::steady_clock::now(); //end time
    auto diff2 = end2 - start2;

    cout << endl << "My puzzle 2 total score is: " << totalScore << endl;
    cout << std::chrono::duration<double,std::milli>(diff2).count() << "ms to execute" << endl;

    return 0;
}
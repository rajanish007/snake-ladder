
//Headers
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include <map>
#include <iterator>
#include <stdbool.h>
#include <stdio.h>
#include <string>
#include <limits>

using namespace std;

#define startIndex 0
#define endIndex 100
#define dieFaceCount 6

//Constants
static const int multiplier=1000000;
static const int welcomeSeconds=5*multiplier;
static const int turnSeconds=4*multiplier;
static const int lostMessageSeconds=8*multiplier;

//Game Board Configuration
static map <int, int> snake;
static map <int, int> ladder;
int minScore = 0;
int maxScore = 100;
int botPositionOnBoard = startIndex;
int playerPositionOnBoard = startIndex;
bool botOpened = false;
bool humanOpenend = false;

//Global variables
string playerName;
string botName="COMPUTER";


//Function prototypes
void welcomePlayer();
string getFileContents (ifstream& File);
void printFileContent(string filename);
void sleepDuration(unsigned int duration);
void getPlayerIntro();
bool getPlayerPlayChoice();
void startGame(int tossResult);
void clrscr();
void seeYouLater();
int getRandom();
int toss();
void loadGame();
void humanTurn();
void botTurn();
void gameStatusDisplay();
void game(int dieFaceValue,string player);
void changePlayerPosition(int newPosition);
void changeBotPosition(int newPosition);
void checkSnakeOrLadder(int newPosition,string player);

int main(){

    int tossResult;
    clrscr();
    getPlayerIntro();
    if(getPlayerPlayChoice()){
        welcomePlayer();
        tossResult = toss();
        loadGame();
        cout << tossResult;
        startGame(tossResult);
    }else{
        seeYouLater();
    }
    return 0;
}


void startGame(int tossResult){
    cin.ignore(numeric_limits<streamsize>::max(), '\n' );
    do{
        clrscr();
        gameStatusDisplay();
        if(tossResult){
            humanTurn();
            botTurn();
        }else{
            botTurn();
            humanTurn();
        }
    }while(botPositionOnBoard != maxScore && playerPositionOnBoard != maxScore);
    if(botPositionOnBoard == maxScore){
        printFileContent("computer_win.txt");
        sleepDuration(welcomeSeconds);
        seeYouLater();
    }else{
        printFileContent("human_win.txt");
    }
}

void gameStatusDisplay(){
    printFileContent("game_title.txt");
    cout << playerName << " POSITION : "<< playerPositionOnBoard << endl;
    cout << botName << " POSITION : " << botPositionOnBoard << "\n\n";
    cout <<"------------------------------------------------------------------------------\n";
}

void humanTurn(){
    clrscr();
    int character;
    gameStatusDisplay();
    cout << playerName << " TURN ! \nPress ENTER to roll ! ";
    cin.get(); 
    cin.clear();
    int randomValue = getRandom();
    cout << playerName << " GOT "<< randomValue << " !\n";
    game(randomValue,playerName);
    sleepDuration(turnSeconds);
    return;
}

void botTurn(){
    clrscr();
    gameStatusDisplay();
    cout << botName + " TURN !\n";
    int randomValue = getRandom();
    cout << botName << " GOT "<< randomValue << " !\n\n";
    game(randomValue,botName);
    sleepDuration(turnSeconds);
    return;
}


void game(int dieFaceValue,string player){
    if(botOpened == false && player==botName){
        if(dieFaceValue == dieFaceCount){
            botOpened = true;
            cout << player << " Opened His Piece !\n";
        }else{
            cout << "Try To Get '6' To Open Your Piece !\n";
        }
        return;
    }
    else if(humanOpenend == false && player==playerName){
          if(dieFaceValue == dieFaceCount){
            humanOpenend = true;
            cout << player << " Opened His Piece !\n";
        }else{
            cout << "Try To Get '6' To Open Your Piece !\n";
        }
        return;
    }
    else{
        if(player == playerName){
            int playerNewPosition = dieFaceValue+playerPositionOnBoard;
            changePlayerPosition(playerNewPosition);
            checkSnakeOrLadder(playerNewPosition,player);
        }else{
            int botNewPosition = dieFaceValue+botPositionOnBoard;
            changeBotPosition(botNewPosition);
            checkSnakeOrLadder(botNewPosition,player);
        }
    }
    
}

void changePlayerPosition(int newPosition){
    playerPositionOnBoard = newPosition;
}

void changeBotPosition(int newPosition){
    botPositionOnBoard = newPosition;
}

void checkSnakeOrLadder(int newPosition,string player){
    //If found in snake map
    if(snake.count(newPosition)){
        cout <<player << " Got Bitten By Snake !\n";
        if(player == playerName){
            changePlayerPosition(snake[newPosition]);
        }else{
            changeBotPosition(snake[newPosition]);
        }
    }
    else if(ladder.count(newPosition)){
        cout <<player <<" Got A Ladder !\n";
        if(player == playerName){
            changePlayerPosition(ladder[newPosition]);
        }else{
            changeBotPosition(ladder[newPosition]);
        }
    }
    else{
        if(player == playerName){
            changePlayerPosition(newPosition);
            cout << player << " Moved To Position : "<<playerPositionOnBoard << endl;
        }else{
            changeBotPosition(newPosition);
            cout << player << " Moved To Position : "<<botPositionOnBoard << endl;
        }
    }
}


int toss(){
    clrscr();
    int tossVal =  getRandom();
    int playerFlag;
    if(tossVal % 2 != 0){
        cout << playerName << " won the TOSS, will PLAY first !\n";
        playerFlag = 1;
    }else{
        cout << botName << " won the TOSS, will PLAY first !\n";
        playerFlag = 0;
    }
    sleepDuration(turnSeconds);
    return playerFlag;
}


int getRandom(){
    return ((rand()% dieFaceCount + 1)+(rand()% dieFaceCount + 1)+(rand()% dieFaceCount + 1)) % dieFaceCount + 1;
}

void welcomePlayer(){
    clrscr();
    printFileContent("welcome_letsplay.txt");
    sleepDuration(welcomeSeconds);
}

void getPlayerIntro(){
    clrscr();
    cout << "Enter your Name : ";
    cin >> playerName;
}

bool getPlayerPlayChoice(){
    int choice;
    do{
        clrscr();
        cout << "Hello " << playerName << " ! Are you ready ?(1/0)";
        cin >> choice;
        if(choice == 0){
            return false;
        }
        if(choice == 1){
            return true;
        }
    }while(1);
}


void seeYouLater(){
    clrscr();
    printFileContent("see_you_later.txt");
    sleepDuration(lostMessageSeconds);
}


void loadGame(){
    clrscr();
    cout << "Loading game.....\n";

    snake.insert(pair <int, int> (17,13));

    snake.insert(pair <int, int> (52,29));

    snake.insert(pair <int, int> (57,40));

    snake.insert(pair <int, int> (62,22));

    snake.insert(pair <int, int> (88,16));

    snake.insert(pair <int, int> (95,51));

    snake.insert(pair <int, int> (97,79));
   
    ladder.insert(pair <int, int> (3,21));

    ladder.insert(pair <int, int> (8,30));

    ladder.insert(pair <int, int> (28,84));

    ladder.insert(pair <int, int> (58,77));

    ladder.insert(pair <int, int> (75,86));

    ladder.insert(pair <int, int> (80,100));

    ladder.insert(pair <int, int> (90,91));

    sleepDuration(turnSeconds);
    cout << "Loaded !\n";
    sleepDuration(turnSeconds);
}

void sleepDuration(unsigned int duration){
    usleep(duration);
}

void clrscr(){
    system("clear");
}

void printFileContent(string filename){

    ifstream Reader (filename);             //Open file

    string Art = getFileContents (Reader);       //Get file
    
    cout << Art << endl;               //Print it to the screen

    Reader.close ();                           //Close file
}

string getFileContents (ifstream& File){
    string Lines = "";        //All lines
    
    if (File)                      //Check if everything is good
    {
        while (File.good ())
        {
            string TempLine;                  //Temp line
            getline (File , TempLine);        //Get temp line
            TempLine += "\n";                      //Add newline character
            
            Lines += TempLine;                     //Add newline
        }
        return Lines;
    }
    else                           //Return error
    {
        return "ERROR File does not exist.";
    }
}
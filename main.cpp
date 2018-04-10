
//Headers
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include <map>
#include <vector>
#include <math.h>
#include <iterator>
#include <stdbool.h>
#include <stdio.h>
#include <string>
#include <limits>
#include <random>

//Namespace
using namespace std;

//Defintions
#define startIndex 0
#define endIndex 100
#define dieFaceCount 6

//Constants
static const int multiplier=1000000;
static const int welcomeSeconds=5*multiplier;
static const int turnSeconds=4*multiplier;
static const int lostMessageSeconds=8*multiplier;


//Files
static const string COMPUTER_WIN_FILE = "assets/computer_win.txt";
static const string HUMAN_WIN_FILE = "assets/human_win.txt";

//Game Board Configuration
static map <int, int> snake;
static map <int, int> ladder;

int maxScore = 100;
int botPositionOnBoard = startIndex;
int playerPositionOnBoard = startIndex;
bool botOpened = false;
bool humanOpenend = false;

//Global variables
string playerName;
string botName = "COMPUTER";


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


/**
*Driver Method
*
*/
int main(){

    int tossResult = 0;

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
        }
        else{
            botTurn();
            humanTurn();
        }

    }while(botPositionOnBoard != maxScore && playerPositionOnBoard != maxScore);

    if(botPositionOnBoard == maxScore){
        printFileContent(COMPUTER_WIN_FILE);
        sleepDuration(welcomeSeconds);
        seeYouLater();
    }
    else{
        printFileContent(HUMAN_WIN_FILE);
    }

}

void gameStatusDisplay(){

    printFileContent("assets/game_title.txt");

    cout << playerName << " POSITION : "<< playerPositionOnBoard << endl;
    cout << botName << " POSITION : " << botPositionOnBoard << "\n";
    cout <<"------------------------------------------------------------------------------\n\n\n";
}

void humanTurn(){

    int character;
    int randomValue = getRandom();

    clrscr();   
    gameStatusDisplay();

    cout << playerName << " TURN ! PRESS ENTER TO ROLL ! \n" << endl;
    cin.get(); 
    cin.clear();
    
    cout << playerName << " GOT "<< randomValue << " !\n";

    game(randomValue,playerName);

    sleepDuration(turnSeconds);

}

void botTurn(){

    int randomValue = getRandom();

    clrscr();
    gameStatusDisplay();

    cout << botName + " TURN !\n\n";
    
    cout << botName << " GOT "<< randomValue << " !\n\n";
    game(randomValue,botName);
    sleepDuration(turnSeconds);

}


void game(int dieFaceValue,string player){

    if(botOpened == false && player==botName){

        if(dieFaceValue == dieFaceCount){
            botOpened = true;
            cout << player << " OPENED HIS PIECE !\n";
        }
        else{
            cout << "TRY TO GET '6' TO OPEN YOUR PIECE !\n";
        }
        return;

    }
    else if(humanOpenend == false && player==playerName){

        if(dieFaceValue == dieFaceCount){
            humanOpenend = true;
            cout << player << " OPENED HIS PIECE !\n";
        }
        else{
            cout << "TRY TO GET '6' TO OPEN YOUR PIECE !\n";
        }
        return;
    }
    else{
        if(player == playerName){

            int playerNewPosition = dieFaceValue+playerPositionOnBoard;
            changePlayerPosition(playerNewPosition);
            checkSnakeOrLadder(playerNewPosition,player);
        }
        else{

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

    //If found in snake map, change position as mapped in snake map
    if(snake.count(newPosition)){

        cout <<player << " GOT BITTEN BY SNAKE\n";

        if(player == playerName){
            changePlayerPosition(snake[newPosition]);
        }
        else{
            changeBotPosition(snake[newPosition]);
        }
    }
    //If found in ladder map, change position as mapped in ladder map
    else if(ladder.count(newPosition)){

        cout <<player <<" GOT A LADDER !\n";

        if(player == playerName){
            changePlayerPosition(ladder[newPosition]);
        }
        else{
            changeBotPosition(ladder[newPosition]);
        }
    }
    //move to new position 
    else{

        if(player == playerName){
            changePlayerPosition(newPosition);
            cout << player << " MOVED TO POSITION : "<< playerPositionOnBoard << endl;
        }
        else{
            changeBotPosition(newPosition);
            cout << player << " MOVED TO POSITION : "<< botPositionOnBoard << endl;
        }
    }
}


int toss(){

    int tossVal =  getRandom();
    int playerFlag;

    clrscr();

    if(tossVal % 2 != 0){
        cout << playerName << " WON THE TOSS, WILL PLAY FIRST !\n";
        playerFlag = 1;
    }
    else{
        cout << botName << " WON THE TOSS, WILL PLAY FIRST !\n";
        playerFlag = 0;
    }

    sleepDuration(turnSeconds);

    return playerFlag;
}


int getRandom(){

    // obtain a random number from hardware
    random_device rd; 
    // seed the generator
    mt19937 eng(rd()); 
    // define the range
    uniform_int_distribution<> distr(1, 6);

    return distr(eng);
}

void welcomePlayer(){

    clrscr();
    printFileContent("assets/welcome_letsplay.txt");
    sleepDuration(welcomeSeconds);
}

void getPlayerIntro(){

    clrscr();

    cout << "ENTER YOUR NAME : ";
    cin >> playerName;
}

bool getPlayerPlayChoice(){

    int choice;

    do{
        clrscr();

        cout << "HELLO " << playerName << " ! ARE YOU READY ?(1/0)";
        cin >> choice;

        if(choice == 0){
            return false;
        }
        else if(choice == 1){
            return true;
        }

    }while(1);
}


void seeYouLater(){

    clrscr();
    printFileContent("assets/see_you_later.txt");
    sleepDuration(lostMessageSeconds);
}


void loadGame(){

    clrscr();

    cout << "LOADING GAME....................\n";

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

    cout << "LOADED !\n";

}

void sleepDuration(unsigned int duration){

    usleep(duration);
}

void clrscr(){

    system("clear");
}

void printFileContent(string filename){
    //Open file
    ifstream Reader (filename);             
    //Get file
    string Art = getFileContents (Reader);      
    //Print it to the screen
    cout << Art << endl;               
    //Close file
    Reader.close ();                          
}

string getFileContents (ifstream& File){
    //All lines
    string Lines = "";        
    //Check if everything is good
    if (File)                      
    {
        while (File.good ())
        {
            //Temp line
            string TempLine; 
            //Get temp line                 
            getline (File , TempLine);
            //Add newline character        
            TempLine += "\n";                      
            //Add newline
            Lines += TempLine;                    
        }
        return Lines;
    }
    else                           
    {
        //Return error
        return "ERROR File does not exist.";
    }
}

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

#define startIndex 0;
#define endIndex 100;
#define dieFaceCount 6;

//Constants
static const int multiplier=1000000;
static const int welcomeSeconds=4*multiplier;
static const int turnSeconds=2*multiplier;
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
string botName="Computer";


//Function prototypes
void welcomePlayer();
string getFileContents (ifstream& File);
void printFileContent(string filename);
void sleepDuration(unsigned int duration);
void getPlayerIntro();
bool getPlayerPlayChoice();
void startGame(int tossResult);
void clrscr();
void lost();
int getRandom();
int toss();
void loadGame();
void humanTurn();
void botTurn();
void gameStatusDisplay();
int game(int dieFaceValue);

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
        lost();
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
    }while(botPositionOnBoard != 100 || playerPositionOnBoard != 100);
}

void gameStatusDisplay(){
    printFileContent("game_title.txt");
    cout << playerName << " Position : "<< playerPositionOnBoard << endl;
    cout << botName << " Position : " << botPositionOnBoard << "\n\n";
    cout <<"------------------------------------------------------------------------------\n";
}

void humanTurn(){
    clrscr();
    int character;
    gameStatusDisplay();
    cout << playerName << " Turn ! Press ENTER to roll ! ";
    cin.get(); 
    cin.clear();
    int randomValue = getRandom();
    cout << playerName << " GOT "<< randomValue << " !";
    game(randomValue);
    sleepDuration(turnSeconds);
    return;
}

void botTurn(){
    clrscr();
    gameStatusDisplay();
    cout << botName + " Rolling !\n\n";
    int randomValue = getRandom();
    cout << botName << " GOT "<< randomValue << " !\n\n";
    game(randomValue);
    sleepDuration(turnSeconds);
    return;
}


int game(int dieFaceValue){

    cout << "twinkle twinkle !\n";
}


int toss(){
    clrscr();
    int tossVal =  rand();
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
    return rand() % 6 + 1;
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


void lost(){
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
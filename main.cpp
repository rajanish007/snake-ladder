
//Headers
#include<iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include <map>
#include <iterator>
#include<stdbool.h>

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
void startGame();
void clrscr();
void lost();
int random();
bool toss();

int main(){

    bool tossResult;

    clrscr();
    getPlayerIntro();
    if(getPlayerPlayChoice()){
        welcomePlayer();
        tossResult = toss();
        tossResultDisplay(tossResult);
        loadGame();
        startGame(tossResult);
    }else{
        lost();
    }
    return 0;
}


void startGame(bool tossResult){
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
    cout << playerName + " Position : "+ playerPositionOnBoard << endl;
    cout << botName + " Position : " + botPositionOnBoard << endl;
}

void humanTurn(){
    clrscr();
    cout << playerName+ " Turn ! Press ENTER to roll !\n\n";
    cin.ignore();
    int randomValue = random();
    cout << playerName + " GOT "+ randomValue + " !";
    game(randomValue);
    sleepDuration(turnSeconds);
}

void botTurn(){
    clrscr();
    cout << botName + " Rolling !\n\n";
    sleepDuration(turnSeconds);
    int randomValue = random();
    cout << botName + " GOT "+ randomValue + " !\n\n";
    game(randomValue);
}


int game(int dieFaceValue){

}


void tossResultDisplay(bool tossResult){
    clrscr();
    if(tossResult == true){
        cout << playerName + " won the TOSS, will PLAY first !";
    }else{
        cout << botName + " won the TOSS, will PLAY first !";
    }
}

bool toss(){
    char choiceCharacter;
    do{
        clrscr();
        cout << "Your Call ? (h/t) : ";
        cin >> choiceCharacter;
        fflush(stdin);
        if(choiceCharacter == 'h' || choiceCharacter == 't'){
            break; 
        }
    }while(1);

    int tossVal =  rand() % 100 + 1;
    if(tossVal % 2 == 0 && choiceCharacter == 't'){
        return true;
    }else if(tossVal % 2 == 1 && choiceCharacter == 'h'){
        return true;
    }else{
        return false;
    }
}


int random(){
    do{
        int randomNumber1 =  rand() % 6 + 1;
        int randomNumber2 =  rand() % 6 + 1;
        int randomNumber3 =  rand() % 6 + 1;
        int finalRandom = (randomNumber1+randomNumber2+randomNumber3)/3;
        if(finalRandom >= 1 && finalRandom <= 6){
            return finalRandom;
        }
    }while(1);
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
    char choiceCharacter;
    do{
        clrscr();
        cout << "Hello "+playerName+" ! Are you ready ?(y/n)";
        cin >> choiceCharacter;
        fflush(stdin);
    if(choiceCharacter == 'n'){
        return false;
    }
    if(choiceCharacter == 'y'){
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

string getFileContents (ifstream& File)
{
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
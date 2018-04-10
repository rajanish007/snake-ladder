
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
static const string GAME_TITLE_FILE = "assets/game_title.txt";
static const string SEE_YOU_LATER_FILE = "assets/see_you_later.txt";
static const string WELCOM_LETS_PLAY_FILE = "assets/welcome_letsplay.txt";

//Game Board Configuration
static map <int, int> snake;
static map <int, int> ladder;

int maxScore = 100;
int botPositionOnBoard = startIndex;
int playerPositionOnBoard = startIndex;
bool botOpened = false;
bool humanOpenend = false;
string botName = "COMPUTER";

//Global variables
string playerName;


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
bool terminalConditionReached();
bool ifGotSnake(int currentPosition);
bool ifGotLadder(int currentPosition);
void printUserReference();


/**
*Driver Method : Loaded when program executes
*
*@param 
*@return int
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

/**
*Takes player name to initialize playerName variable
*
*@param 
*@return void
*
*/
void getPlayerIntro(){

    clrscr();

    cout << "ENTER YOUR NAME : ";
    cin >> playerName;
}

/**
*Confirm if user wants to play
*
*@param 
*@return boolean
*
*/
bool getPlayerPlayChoice(){

    char choice;

    do{
        clrscr();

        cout << "HELLO " << playerName << " ! ARE YOU READY ?(y/n)";
        cin >> choice;

        if(choice == 'n'){
            return false;
        }
        else if(choice == 'y'){
            return true;
        }

    }while(1);
}

/**
*Show welcome text
*
*@param 
*@return void
*
*/
void welcomePlayer(){

    clrscr();
    printFileContent(WELCOM_LETS_PLAY_FILE);
    sleepDuration(welcomeSeconds);
}

/**
*Decide who play first
*
*@param 
*@return int
*
*/
int toss(){

    //get random number to set criteria for first play
    int tossVal =  getRandom();
    
    //flag for player who won toss
    int playerFlag;
    char playerChoice;

    do{
        clrscr();
        cout << "YOUR CALL (h/t) : ";
        cin >> playerChoice;

        if(playerChoice == 'h' || playerChoice == 't'){
            break;
        }
    }while(1);
    
    clrscr();

    //if generated number is not even let human player play first
    if(tossVal % 2 != 0 && playerChoice=='t'){
        cout << playerName << " WON THE TOSS, WILL PLAY FIRST !\n";
        playerFlag = 1;
    }
    else if(tossVal % 2 == 0 && playerChoice=='h'){
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

/**
*Game controller, decides who plays first and switch turns.
*terminal condition, when any user reaches 100 position.
*
*@param tossResult
*@return void
*
*/
void startGame(int tossResult){

    //clear input buffers if any
    cin.ignore(numeric_limits<streamsize>::max(), '\n' );

    //Infinite loop
    do{
        clrscr();
        gameStatusDisplay();

        //if human won tos game will switch between human and bot
        if(tossResult){

            if(!terminalConditionReached()){
                  humanTurn();
            }
            else{
                break;
            }
            if(!terminalConditionReached()){
                botTurn();
            }
            else{
                break;
            }
        }
        // if bot won toss game will switch between bot and human
        else{

                if(!terminalConditionReached()){
                    botTurn();
                }
                else{
                    break;
                }
                if(!terminalConditionReached()){
                    humanTurn();
                }
                else{
                    break;
                }
            }

    }while(1);

    //if bot win
    if(botPositionOnBoard == maxScore){

        printFileContent(COMPUTER_WIN_FILE);
        sleepDuration(welcomeSeconds);
        seeYouLater();
    }
    //if human win
    else{
        printFileContent(HUMAN_WIN_FILE);
    }

}

/**
*Human game controller
*
*@param 
*@return void
*
*/
void humanTurn(){

    //human throws die
    int randomValue = getRandom();

    clrscr();   
    gameStatusDisplay();

    cout << playerName << " TURN ! PRESS ENTER TO ROLL ! \n";
    cin.get(); 
    cin.clear();
    
    cout << playerName << " GOT "<< randomValue << " !\n\n";

    //take action based on generated random number
    game(randomValue,playerName);

    sleepDuration(turnSeconds);

}

/**
*Bot game controller
*
*@param 
*@return void
*
*/
void botTurn(){

    // bot throws die
    int randomValue = getRandom();

    clrscr();
    gameStatusDisplay();

    cout << botName + " TURN !\n\n";   
    cout << botName << " GOT "<< randomValue << " !\n\n";

    //take action based on generated random number
    game(randomValue,botName);

    sleepDuration(turnSeconds);

}

/**
*Game logic as algorithm for program
*
*@param dieFaceValue
*@param player
*@return void
*
*/
void game(int dieFaceValue,string player){

    //check if player is bot and has opened his piece by getting 6
    if(botOpened == false && player==botName){

        //if die value is equal to 6 set botOpened flag true
        if(dieFaceValue == dieFaceCount){
            botOpened = true;
            cout << player << " OPENED HIS PIECE !\n";
        }
        else{
            cout << "TRY TO GET '6' TO OPEN YOUR PIECE !\n";
        }
        return;

    }

    //check if player is human and has opened his piece by getting 6
    else if(humanOpenend == false && player==playerName){

        //if die value is equal to 6 set humanOpened flag true
        if(dieFaceValue == dieFaceCount){
            humanOpenend = true;
            cout << player << " OPENED HIS PIECE !\n";
        }
        else{
            cout << "TRY TO GET '6' TO OPEN YOUR PIECE !\n";
        }
        return;
    }

    /*if both has already opened,then
        check player is human or bot
        change players position
        check player got snake or ladder at new position
    */ 
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

/* 
Change Player position on Board
@param newPosition
*/
void changePlayerPosition(int newPosition){

    //set player current position to new position
    if(newPosition > maxScore){
        cout << "Need "<< newPosition-maxScore << " To reach 100 !\n";
    }
    else{
        playerPositionOnBoard = newPosition;
    }
}

/* 
Change Bot position on Board
@param newPosition
 */
void changeBotPosition(int newPosition){

    //set bot current position to new position
    if(newPosition > maxScore){
        cout << "Need "<< newPosition-maxScore << " To reach 100 !\n";
    }
    else{
        botPositionOnBoard = newPosition;
    }
}

/**
*Decides if player got Snake or Ladder or Increment
*
*@param newPosition
*@param player
*@return int
*
*/
void checkSnakeOrLadder(int newPosition,string player){

    //If found in snake map, change position as mapped in snake map
    if(ifGotSnake(newPosition)){

        cout <<player << " GOT BITTEN BY SNAKE !\n";

        if(player == playerName){

            changePlayerPosition(snake[newPosition]);
        }
        else{

            changeBotPosition(snake[newPosition]);
        }
    }
    //If found in ladder map, change position as mapped in ladder map
    else if(ifGotLadder(newPosition)){

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

/**
*Display game status
*
*@param 
*@return void
*
*/
void gameStatusDisplay(){
    printFileContent(GAME_TITLE_FILE);
    printUserReference();
    cout <<"***************************************SCORE BOARD************************************\n";
    cout <<"*                                                                                    *\n";
    cout <<"*                 " << playerName << " POSITION\t\t::\t"<< playerPositionOnBoard <<"                                   *"<<endl;
    cout <<"*                 " <<  botName << " POSITION\t::\t" << botPositionOnBoard << "                                   *"<<endl;
    cout <<"*                                                                                    *\n";
    cout <<"**************************************************************************************\n\n\n";
}

/**
*Random number generator
*
*@param 
*@return int
*
*/
int getRandom(){

    // obtain a random number from hardware
    random_device rd; 
    // seed the generator
    mt19937 eng(rd()); 
    // define the range
    uniform_int_distribution<> distr(1, 6);

    return distr(eng);
}

/*
Show see you later text on console
*/
void seeYouLater(){

    clrscr();
    printFileContent(SEE_YOU_LATER_FILE);
    sleepDuration(lostMessageSeconds);
    clrscr();
}

/**
*Initialize snakes and ladders
*
*@param 
*@return void
*
*/
void loadGame(){

    clrscr();

    cout << "LOADING GAME....................\n";

    //snake <currentPosition, positionAfterSnakeBite>
    snake.insert(pair <int, int> (17,13));

    snake.insert(pair <int, int> (52,29));

    snake.insert(pair <int, int> (57,40));

    snake.insert(pair <int, int> (62,22));

    snake.insert(pair <int, int> (88,16));

    snake.insert(pair <int, int> (95,51));

    snake.insert(pair <int, int> (97,79));
   

    //ladder <currentPosition, positionAfterClimbingLadder>   
    ladder.insert(pair <int, int> (3,21));

    ladder.insert(pair <int, int> (8,30));

    ladder.insert(pair <int, int> (28,84));

    ladder.insert(pair <int, int> (58,77));

    ladder.insert(pair <int, int> (75,86));

    ladder.insert(pair <int, int> (80,99));

    ladder.insert(pair <int, int> (90,91));

    sleepDuration(turnSeconds);

    cout << "LOADED !\n";

}

void printUserReference(){

    cout << "**************************************REFERENCE***************************************\n";
    cout << "*                                        ***                                         *\n";
    cout << "*_________________SNAKES_________________***"<<"_________________LADDERS_________________*\n";
    map <int, int> :: iterator itr1;
    map <int, int> :: iterator itr2;

    itr1 = snake.begin();
    itr2 = ladder.begin();

    for (; itr1 != snake.end(), itr2 != ladder.end() ;)
    {
        cout  <<"*               "<<itr1->first << " -> "<< itr1->second << "                 ***";
        cout  <<"                 "<<itr2->first << " -> "<< itr2->second << "                 *"<<endl;
        
        ++itr1;
        ++itr2;
    }
    cout << "**************************************************************************************\n\n";
}

//Search for currentPosition in Snake map
bool ifGotSnake(int currentPosition){

    map <int, int> :: iterator itr;

    for (itr = snake.begin(); itr != snake.end(); ++itr)
    {
        if((itr->first) == currentPosition){
            return true;
        }
        else{
            return false;
        }
    }
}

//Search for currentPosition in Ladder map
bool ifGotLadder(int currentPosition){

    map <int, int> :: iterator itr;

    for (itr = ladder.begin(); itr != ladder.end(); ++itr)
    {
        if((itr->first) == currentPosition){
            return true;
        }
        else{
            return false;
        }
    }
}

/*
Checks for if any player reached terminal condition
maxScore = 100
*/
bool terminalConditionReached(){

    //Check if any player reached 100th positionAfterClimbingLadder
    if(botPositionOnBoard == maxScore || playerPositionOnBoard == maxScore){
        return true;
    }
    return false;
}

/*
Make running thread sleep for a duration
*/
void sleepDuration(unsigned int duration){

    usleep(duration);
}

/*
Clear screen
*/
void clrscr(){

    system("clear");
}

/**
*Print file contents
*
*@param fileName
*@return void
*
*/
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

/**
*Get file content
*
*@param file as stream
*@return string
*
*/
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
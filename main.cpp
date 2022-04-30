#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "problem.h"
#include <stdlib.h>
#include "search.h"

using namespace std;

//HERE WE WILL DECLARE THE SETUP FOR THE SIZE OF THE GAME
const int rows = 3 ; const int columns = 3;
const int puzzlesize = rows*columns;
//HERE ARE FUNCTIONS THAT WILL BE USED TO SETUP THE TILE PUZZLE, DEFINED AT THE BOTTOM
int gamecreation(vector<int> &startstate);
void makeinitialstate(int selection, vector<int> &startstate);
void makegoalstate(vector<int> &goaltiles);
bool validtiles(vector<int> tiles);
void fillrow(vector<int> &tiles);


//THIS IS WHERE THE CODE BEGINS TO RUN THE WHOLE PUZZLE
int main(){
    vector<int> initialstate = {};
    int solvertype = gamecreation(initialstate);
    //AT THIS POINT WE HAVE THE VECTOR FILLED IN WITH THE VALUES IN ORDER THAT ARE DESIRED FOR INITIAL STATE
    //GOAL STATE WILL BE PART OF EVERY PROBLEM OBJECT FOR QUICK COMPARISON
    //NOW WE HAVE TO CREATE A PROBLEM CLASS OBJECT THAT WILL REPRESENT EACH STATE

    //THIS IS THE INTIIAL STATE HOLDER
    problem* firststate = new problem(initialstate, rows, columns);
    //TODO: MAKE PROBLEM CLASS AND FUNCTIONS TO WORK ON THE PROBLEM CLASS
        //CLASS MADE, FUNCTIONS ALSO DONE
    //TODO: MAKE OPERATORS FOR MOVEMENT
        //OPERATORS ARE PART OF THE PROBLEM CLASS
    //TODO: MAKE FUNCTIONS FOR CALCULATING THE HEURISTICS
        //CALCULATIING AND CREATING NEW CHILD STATES ARE ARE PART OF THE PROBLEM CLASS


    //WE NEED TO ACCOUNT FOR A STATEQUEUE AS WELL, AND A VECTOR OF SOLUTIONS BECAUSE A* CAN HAVE MULTIPLE SOLUTIONS
    //FOR THE EXPANSION, THE PROJECT GUIDE WANTS TO KNOW THE NODES EXPANDED, DEPTH, AND MAXQUEUE SIZE
    vector<problem*> queue;
    vector<problem*> solutionstates;
    int nodesexpanded = 0;
    int solutiondepth = 0;   //solution depth is going to be the same as the gn of the leaf/solution node
    int maxqueuesize = 0;

    //HERE WE WILL RUN THE METHOD CHOSEN AND AS THE METHOD IS BEING RAN WE NEED TO BE PRINTING THE EXPANSION
    //RUNMETHOD1( .... );
    //RUNMETHOD2( .... );
    //RUNMETHOD3( .... );
    if(solvertype == 1){
        UCS(firststate, queue, solutionstates, maxqueuesize, nodesexpanded);
    }
    if(solvertype == 2){
        AMIS(firststate, queue, solutionstates, maxqueuesize, nodesexpanded);
    }
    if(solvertype == 3){
        AEUC(firststate, queue, solutionstates, maxqueuesize, nodesexpanded);
    }

    //WE NEED TO DO THE EXPANSION BETWEEN HERE^^^ AND HEREVVV SO IT WILL GO INSIDE OF THE METHODS BECAUSE 
    //EXPANSION IS DEPENDENT ON THE EXACT METHOD

    //WE NEED TO PRINT THE 3 LAST LINES OF THE CODE FROM TH EPROJECT GUUIDE, ASSUMING ITS FILLED OUT
    cout << "To solve this problem the search algorithm expanded a total of " << nodesexpanded << " nodes.\n";
    cout << "The maximum number of nodes in the queue at any one time: " << maxqueuesize << ".\n";
    cout << "The depth of the goal node was " << solutiondepth <<"."; //the endlines are aleady added from the solution trace print



    //AFTER PRINTING THE EXPANSION, FOR THE EXTRA CREDIT, PRINT THE SOLUTION PATH
    /* COUT "SOLUTION", AND THEN DO A LOOP TO GO THROUGH EACH STATE FROM THE INITIAL STATE TO THE GOAL STATE */
    
    //Assuming that solutionstates vector is holding all the possible solutions() then after sorting them, 
    //the first element will be the best cost sortqueue here, will sort solutionstates
    problem* bestsolution = solutionstates.at(0);
    //then we will fill out a vector that goes from the parent node to the child node for the solution path
    vector<problem*> startendpath={};
    // inserting at the front of the vector each time, NULL is the initial state node's parent
    while(bestsolution != NULL){
        startendpath.insert(startendpath.begin(),bestsolution);
        bestsolution = bestsolution->parent;
    }
    //now startendpath holds the correct path form left to right
    //WE HAVE THE MOVEMENT STRING MEMBER FROM THE PROBLEM OBEJCT CLASS TO HOLD THE MOVEMENT USED TO GET FROM ONE STATE TO THE NEXT
    cout << "\n\nSOLUTION TRACE\n";
    for(int i=1; i < startendpath.size();++i){
        cout << startendpath.at(i)->movement << endl;
    }
    cout << endl;
    startendpath.at(0)->print(); 
    cout << endl << endl;
    for(int i=1; i<startendpath.size();++i){
        cout << startendpath.at(i)->movement << endl;
        startendpath.at(i)->print();
        cout << endl << endl;;
    }



}






//THESE ARE THE FUNCTIONS THAT SETUP THE WHOLE PUZZLE

//THIS CHECKS FOR THE VALIDITY OF THE TILES
bool validtiles(vector<int> tiles){    
    sort(tiles.begin(), tiles.end());
    for(int i = 0; i < puzzlesize; i++){
        if(tiles.at(i)!= i){
            cout << "Invalid Tiles, Try Again\n";
            return false;
        }
    }
    return true;
}

//THIS CREATES THE GOALSTATE, IT WILL BE USED FOR THE PROBLEM/STATE OBJECTS, SO COMPARISON IS QUICK
void makegoalstate(vector<int> &goaltiles){
    for(int i = 1; i < puzzlesize; i++){
        goaltiles.push_back(i);
    }
    //we always want the blank tile to be in the bottom right of the puzzle, so that is the goal
    goaltiles.push_back(0);
}

//THIS FUNCTION CREATES EACH ROW
void fillrow(vector<int> &tiles){
    //this function takes the row inputs and adds it to the tile vector set
    int value;
    do{
        cin >> value;
        tiles.push_back(value);
    }
    while(cin.peek() == ' '); //because we are asking for spaces between the numberes
}

//THIS FUNCTION CREATES THE INITIALSTATE, IT WILL BE USED FOR THE PROBLEM/STATE OBJECTS, AT LEAST FOR
//THE PROBLEM OBJECT THAT WILL BE THE FIRST ONE WE EXPAND FROM
void makeinitialstate(int selection, vector<int> &startstate){
    bool validity = false;
    int value;

    if(selection == 1){
        startstate = {1, 0, 3, 4, 2, 6, 7, 5, 8};
    }
    else if(selection == 2){
        while(!validity){
            startstate = {};
                cout << "Enter tiles with 0 for blank\nEnter first row with spaces between #'s: ";
                fillrow(startstate);
                cout << "Enter second row with spaces between #'s: ";
                fillrow(startstate);
                cout << "Enter third row with spaces between #'s: ";
                fillrow(startstate);
                validity = validtiles(startstate);
            }
    }
}

//THIS FUNCTION SETS UP THE GAME, POPULATING THE VECTOR FOR THE INITIAL STATE AND SELECTING THE DESIRED SOLVING METHOD
int gamecreation(vector<int> &startstate){
    int type = 0;
    bool choosetiles, choosealgo = false;
    
    cout << "Welcome to 862126786 8 puzzle solver." << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    cin >> type;
    
    while(!choosetiles){
        if(type == 1){
            makeinitialstate(1,startstate);
            choosetiles = true;
        }
        else if(type == 2){
            makeinitialstate(2,startstate);
            choosetiles = true;
        }
        else{
            cout << "Invalid Type, Enter type: ";
            cin >> type;
        }
    }
 
    cout << "Enter your choice of algorithm\nUniform Cost Search\n";
    cout << "A* with the Misplaced Tile heuristic\nA* with the Euclidean distance heuristic\n\n";
    cin >> type;

    while(!choosealgo){
        if((type == 1) || (type == 2) || (type == 3)){
            choosealgo = true;
        }
        else{
            cout << "Invalid Method, Enter method: ";
            cin >> type;
        }
    }
    return type;
}
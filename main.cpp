#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//HERE WE WILL DECLARE THE SETUP FOR THE SIZE OF THE GAME
const int rows, columns = 3;
const int tiles = rows*columns;
//HERE ARE FUNCTIONS THAT WILL BE USED TO SETUP THE TILE PUZZLE, DEFINED AT THE BOTTOM
int gamecreation(vector<int> &goalstate, vector<int> &startstate);
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
        //CLASS MADE, FUNCTIONS NOT DONE
    //TODO: MAKE OPERATORS FOR MOVEMENTS
    //TODO: MAKE FUNCTIONS FOR CALCULATING THE HEURISTICS


    //WE NEED TO ACCOUNT FOR A STATEQUEUE AS WELL, AND A VECTOR OF SOLUTIONS BECAUSE A* CAN HAVE MULTIPLE SOLUTIONS
    //FOR THE EXPANSION, THE PROJECT GUIDE WANTS TO KNOW THE NODES EXPANDED, DEPTH, AND MAXQUEUE SIZE
    vector<problem*> queue;
    vector<problem*> solutionstates;
    int nodesexpanded = 0;
    int solutiondepth = 0;
    int maxqueuesize = 0;

    //HERE WE WILL RUN THE METHOD CHOSEN AND AS THE METHOD IS BEING RAN WE NEED TO BE PRINTING THE EXPANSION
    //RUNMETHOD1( .... );
    //RUNMETHOD2( .... );
    //RUNMETHOD3( .... );

    //AFTER PRINTING THE EXPANSION, FOR THE EXTRA CREDIT, PRINT THE SOLUTION PATH
    /* COUT "SOLUTION", AND THEN DO A LOOP TO GO THROUGH EACH STATE FROM THE INITIAL STATE TO THE GOAL STATE */

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
    while(cin.peek() == ' ');
}

//THIS FUNCTION CREATES THE INITIALSTATE, IT WILL BE USED FOR THE PROBLEM/STATE OBJECTS, AT LEAST FOR
//THE PROBLEM OBJECT THAT WILL BE THE FIRST ONE WE EXPAND FROM
void makeinitialstate(int selection, vector<int> &startstate){
    bool validity = false;
    int value;

    if(selection == 1){
        problemBoard = {1, 0, 3, 4, 2, 6, 7, 5, 8};
    }
    else if(selection == 2){
        while(!validity){
            problemBoard = {};
                cout << "Enter tiles with 0 for blank\nEnter first row with spaces between #'s: ";
                fillrow(startstate);
                cout << "Enter second row with spaces between #'s: ";
                fillrow(startstate);
                cout << "Enter third row with spaces between #'s: ";
                fillrow(startstate);
                validity = checkBoardInput(startstate);
            }
    }
}

//THIS FUNCTION SETS UP THE GAME, POPULATING THE VECTOR FOR THE INITIAL STATE AND SELECTING THE DESIRED SOLVING METHOD
int gamecreation(vector<int> &startstate){
    int type = 0;
    bool choosetiles, choosealgo = false;
    
    cout << "Welcome to 862126786 8 puzzle solver." << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    cin >> puzzletype;
    
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
 
    cout << "Enter your choice of algorithm" << endl << "Uniform Cost Search" << endl;
    cout << "A* with the Misplaced Tile heuristic" << endl "A* with the Euclidean distance heuristic" <<endl;
    cout << "Please enter your selection (1/2/3): ";
    cin >> type;

    while(!choosealgo){
        if((type == 1) || (type == 2) || (type == 3)){
            choosealgo = true;
        }
        else{
            cout << "Invalid Method, Enter method: "
            cin >> type;
        }
    }
    return type;
}
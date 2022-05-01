#include "puzzlemake.h"
using namespace std;

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
        startstate = {1, 2, 0, 4, 5, 3, 7, 8, 6};
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
    
    cout << "\nWelcome to 862126786 8 puzzle solver." << endl;
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
 
    cout << "\nEnter your choice of algorithm\nUniform Cost Search\n";
    cout << "A* with the Misplaced Tile heuristic\nA* with the Euclidean distance heuristic\n";
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
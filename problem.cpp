#include "problem.h"
#include "puzzlemake.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;


//I needed to get this kind of function into each problem and main so I just put it in both and changed the name
//normally the 9 would be board size or total tiles but for now im leaving it as 9 for the 8 puzzle
/*void makegoal(vector<int> &goaltiles){
    for(int i = 1; i < 9; i++){
        goaltiles.push_back(i);
    }
    //we always want the blank tile to be in the bottom right of the puzzle, so that is the goal
    goaltiles.push_back(0);
}*/

problem::problem(){
    parent = NULL;
    rows = numrows;
    columns = numcolumns;
    puzzlecnt = rows*columns;
    makegoalstate(currpuzzle);
    makegoalstate(goalpuzzle);
    fn = 0;
    hn = 0;
    gn = 0;
    movement = " ";
}

problem::problem(vector<int> initial, int numrows, int numcolumns){
    parent = NULL;
    rows = numrows;
    columns = numcolumns;
    puzzlecnt = rows*columns;
    fn = 0;
    gn = 0;
    hn = 0;
    movement = " ";
    currpuzzle = initial;
    makegoalstate(goalpuzzle);

}

//THIS IS TO CHECK IF THE NODE THAT WAS JUST POPPED OFF IS THE SOLUTION, SO WE KNOW WHAT
//NODES ARE GOAL NODES, ESPECIALLY FOR A* SINCE APPARENTLY THERE CAN BE MULTIPLE
bool problem::checksolution(){
    for(int i=0; i<puzzlesize; ++i){
        if(currpuzzle.at(i) != goalpuzzle.at(i)){
            return false;
        }
    }
    return true;
}

//THIS FUNCTION IS TO KEEP TRACK OF THE PLACEMENT OF THE BLANK SQUARE FOR MOVEMENT OPTIONS
int problem::getblank(){
    int index;

    for(int i = 0; i < puzzlesize; ++i){
        if(currpuzzle.at(i) == 0){
            index = i;
        }
    }
    return index;
}

//COUNT THE MISPLACED TILES FOR THE MISPLACED METHOD'S HEURISTIC FUNCTION H(N) 
int problem::misplaced(){
    int count = 0;

    for(int i = 0; i < puzzlesize - 1; i++){
        if(currpuzzle.at(i) != goalpuzzle.at(i)){
            count++;
        }
    }
    return count;
}

//CALCULATE THE EUCLIDEAN/MANHATTAN COST FOR A STATE, WHERE YOU COMBINE THE TOTAL DISTANCE
//OF EACH TILE FROM ITS CORRECT LOCATION, IF NOT IN THE RIGHT PLACE
//FORMULA FOR CALCULATIING THIS COST IS SQRT((X1-Y1)^2 + (X2-Y2)^2)
int problem::euclidean(){

    int curval = 0;
    int correct = 0;
    int rowdiff = 0;;
    int coldiff = 0;
    int curro = 0;
    int curcol=0;

    int trow = 0;
    int tcol=0;

    int manhattan=0;
    

    //correct placements for for number 0, 1, 2, 3, 4, 5, 6, 7, 8, 
    //the row for #0 is 3, col for #0 is 3,
    vector<int> royes = {3, 1, 1, 1, 2, 2, 2, 3, 3};
    vector<int> colyes = {3, 1, 2, 3, 1, 2, 3, 1, 2};

    for(int i = 0; i<puzzlesize; ++i){
        if((currpuzzle.at(i) != goalpuzzle.at(i)) && (currpuzzle.at(i) != 0) ){
            //this means that index i is not holding the right number
            curval = currpuzzle.at(i); //pretend #3 is in index 0
            if(i == 0){
                curro = 1; curcol = 1;
            }
            if(i == 1){
                curro = 1; curcol = 2;
            }
            if(i == 2){
                curro = 1; curcol = 3;
            }
            if(i == 3){
                curro = 2; curcol = 1;
            }
            if(i == 4){
                curro = 2; curcol = 2;
            }
            if(i == 5){
               curro = 2; curcol = 3;
            }
            if(i == 6){
               curro = 3; curcol = 1;
            }
            if(i == 7){
                curro = 3; curcol = 2;
            }
            if(i == 8){
                curro = 3; curcol = 3;
            }   

            trow = royes.at(curval); 
            tcol = colyes.at(curval);

            rowdiff = abs(trow - curro);
            coldiff = abs(tcol - curcol);
            //cout << "index: " << i <<"  hn " << rowdiff + coldiff << endl;

            manhattan += rowdiff;
            manhattan += coldiff;
            //cout << "manhattan: " << manhattan <<endl;
    
        }
        else{
            //cout << currpuzzle.at(i) << "is in the right place\n";
        }
    }
    return manhattan;
   
}


problem* problem::moveUp(){
    problem* child = new problem(this->currpuzzle, rows, columns);
    int blank = getblank();

    //DO NOT CREATE A NEW STATE IF THE BLANK IS ALREADY LOCATED ON THE TOP ROW
    if(blank < columns){
        return NULL;
    }
    else{
        //SWAP THE CURRENT PLACEMENT OF BLANK WITH THE INDEX ABOVE IT
        swap(child->currpuzzle.at(blank), child->currpuzzle.at(blank- columns));
        child->parent = this;
        child->gn = this->gn + 1;
        return child;

    }

}

problem* problem::moveLeft(){
    problem* child = new problem(this->currpuzzle, rows, columns);
    int blank = getblank();

    //ILLEGAL MOVEMENT IF THE BLANK IS ALREADY LOCATED ON THE LEFTMOST SIDE OF THE PUZZLE
    if(blank % columns == 0){
        return NULL;
    }
    else{
        //SWAP THE CURRENT PLACEMENT OF BLANK WITH THE INDEX ON ITS LEFT
        swap(child->currpuzzle.at(blank), child->currpuzzle.at(blank - 1));
        child->parent = this;
        child->gn = this->gn + 1;
        return child;
    }

}

//THIS FUNCTION RETURNS A POINTER TO A NEW CHILD PROBLEM OBJECT AFTER BLANK MOVEMENT DOWNWARDS
problem* problem::moveDown(){
    problem* child= new problem(this->currpuzzle, rows, columns);
    int blank = getblank();

    //IF THE BLANK INDEX IS ON THE 3RD ROW, DO NOT CREATE NEW STATE, ILLEGAL MOVEMENT
    if(blank >= (columns*(columns - 1))){
        return NULL;
    }
    else{
        //SWAP THE CURRENT PLACEMENT OF BLANK WITH THE INDEX BELOW IT
        swap(child->currpuzzle.at(blank), child->currpuzzle.at(blank + columns));
        child->parent = this;
        child->gn = this->gn + 1;
        return child;
    }
}


//THIS FUNCTION RETURNS A POINTER TO A NEW CHILD PROBLEM OBJECT AFTER BLANK MOVEMENT TO RIGHT
problem* problem::moveRight(){
    problem* child = new problem(this->currpuzzle, rows, columns);
    int blank = getblank();

    //THIS RETURNS NULL IF THE BLANK IS ALREADY IN THE 3RD COLUMN
    if((blank + 1) % columns == 0){
        return NULL;
    }
    else{
        //SWAP THE CURRENT PLACEMENT OF BLANK WITH THE INDEX ON ITS RIGHT
        swap(child->currpuzzle.at(blank), child->currpuzzle.at(blank + 1));
        child->parent = this;
        child->gn = this->gn + 1;
        return child;
    }
}

//THIS FUNCTION PRINTS A DISPLAY OF THE STATE 
void problem::print(){
    for(int i = 0; i < puzzlesize; ++i){
        if(i % columns == 0){
            cout << endl;
        }
        std::cout << currpuzzle.at(i) << " ";
    }
    //cout << endl;
}
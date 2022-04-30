#include "problem.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

problem::problem(){
    parent = NULL;
    rows = rows;
    columns = columns;
    puzzlesize = tiles;
    makegoalstate(currpuzzle);
    makegoalstate(goalpuzzle);
    fn = 0;
    hn = 0;
    gn = 0;
    movement = " ";
}

problem::problem(vector<int> initial, int rows, int columns){
    parent = NULL;
    rows = rows;
    columns = columns;
    puzzlesize = rows * columns;
    fn = 0;
    gn = 0;
    movement = " ";
    currBoard = initial;
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
    int total;
    int count = 0;
    int X1, Y1;
    int X2, Y2;
    int X3, Y3;
    bool cY, tY = false;

    for(int i = 0; i < puzzlesize; i++){
        if(currpuzzle.at(i) == 0){
            continue;
        }
        else if(currpuzzle.at(i) != goalpuzzle.at(i)){
            X1 = ((i+1) % columns == 0) ? columns : (i + 1) % columns;
            X2 = (currpuzzle.at(i) % columns == 0) ? columns : currpuzzle.at(i) % columns;

            cY = tY = false;

            for(int j = 1; j < rows + 1; j++){
                if((i < j * columns) && !cY){
                    Y1 = j;
                    cY = true;
                }
                if((currpuzzle.at(i) < j * columns) && !tY){
                    Y2 = j;
                    tY = true;
                }
            }

            X3 = X1 - X2;
            Y3 = Y1 - Y2;

            X3 = abs(X3);
            Y3 = abs(Y3);

            total = sqrt(pow(X3, 2) + pow(Y3, 2));

            count += total;
        }
    }
    return count;
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
        cout << currpuzzle.at(i) << ' ';
    }
    cout << endl;
}
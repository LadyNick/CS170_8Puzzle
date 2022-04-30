#include "problem.h"
using namespace std;

//THIS FILE HOLDS THE DIFFERENT SEARCHING SOLVING METHODS
//UCS
void UCS(problem* node, vector<problem*> &queue, vector<problem*> &solutionstates, int &maxqueuesize, int &nodesexpanded){

    //this will capture the max size the queue ever was, for the last 3 lines of the trace
    if(queue.size() > maxqueuesize){ maxqueuesize = queue.size();}
    //we do not want the queue to be empty, its illegal or invalid or something from lecture
    if(queue.empty()){return;}
    //Every loop, we take the the frontier of the queue, and pop the node before expansion
    queue.erase(queue.begin());
    //after popping the frontier of the node, we ask the state, are you the solution?
    if(node->checksolution){solutions.push_back(initial_state); return;}

    //This is where we create new child nodes moving the blank in every possible direction
    //The movemenet functions handle cases where the blank is unable to move in illegal directions
    //Here is where we increment the # of nodes expanded, after we know that the solution(s) haven't been found yet
    ++nodesexpanded;
    problem* up = node->moveUp();
    problem* down = node->moveDown();
    problem* left = node->moveLeft();
    problem* right = node->moveRight();

    if(up != NULL){
        up->movement = "Move Up";
        up->parent = node;
        up->fn = up->gn;
        queue.push_back(up);
    }
    if(down != NULL){
        down->movement = "Move Down";
        down->parent = node;
        down->fn = down->gn;
        queue.push_back(down);
    }
    if(left != NULL){
        left->movement = "Move Left";
        left->parent = node;
        left->fn = left->gn;
        queue.push_back(left);
    }
    if(right != NULL){
        right->movement = "Move Right";
        right->parent = node;
        right->fn = right->gn;
        queue.push_back(right);
    }
    arrangequeue(queue);

    UCS(queue.at(0), queue, solutionstates, maxqueuesize, nodesexpanded);
}


//This function sorts the queue from lowest cost to highest cost and it is useful because we always 
//want to be expanding the node with the lowest cost
void arrangequeue(vector<problem*> &queue){

    for(int i = 0; i<queue.size(); ++i){
        //reset min index and cost, since we are going to be findinging th nth min every time
        //and placing the nth mins in the order of ascending indexes
        int mini= i;
        int minfn = queue.at(i)->fn;

        for(int k = i; k<queue.size(); ++k){
            if(queue.at(k)->fn < minfn){
                minfn = queue.at(k)->fn;
                mini = k;
            }
        }
        //put the nth min into the ith index
        problem* curr = queue.at(i);
        queue.at(i) = statequeue.at(mini);
        statequeue.at(mini) = curr;
    }
}

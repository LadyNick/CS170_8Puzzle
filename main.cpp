#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "problem.h"
#include "search.h"
#include "puzzlemake.h"
#include <stdlib.h>

using namespace std;


//THIS IS WHERE THE CODE BEGINS TO RUN THE WHOLE PUZZLE
int main(){
    vector<int> initialstate;
    int solvertype = gamecreation(initialstate);
    //AT THIS POINT WE HAVE THE VECTOR FILLED IN WITH THE VALUES IN ORDER THAT ARE DESIRED FOR INITIAL STATE
    //GOAL STATE WILL BE PART OF EVERY PROBLEM OBJECT FOR QUICK COMPARISON
    //NOW WE HAVE TO CREATE A PROBLEM CLASS OBJECT THAT WILL REPRESENT EACH STATE

    //THIS IS THE INTIIAL STATE HOLDER
    problem* firststate = new problem(initialstate, numrows, numcolumns);
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
    vector<problem*> repeatedstates;
    queue.push_back(firststate);
    repeatedstates.push_back(firststate);
    int nodesexpanded = 0;
    int solutiondepth = 0;   //solution depth is going to be the same as the gn of the leaf/solution node
    int maxqueuesize = 0;
    //int poss = 0;

    //HERE WE WILL RUN THE METHOD CHOSEN AND AS THE METHOD IS BEING RAN WE NEED TO BE PRINTING THE EXPANSION
    //RUNMETHOD1( .... );
    //RUNMETHOD2( .... );
    //RUNMETHOD3( .... );
    if(solvertype == 1){
        UCS(firststate, queue, solutionstates, maxqueuesize, nodesexpanded, repeatedstates);
        //cout << "\nUCS\n";
    }
    if(solvertype == 2){
        AMIS(firststate, queue, solutionstates, maxqueuesize, nodesexpanded, repeatedstates);
        //cout << "\nAMIS\n";
    }
    if(solvertype == 3){
        AEUC(firststate, queue, solutionstates, maxqueuesize, nodesexpanded, repeatedstates /*poss*/);
        //cout << "\nAEUC\n";
    }

    if(!solutionstates.size()){ 
        cout<< "\n\nTHIS PUZZLE IS IMPOSSIBLE TO SOLVE" <<endl;
    }
    else{

    //WE NEED TO DO THE EXPANSION BETWEEN HERE^^^ AND HEREVVV SO IT WILL GO INSIDE OF THE METHODS BECAUSE 
    //EXPANSION IS DEPENDENT ON THE EXACT METHOD
    arrangequeue(solutionstates);
    solutiondepth = solutionstates.at(0)->gn;
    //WE NEED TO PRINT THE 3 LAST LINES OF THE CODE FROM TH EPROJECT GUUIDE, ASSUMING ITS FILLED OUT
    cout << "\nTo solve this problem the search algorithm expanded a total of " << nodesexpanded << " nodes.\n";
    cout<< "**Node #" << nodesexpanded+1 << " we look at is the solution node.";
    cout << "The maximum number of nodes in the queue at any one time: " << maxqueuesize << ".\n";
    cout << "The depth of the goal node was " << solutiondepth <<"."; //the endlines are aleady added from the solution trace print

    //AFTER PRINTING THE EXPANSION, FOR THE EXTRA CREDIT, PRINT THE SOLUTION PATH
    /* COUT "SOLUTION", AND THEN DO A LOOP TO GO THROUGH EACH STATE FROM THE INITIAL STATE TO THE GOAL STATE */
    //arrangequeue(solutionstates);
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
    cout<< "\nInitial";
    startendpath.at(0)->print(); 
    cout << endl << endl;
    for(int i=1; i<startendpath.size();++i){
        cout << startendpath.at(i)->movement;
        startendpath.at(i)->print();
        cout << endl << endl;;
    }
    cout<< "GOAL REACHED";

    //cout<< endl << poss << endl;

    //cout<< "Total unique states: " << repeatedstates.size();
}


}

#include "problem.h"
using namespace std;

void arrangequeue(vector<problem*> &queue);

//THIS FILE HOLDS THE DIFFERENT SEARCHING SOLVING METHODS
//UCS
void UCS(problem* node, vector<problem*> &queue, vector<problem*> &solutionstates, int &maxqueuesize, int &nodesexpanded, vector<problem*> &repeatedstates){
    //According to the project guide, we put expanding state and print the root node, only for the root node's expansion
    if(node->parent == NULL){cout << "\nExpanding state";
    node->print();}
    //cout << "\n\n";
    //this will capture the max size the queue ever was, for the last 3 lines of the trace
    if(queue.size() > maxqueuesize){ maxqueuesize = queue.size();}
    //we do not want the queue to be empty, its illegal or invalid or something from lecture
    //cout << "this3";
    if(queue.empty()){return;}
    //cout << "this4";
    //Every loop, we take the the frontier of the queue, and pop the node before expansion
    queue.erase(queue.begin());
    //after popping the frontier of the node, we ask the state, are you the solution?
    if(node->checksolution()){solutionstates.push_back(node); return;}
    //cout<<"gets to here 1";
    if(node->parent !=NULL){
    cout << "\tExpanding this node...\n\n";}
    else{ cout << endl << endl;}


    //This is where we create new child nodes moving the blank in every possible direction
    //The movemenet functions handle cases where the blank is unable to move in illegal directions
    //Here is where we increment the # of nodes expanded, after we know that the solution(s) haven't been found yet
    ++nodesexpanded;
    //cout << "expanded nodes" << nodesexpanded << endl;
    problem* up = node->moveUp();
    problem* down = node->moveDown();
    problem* left = node->moveLeft();
    problem* right = node->moveRight();
    bool upb; bool downb; bool leftb; bool rightb;
    upb = downb = leftb = rightb = false;

    if(up != NULL){
        up->movement = "Move Up";
        up->parent = node;
        up->fn = up->gn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(up->currpuzzle == repeatedstates.at(i)->currpuzzle){
                upb = true;
                //./acout << "already exists\n";
            }
        }
        if(!upb){
        repeatedstates.push_back(up);
        queue.push_back(up);}
    }
    if(down != NULL){
        down->movement = "Move Down";
        down->parent = node;
        down->fn = down->gn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(down->currpuzzle == repeatedstates.at(i)->currpuzzle){
                downb = true;
                //cout << "already exists\n";
            }
        }
        if(!downb){
        repeatedstates.push_back(down);
        queue.push_back(down);}
    }
    if(left != NULL){
        left->movement = "Move Left";
        left->parent = node;
        left->fn = left->gn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(left->currpuzzle == repeatedstates.at(i)->currpuzzle){
                leftb = true;
                //cout << "already exists\n";
            }
        }
        if(!leftb){
        repeatedstates.push_back(left);
        queue.push_back(left);}
    }
    if(right != NULL){
        right->movement = "Move Right";
        right->parent = node;
        right->fn = right->gn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(right->currpuzzle == repeatedstates.at(i)->currpuzzle){
                rightb = true;
                //cout << "already exists\n";

            }
        }
        if(!rightb){
        repeatedstates.push_back(right);
        queue.push_back(right);}
    }
    //cout << "gets to here2";
    arrangequeue(queue);
    //After the queue is rearranged so the costs of the nodes are ascending, the problem state at index
    //0 will be the next node to be expanded so we pass that in after printing out the expansion trace into
    //the UCS function again for recursion

    cout << "The best state to expand with g(n) = " << queue.at(0)->gn << " and h(n) = ";
    cout << queue.at(0)->hn << " is...";
    queue.at(0)->print();
    UCS(queue.at(0), queue, solutionstates, maxqueuesize, nodesexpanded, repeatedstates);
}


//The A* with Misplaced tile heuristic will go here
void AMIS(problem* node, vector<problem*> &queue, vector<problem*> &solutionstates, int &maxqueuesize, int &nodesexpanded, vector<problem*> &repeatedstates){
    //According to the project guide, we put expanding state and print the root node, only for the root node's expansion
    if(node->parent == NULL){cout << "\nExpanding state";
    node->print();}
    //cout << "\n\n";
    //this will capture the max size the queue ever was, for the last 3 lines of the trace
    if(queue.size() > maxqueuesize){ maxqueuesize = queue.size();}
    //we do not want the queue to be empty, its illegal or invalid or something from lecture
    //cout << "this3";
    if(queue.empty()){return;}
    //cout << "this4";
    //Every loop, we take the the frontier of the queue, and pop the node before expansion
    queue.erase(queue.begin());
    //after popping the frontier of the node, we ask the state, are you the solution?
    if(node->checksolution()){solutionstates.push_back(node); return;}
    //cout<<"gets to here 1";
    if(node->parent !=NULL){
    cout << "\tExpanding this node...\n\n";}
    else{ cout << endl << endl;}

    //This is where we create new child nodes moving the blank in every possible direction
    //The movemenet functions handle cases where the blank is unable to move in illegal directions
    //Here is where we increment the # of nodes expanded, after we know that the solution(s) haven't been found yet
    ++nodesexpanded;
    //cout << "expanded nodes" << nodesexpanded << endl;
    problem* up = node->moveUp();
    problem* down = node->moveDown();
    problem* left = node->moveLeft();
    problem* right = node->moveRight();
    bool upb; bool downb; bool leftb; bool rightb;
    upb = downb = leftb = rightb = false;

    if(up != NULL){
        up->movement = "Move Up";
        up->parent = node;
        up->hn = up->misplaced();
        up->fn = up->gn + up->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(up->currpuzzle == repeatedstates.at(i)->currpuzzle){
                upb = true;
                //cout << "already exists\n";
                //repeatedstates.at(i)->print();
                cout<< endl;
            }
        }
        if(!upb){
        repeatedstates.push_back(up);
        queue.push_back(up);}
    }
    if(down != NULL){ 
        down->movement = "Move Down";
        down->parent = node;
        down->hn = down->misplaced();
        down->fn = down->gn + down->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(down->currpuzzle == repeatedstates.at(i)->currpuzzle){
                downb = true;
                //cout << "already exists\n";
                //repeatedstates.at(i)->print();
                cout<< endl;
            }
        }
        if(!downb){
        repeatedstates.push_back(down);
        queue.push_back(down);}
    }
    if(left != NULL){
        left->movement = "Move Left";
        left->parent = node;
        left->hn = left->misplaced();
        left->fn = left->gn + left->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(left->currpuzzle == repeatedstates.at(i)->currpuzzle){
                leftb = true;
                //cout << "already exists\n";
                //repeatedstates.at(i)->print();
                cout<< endl;
            }
        }
        if(!leftb){
        repeatedstates.push_back(left);
        queue.push_back(left);}
    }
    if(right != NULL){
        right->movement = "Move Right";
        right->parent = node;
        right->hn = right->misplaced();
        right->fn = right->gn + right->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(right->currpuzzle == repeatedstates.at(i)->currpuzzle){
                rightb = true;
                //cout << "already exists\n";
                //repeatedstates.at(i)->print();
                cout<< endl;
            }
        }
        if(!rightb){
        repeatedstates.push_back(right);
        queue.push_back(right);}
    }
    arrangequeue(queue);
    //After the queue is rearranged so the costs of the nodes are ascending, the problem state at index
    //0 will be the next node to be expanded so we pass that in after printing out the expansion trace into
    //the UCS function again for recursion

    cout << "The best state to expand with g(n) = " << queue.at(0)->gn << " and h(n) = ";
    cout << queue.at(0)->hn << " is...";
    queue.at(0)->print();
    AMIS(queue.at(0), queue, solutionstates, maxqueuesize, nodesexpanded, repeatedstates);
}

//THE A* with euclidean/manhattan heuristic will go here
void AEUC(problem* node, vector<problem*> &queue, vector<problem*> &solutionstates, int &maxqueuesize, int &nodesexpanded, vector<problem*> &repeatedstates/*, int &poss*/){
    //According to the project guide, we put expanding state and print the root node, only for the root node's expansion
    if(node->parent == NULL){cout << "\nExpanding state";
    node->print();}
    //cout << "\n\n";
    //this will capture the max size the queue ever was, for the last 3 lines of the trace
    if(queue.size() > maxqueuesize){ maxqueuesize = queue.size();}
    //we do not want the queue to be empty, its illegal or invalid or something from lecture
    //cout << "this3";
    if(queue.empty()){return;}
    //cout << "this4";
    //Every loop, we take the the frontier of the queue, and pop the node before expansion
    queue.erase(queue.begin());
    //after popping the frontier of the node, we ask the state, are you the solution?
    if(node->checksolution()){solutionstates.push_back(node); return;}
    //cout<<"gets to here 1";
    if(node->parent !=NULL){
    cout << "\tExpanding this node...\n\n";}
    else{ cout << endl << endl;}

    //This is where we create new child nodes moving the blank in every possible direction
    //The movemenet functions handle cases where the blank is unable to move in illegal directions
    //Here is where we increment the # of nodes expanded, after we know that the solution(s) haven't been found yet
    ++nodesexpanded;
    //cout << "expanded nodes" << nodesexpanded << endl;
    problem* up = node->moveUp();
    problem* down = node->moveDown();
    problem* left = node->moveLeft();
    problem* right = node->moveRight();
    bool upb; bool downb; bool leftb; bool rightb;
    upb = downb = leftb = rightb = false;

    if(up != NULL){
        //++poss;
        up->movement = "Move Up";
        up->parent = node;
        up->hn = up->euclidean();
        up->fn = up->gn + up->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(up->currpuzzle == repeatedstates.at(i)->currpuzzle){
                //cout << "already exists\n";
                upb = true;
            }
        }
        if(!upb){
        repeatedstates.push_back(up);
        queue.push_back(up);}
    }
    if(down != NULL){
        //++poss;
        down->movement = "Move Down";
        down->hn = down->euclidean();
        down->parent = node;
        down->fn = down->gn + down->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(down->currpuzzle == repeatedstates.at(i)->currpuzzle){
                //cout << "already exists\n";
                downb = true;
            }
        }
        if(!downb){
        repeatedstates.push_back(down);
        queue.push_back(down);}
    }
    if(left != NULL){
        //++poss;
        left->movement = "Move Left";
        left->parent = node;
        left->hn = left->euclidean();
        left->fn = left->gn + left->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(left->currpuzzle == repeatedstates.at(i)->currpuzzle){
                //cout << "already exists\n";
                leftb = true;
            }
        }
        if(!leftb){
        repeatedstates.push_back(left);
        queue.push_back(left);}
    }
    if(right != NULL){
        //++poss;
        right->movement = "Move Right";
        right->parent = node;
        right->hn = right->euclidean();
        right->fn = right->gn + right->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(right->currpuzzle == repeatedstates.at(i)->currpuzzle){
                //cout << "already exists\n";
                rightb = true;
            }
        }
        if(!rightb){
        repeatedstates.push_back(right);
        queue.push_back(right);}
    }
    arrangequeue(queue);
    //After the queue is rearranged so the costs of the nodes are ascending, the problem state at index
    //0 will be the next node to be expanded so we pass that in after printing out the expansion trace into
    //the UCS function again for recursion

    cout << "The best state to expand with g(n) = " << queue.at(0)->gn << " and h(n) = ";
    cout << queue.at(0)->hn << " is...";
    queue.at(0)->print();
    AEUC(queue.at(0), queue, solutionstates, maxqueuesize, nodesexpanded, repeatedstates/*, poss*/);
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
        queue.at(i) = queue.at(mini);
        queue.at(mini) = curr;
    }
}

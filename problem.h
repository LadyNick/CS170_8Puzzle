#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include "main.cpp"
using namespace std;

class problem{
    private:
        //vector holding current state values in order
        vector<int> currpuzzle;
        //vector holding the values in goal order, same for every problem object
        vector<int> goalpuzzle;
        //size elements that determine if its a 8 puzzle, 15 puzzle, etc..
        int rows;
        int columns;
        int puzzlesize;
    public:
        //constructors
        problem();
        problem(std::vector<int> initial, int rows, int columns);
        //deconstructor
        ~problem();
        //parent pointer for leaf nodes to link to their parent nodes, will be used for solution path
        problem* parent;           
        int getblank();
        bool checksolution();
        //functions for creating child nodes based on movement
        problem* moveUp();
        problem* moveDown();
        problem* moveLeft();
        problem* moveRight();
        //functions that calculate heuristic costs, g(n) will be distance from the initial node
        int misplaced();
        int euclidean();
        //function that prints the state in a row x column display
        void print();
        void frontier(std::vector<problem*> &statequeue);
        //variables holding values for f(n) h(n) and g(n)
        double fn;           
        double hn;           
        double gn;
        //this string holds the movement, will be used for printing solution path
        string movement;
};

#endif
#ifndef __PUZZLEMAKE_H__
#define __PUZZLEMAKE_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
using namespace std;

//HERE WE WILL DECLARE THE SETUP FOR THE SIZE OF THE GAME
const int numrows = 3 ; 
const int numcolumns = 3;
const int puzzlesize = numrows*numcolumns;
//HERE ARE FUNCTIONS THAT WILL BE USED TO SETUP THE TILE PUZZLE, DEFINED AT THE BOTTOM
int gamecreation(vector<int> &startstate);
void makeinitialstate(int selection, vector<int> &startstate);
void makegoalstate(vector<int> &goaltiles);
bool validtiles(vector<int> tiles);
void fillrow(vector<int> &tiles);

#endif
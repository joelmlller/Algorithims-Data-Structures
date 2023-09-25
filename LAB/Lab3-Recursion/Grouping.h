/*
 * Name: Joel Miller
 * Date Submitted: 02/12/2023
 * Lab Section: 004
 * Assignment Name: Lab3 Recursion
 */

#pragma once

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Represents an occupied square in the grid
//Do not modify the GridSquare class or its member functions
class GridSquare
{
    private:
        int row, col;
    public:
        GridSquare(); //Default constructor, (0,0) square
        GridSquare(int r, int c); //(r,c) square
        //Compare with == operator, used in test cases
        bool operator== (const GridSquare r) const;
        int getRow(); //return row value
        int getCol(); //return column value
        //Output using << operator, used in Grouping::printGroups()
        friend ostream& operator<< (ostream& os, const GridSquare obj);
};




class Grouping
{
    private:
        int grid[10][10]; //Holds the input grid
        vector<vector<GridSquare>> groups; //Each element in this vector is a group of GridSquare objects
        //Private recursive helper function
        void findGroup(int row, int col);

    public:
        Grouping(); //Default constructor, no groups
        Grouping(string fileName); //Reads file into the grid and finds groups
        void printGroups(); //Displays grid's groups of squares
        vector<vector<GridSquare>> getGroups(); //Needed in unit tests
};
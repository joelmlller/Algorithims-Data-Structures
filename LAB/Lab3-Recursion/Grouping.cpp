/*
 * Name: Joel Miller
 * Date Submitted: 02/12/2023
 * Lab Section: 004
 * Assignment Name: Lab3 Recursion
 */

#include "Grouping.h"


GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{},groups() {} //Default constructor, no groups

void Grouping::printGroups() //Displays grid's groups of squares
{
    for(int g=0; g<groups.size(); g++)
    {
        cout << "Group " << g+1 << ": ";
        for(int s=0; s<groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}



Grouping::Grouping(string filename)
    : grid{}, groups{}
{
    ifstream file(filename);
    if (file.is_open())
    {
        for (int row = 0; row < 10; row++)
        {
            for (int col = 0; col < 10; col++)
            {
                char c;
                file >> c;
                grid[row][col] = (c == '.') ? 0 : 1;
            }
        }
        file.close();

        for (int row = 0; row < 10; row++)
        {
            for (int col = 0; col < 10; col++)
            {
                if (grid[row][col] == 1)
                {
                    groups.push_back(vector<GridSquare>());
                    findGroup(row, col);
                }
            }
        }
    }
}

void Grouping::findGroup(int row, int col)
{
    if (row < 0 || row >= 10 || col < 0 || col >= 10)
    {
        return;
    }

    if (grid[row][col] == 0)
    {
        return;
    }

    grid[row][col] = 0;
    groups[groups.size() - 1].push_back(GridSquare(row, col));
    
    findGroup(row - 1, col);
    findGroup(row + 1, col);
    findGroup(row, col - 1);
    findGroup(row, col + 1);
}
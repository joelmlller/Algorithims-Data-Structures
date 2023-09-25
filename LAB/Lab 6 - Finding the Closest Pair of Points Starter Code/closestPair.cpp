/*
 * Name: Joel Miller
 * Date Submitted: 03/13/2023
 * Lab Section: 01
 * Assignment Name: Closest Pair of Points
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

struct point
{
    double x;
    double y;
};

/*Implement the following function
  Reads in a file specified by the parameter
  Format of file: #of points on first line
                  remaining (#of points) lines: x-value and y-value of point
                  one point per line
                  x-value and y-value are double-precision values and
                  bounded by the unit square 0.0 <= x,y < 1.0
  Should use "spatial hashing" where the #of cells scales with the #of points
  and find the distance between the closest pair of points which will be
  returned as a double type value
*/
double closestPair(string filename);

/*int main()
{
    double min;
    string filename;
    cout << "File with list of points within unit square: ";
    cin >> filename;
    min = closestPair(filename);
    cout << setprecision(16);
    cout << "Distance between closest pair of points: " << min << endl;
    return 0;
}*/




/*Implement the following function
  Reads in a file specified by the parameter
  Format of file: #of points on first line
                  remaining (#of points) lines: x-value and y-value of point
                  one point per line
                  x-value and y-value are double-precision values and
                  bounded by the unit square 0.0 <= x,y < 1.0
  Should use "spatial hashing" where the #of cells scales with the #of points
  and find the distance between the closest pair of points which will be
  returned as a double type value
*/
double closestPair(string filename) {

  int numPoints;

    ifstream fileIn(filename);
    if (!fileIn) 
    {
        cerr << "File not found!" << filename << endl;
        exit(1);
    }

    // read in number of points and initliaze vector
  
    fileIn >> numPoints;

    //initialize vector of points
    vector<point> points(numPoints);

    //read in points
    for (int i = 0; i < numPoints; i++) 
    {
        fileIn >> points[i].x >> points[i].y;
    }

    //points by x-coordinate
    sort(points.begin(), points.end(), [](const point& a, const point& b)
     {
        return a.x < b.x;
    });

    // closest pair of points
    double min = numeric_limits<double>::infinity();

    for (int i = 0; i < numPoints; i++) 
    {
        for (int j = i + 1; j < numPoints && points[j].x - points[i].x < min; j++) 
        {

            double dist = sqrt(pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2));

            if (dist < min) 
            {
                min = dist;
            }
        }
    }

    return min;
}

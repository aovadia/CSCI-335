//
//  Ovadia2.cpp
//  
//
//  Created by Adam on 12/19/16.
//
//

#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

// Iterate through input data and compute distances from one point to every other point
void nearestInsertion::computeAdjMatrix(vector<city> cityArray) {
    for (int a = 0; a < numCities; a++) {
        for (int b = 0; b <numCities; b++) {
            if (a != b) {
                double distance = computeDistance(cityArray[a], cityArray[b]);
                adjMatrix[a][b] = distance;
            }
        }
    }
}


// pythagorean theorem
double nearestInsertion::computeDistance(city city1, city city2) {
    double changeX, changeY;
    changeX = city2.x - city1.x;
    changeY = city2.y - city1.y;
    return sqrt((changeX * changeX) + (changeY * changeY));
}

// output AdjMatrix to terminal --> used for testing
void nearestInsertion::displayAdjMatrix() {
    for (int a = 0;  a < numCities; a++) {
        for (int b = 0; b < numCities; b++) {
            cout << adjMatrix[a][b] << "  ";
        }
        cout <<endl <<endl <<endl;
    }
}

// Initialize a few vars
void nearestInsertion::setNumCities(int num) {
    numCities = num;
    pathCount = 0;
}


void nearestInsertion::setCityVec(vector<city> storage) {
    data = storage;
}


void nearestInsertion::computePath() {
    double min = 99999999; // large number to make sure it will get updated
    int minX , minY;
    for (int a = 0; a < numCities; a++ ) {
        for (int b = 0; b < numCities; b++) {
            if ( (adjMatrix[a][b] != 0) && (adjMatrix[a][b] < min)) {
                minX = a;
                minY = b;
                min = adjMatrix[a][b];
            }
        }
    }
    cout <<"Min x: " <<minX <<endl <<"Min y: " <<minY <<endl;
    data[minX].inPath = true;
    data[minY].inPath = true;
    path.push_back(data[minX]);
    pathCount++;
    path.push_back(data[minY]);
    pathCount++;
    cout << "Min X: " <<path[0].x <<endl <<"Min Y: " <<path[0].y <<endl;
    cout << "Min X: " <<path[1].x <<endl <<"Min Y: " <<path[1].y <<endl;
    
    cout <<"Find Xadj: " << findXadjMatrixPos(path[0].x) <<endl;
    for (int a = 0; a < numCities - 2; a++) {
        computePathFromVertex();
    }
}

void nearestInsertion::computePathFromVertex() {
    int X1 = findXadjMatrixPos(path[0].x);
    int X2 = findXadjMatrixPos(path[path.size() - 1 ].x);
    double min = 99999999;
    double min2 = 99999999;
    int minX1, minX2;
    for (int a = 0; a <numCities; a++) {
        if ((adjMatrix[a][X1] < min) && (adjMatrix[a][X1] != 0) && !isInPath(data[a].x, data[a].y)) {
            min = adjMatrix[a][X1];
            minX1 = a;
        }
    }

    for (int a = 0; a <numCities; a++) {
        if ((adjMatrix[a][X2] < min2) && (adjMatrix[a][X2] != 0) && !isInPath(data[a].x, data[a].y)) {
            min2 = adjMatrix[a][X2];
            minX2 = a;
        }
    }
    if (min < min2) {
        data[minX1].inPath = true;
        path.insert(path.begin(), data[minX1]);
        pathCount++;
    }
    else {
        data[minX2].inPath = true;
        path.push_back(data[minX2]);
        pathCount++;
    }
}

int nearestInsertion::findXadjMatrixPos(double xCoord) {
    for (int a = 0; a <numCities; a++) {
        if (data[a].x == xCoord) {
            return a;
        }
    }
}

bool nearestInsertion::isInPath(double xValue, double yValue) { /* used to exclude cycles */
    bool isTrue = false;
    for (int a = 0; a < path.size(); a++) {
        if ((path[a].x == xValue) && path[a].y == yValue) {
            isTrue = true;
        }
    }
   
    return isTrue;
}

void nearestInsertion::displayPath() {
    cout <<endl <<"PATH: " <<endl;
    for (int a = 0; a < path.size(); a++) {
        cout << path[a].position <<endl;
    }
}


double nearestInsertion::computeLength() {
    double workingLength = 0;
    for (int a = 0; a < path.size(); a++) {
        workingLength = workingLength + adjMatrix[findXadjMatrixPos(path[a].x)][findXadjMatrixPos(path[a+1].x)];
    }
    return workingLength;
}

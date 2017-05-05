//
//  Ovadia1.cpp
//  
//
//  Created by Adam on 12/20/16.
//
//
#include "Node.h"
#include <stdio.h>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

void greedyTSP::setCity(vector<Node>& input) {
    data = input;
}
void greedyTSP::outputData() {
    cout <<endl <<"START GREEDY" <<endl;
    for (int a = 0; a < data.size(); a++) {
        cout <<data[a].identifier <<"   " <<data[a].x <<"  " << data[a].y <<endl;
    }
}


void greedyTSP::computeEdges() {
    for (int a = 0; a < cityCount; a++) {
        for (int b = 0; b <cityCount; b++) {
            if (a != b) {
                double distance = computeDistance(data[a], data[b]);
                weights[a][b] = distance;
            }
        }
    }
}

// pythagorean theorem
double greedyTSP::computeDistance(Node first, Node second) {
    double changeX, changeY;
    changeX = second.x - first.x;
    changeY = second.y - first.y;
    return sqrt((changeX * changeX) + (changeY * changeY));
}


void greedyTSP::begin(vector<Node> input) {
    cityCount = input.size();
    counter = 0;
}

// output edge weights to terminal --> used for testing
void greedyTSP::displayEdgeWeights() {
    for (int a = 0;  a < cityCount; a++) {
        for (int b = 0; b < cityCount; b++) {
            cout << weights[a][b] << "  ";
        }
        cout <<endl <<endl <<endl;
    }
}



void greedyTSP::computePath() {
    vector<int> addToPath = findSmallestEdge();

    // Add initial smallest path
  
    
    path[0] = data[addToPath[0]].identifier;
    path[1] = data[addToPath[1]].identifier;
    data[addToPath[0]].inPath = true;
    data[addToPath[1]].inPath = true;
    counter = counter + 2;
    // find the next
   
    vector<double> findNext = findNextSmallestEdge();
    for (int a = 0; a < cityCount - 2; a++) {
    int pos = findDataPos(findNext[0]);
        if (findNext[0] <= findNext[1] && !isInPath(pos)) { /* place city before */
            path[counter] = data[pos].identifier;
            counter++;
            data[pos].inPath = true;
        }
        findNext = findNextSmallestEdge();
    }
}

int greedyTSP::findDataPos(double element) {
    for (int a = 0; a <cityCount; a++) {
        for (int b = 0; b <cityCount; b++) {
            if (element == weights[a][b]) {
                return b;
            }
        }
    }
    
}

//int computePathPos(

vector<double> greedyTSP::findNextSmallestEdge() {
    vector<double> pathID;
    int minX, minY, minX1, minY1, minX2, minY2;
    int id = path[0];
    double min1, min2;
    double min = 99999999;
    for (int a = 0; a < cityCount; a++) {
      //  if ( (weights[a][path[0]] != 0) && (weights[a][path[0]]  < min) && (!data[a].inPath) && data[a].identifier != id)  {
        
        if (weights[a][path[0]] != 0 && weights[a][path[0]] < min && !data[a].inPath && !isInPath(data[a].identifier)) {
        
            minX = a;
            minY = path[0];
            min1 = weights[minX][minY];
            min = weights[minX][minY];

        }
    }
    pathID.push_back(min1);
    min = 9999999;
    for (int a = 0; a < cityCount; a++) {
   //     if (( weights[a][path[counter - 1]] != 0) && (weights[a][path[counter - 1]]  < min) && (!data[a].inPath) && (weights[a][path[counter - 1]] != min1) && (a != minY) && weights[a][path[counter - 1]] != min && !isInPath(data[a].identifier))  {
     
        if ( weights[a][path[counter - 1]] != 0 && weights[a][path[counter - 1]]  < min && !data[a].inPath) {
        
            minX1 = a;
            minY1 = path[0];
            min2 = weights[minX][minY];
            min = weights[minX][minY];
        }
    }
    pathID.push_back(min2);
    min = 99999999;
    bool update = false;
    for (int a = 0; a <cityCount; a++) {
        for (int b = 0; b <cityCount; b++) {
            if ((weights[a][b] != 0) && (weights[a][b] < min) && !data[a].inPath && !isInPath(data[a].identifier)) {
                minX2 = a;
                minY2 = b;
                min = weights[a][b];
                update = true;
            }
        }
    }
    if (update) {
        pathID.push_back(min);
    }
    for (int a = 0; a <pathID.size(); a++) {
        cout <<pathID[a] <<endl;
    }
    
    return pathID;
}

bool greedyTSP::isInPath(int x1) {
    bool isTrue = false;
    for (int a = 0; a < counter; a++) {
        if (path[a] == x1) {
            isTrue = true;
        }
    }
    
    return isTrue;
}



            
vector<int> greedyTSP::findSmallestEdge() {
    double min = 99999999;
    int minX, minY;
    for (int a = 0; a < cityCount; a++) {
        for (int b = 0; b <cityCount; b++) {
            if ((weights[a][b] != 0) && (weights[a][b] < min)) {
                if (!data[a].inPath && !data[b].inPath) {
                    minX = a;
                    minY = b;
                    min = weights[a][b];
                }
            }
        }
    }
    vector<int> aPath;
    aPath.push_back(minX);
    aPath.push_back(minY);
    data[minX].inPath = true;
    data[minY].inPath = true;
    return aPath;
}


void greedyTSP::outputPath() {
    cout <<endl <<"PATH: " <<endl;
    //Node* i = path[0].edge1;
    if (counter > 4) {
        for (int a = 0; a < counter; a++) {
            cout <<path[a] <<endl;
        }
    }
    else {
        cout <<path[0] <<endl << path[1] <<endl;
        for (int c = 2; c < cityCount; c++) {
            path[counter] = data[c].identifier;
            cout <<path[c] <<endl;
            counter++;
        }
    }
        
  //  cout <<data[0].identifier <<"   " << data[0].edge2->identifier <<endl;
   // cout <<data[1].identifier <<"   " << data[1].edge1->identifier <<endl;
}

double greedyTSP::computeLength() {
    double workingLength = 0;
    for (int a = 0; a < cityCount; a++) {
        workingLength = workingLength + weights[path[a]][path[a+1]];
    }
    return workingLength;
}

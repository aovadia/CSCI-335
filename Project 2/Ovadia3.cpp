//
//  Ovadia3.cpp
//  
//
//  Created by Adam on 12/23/16.
//
//
#include "Node.h"
#include <stdio.h>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

/*void greedy::outputPath() {
    cout <<endl <<"PATH: " <<endl;
    //Node* i = path[0].edge1;
    for (int a = 0; a < counter; a++) {
        cout <<path[a] <<endl;
    }
    
    //  cout <<data[0].identifier <<"   " << data[0].edge2->identifier <<endl;
    // cout <<data[1].identifier <<"   " << data[1].edge1->identifier <<endl;
}*/

// Initialize a few private elements
void greedy::begin(vector<Node> input) {
    cityCount = input.size();
    counter = 0;
}

void greedy::outputData() {
    cout <<endl <<"START GREEDY" <<endl;
    for (int a = 0; a < data.size(); a++) {
        cout <<data[a].identifier <<"   " <<data[a].x <<"  " << data[a].y <<endl;
    }
}

void greedy::setCity(vector<Node>& input) {
    data = input;
}


void greedy::computeEdges() {
    for (int a = 0; a < cityCount; a++) {
        for (int b = 0; b <cityCount; b++) {
            if (a != b) {
                double distance = computeDistance(data[a], data[b]);
                weights[a][b] = distance;
            }
        }
    }
}



// output edge weights to terminal --> used for testing
void greedy::displayEdgeWeights() {
    for (int a = 0;  a < cityCount; a++) {
        for (int b = 0; b < cityCount; b++) {
            cout << weights[a][b] << "  ";
        }
        cout <<endl <<endl <<endl;
    }
}

// pythagorean theorem
double greedy::computeDistance(Node first, Node second) {
    double changeX, changeY;
    changeX = second.x - first.x;
    changeY = second.y - first.y;
    return sqrt((changeX * changeX) + (changeY * changeY));
}


void greedy::computePath() {
    for (int b = 0; b < (cityCount / 2) + 1; b++) {
        // turn data set into unique edges
        vector<int> smallestEdge = findSmallestEdge();
            Edge add;
            add.id1 = smallestEdge[0];
            add.id2 = smallestEdge[1];
            EdgePath.push_back(add);
    
    }
    
    // determine how to combine the vector of edges
    path.push_back(EdgePath[0].id1);
    path.push_back(EdgePath[0].id2); // add smallest edge to path
    for (int c = 0; c < (cityCount / 2) + 1; c++) {
        connectEdgePath();

    }
    for (int d = 0; d < EdgePath.size(); d++) {
      //  if (!posInPath(d)) {
            path.push_back(EdgePath[d].id1);
            path.push_back(EdgePath[d].id2);
        //}
    }
    
    for (int i = 0; i < path.size(); i++) {
        for (int j = 1; j < path.size(); j++) {
            if (path[j] == i) {
                path.erase(path.begin() + j);
            }
        }
    }

}

void greedy::connectEdgePath() {
    double min = 99999999;
    int edge1, edge2;
    for (int a = 0; a < EdgePath.size(); a++) {
        for (int b = 0; b < EdgePath.size(); b++) {
            if (weights[a][b] != 0 && weights[a][b] < min) {
                if (!posInPath(a)) {
                    edge1 = a;
                    
                }
            }
        }
    }
    for (int a = 0; a < EdgePath.size(); a++) {
        for (int b = 0; b < EdgePath.size(); b++) {
            if (weights[a][b] != 0 && weights[a][b] < min) {
                if (!posInPath(a)) {
                    edge2 = a;
                }
            }
        }
    }
        
    if (edge1 <= edge2) {
        for (int c = 0; c < EdgePath.size(); c++ ) {
            if (EdgePath[c].id1 == edge1 || EdgePath[c].id2 == edge1) {
                path.insert(path.begin(), EdgePath[c].id2);
                path.insert(path.begin(), EdgePath[c].id1);
            }
        }
    }
    else {
        for (int c = 0; c < EdgePath.size(); c++ ) {
            if (EdgePath[c].id2 == edge2 || EdgePath[c].id1 == edge2) {
                path.push_back(EdgePath[c].id1);
                path.push_back(EdgePath[c].id2);
            }
        }
    }
   
}

bool greedy::posInPath(int pos) {
    bool isTrue = false;
    for (int a = 0; a < path.size(); a++) {
        if (path[a] == pos) {
            isTrue = true;
        }
    }
    return isTrue;
}

vector<int> greedy::findSmallestEdge() {
    double min = 99999999;
    int minX, minY;
    for (int a = 0; a < cityCount; a++) {
        for (int b = 0; b <cityCount; b++) {
            if ((weights[a][b] != 0) && (weights[a][b] < min)) {
                if (!isInPath(a)) {
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

bool greedy::isInPath(int pos) {
    bool inPath = false;
    for (int a = 0; a <EdgePath.size(); a++) {
        if (EdgePath[a].id1 == pos || EdgePath[a].id2 == pos) {
            inPath = true;
        }
    }
    return inPath;
}


void greedy::outputPath() {
    cout <<"PATH: " <<endl;
    for (int a = 0; a < path.size(); a++) {
        cout <<path[a] <<endl;
    }
}

double greedy::computeLength() {
    double workingLength = 0;
    for (int a = 0; a < cityCount; a++) {
        workingLength = workingLength + weights[path[a]][path[a+1]];
    }
    return workingLength;
}


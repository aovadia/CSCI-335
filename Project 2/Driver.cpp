// Adam Ovadia
//
//  Driver.cpp
//  
//
//  Created by Adam on 12/17/16.
//
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <chrono> // calculate time
#include "cityHeader.h"
#include "Ovadia1.h"
#include "Ovadia2.h"
#include "Ovadia3.h"
#include <fstream>
#include <string>
using namespace std;

// Put entire file into a vector of strings
vector<string> handleInput(string name, vector<string> tempStore) {
    ifstream fileIn;
    string line;
    fileIn.open(name);
    while (!fileIn.eof()) {
        getline(fileIn, line);
        tempStore.push_back(line);
    }
    fileIn.close();
    return tempStore;
}

// extract data from file vector into meaningful variables
vector<city> convertInToCity(vector<string> input) {
    vector<city> storage;
    for (int a = 7; a < input.size() - 1; a++) { /*ignore 0-6 lines in file */
        city singleCity;
        string temp;
        
        int num;
        int pos;
        num = input[a].find(' ');
        temp.assign(input[a], 0, num);
        singleCity.position = atoi(temp.c_str());
        input[a].assign(input[a], num+1, input[a].size());
        
        num = input[a].find(' ');
        temp.assign(input[a], 0, num);
        singleCity.x = atof(temp.c_str());
        input[a].assign(input[a], num+1, input[a].size());
        
        singleCity.y = atof(input[a].c_str());
        singleCity.inPath = false;
      
        // ignore duplicates
        bool Duplicate = false;
        for (int b = 0; b <storage.size(); b++) { /* search cities already added to see if duplicate is found */
            if (storage[b].x == singleCity.x && storage[b].y == singleCity.y) {
                Duplicate = true;
            }
        }
        if (!Duplicate) { /* only add if city is unique */
            storage.push_back(singleCity);
        }
    }
    return storage;
}

// convert City struct to Node struct
// Used for 2nd and 3rd Algorithms
vector<Node> convertToDouble(vector<city> myCity) {
    vector<Node> temp;
    for (int a = 0; a < myCity.size(); a++) {
        Node aNode;
        aNode.x = myCity[a].x;
        aNode.y = myCity[a].y;
        aNode.identifier = a;
        aNode.inPath = false;
        temp.push_back(aNode);
    }
    return temp;
}

int main (int argc, char* argv[ ]) {
    
    vector<city> storage;
    vector<string> tempStore;
    tempStore = handleInput(argv[1], tempStore);
    cout  <<"file name: " <<argv[1] <<endl;
    
    storage = convertInToCity(tempStore);
    
    for (int a = 0; a <storage.size(); a++) {
        cout << a <<'\t' <<"pos: " <<storage[a].position <<'\t' <<storage[a].x <<"   " << storage[a].y <<endl;
    }
    
    
    nearestInsertion NI; //First Algorithm: Nearest insertion
    NI.setCityVec(storage);
    NI.setNumCities(storage.size());
    
    //Begin Algorithm 2: Nearest Insertion
    // start clock
    auto start = chrono::steady_clock::now();
    NI.computeAdjMatrix(storage);
    NI.computePath();
    // end clock
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    
    // output to terminal
    NI.displayAdjMatrix();
    
    double length2 = NI.computeLength();
    cout <<endl <<"Length2 of path: " << length2 <<endl;

    vector<Node> tsp = convertToDouble(storage);
    vector<Node> thirdA = tsp;
    
 //   if (tsp.size() < 100) {
   // thirdA.erase(thirdA.begin() +100, thirdA.begin() + thirdA.size());
   // cout <<"SIZE: " << thirdA.size() <<endl;
   // }
    
    greedy gAlg; // Third Algorithm
    gAlg.begin(thirdA);
    gAlg.setCity(thirdA);
   
    auto start3 = chrono::steady_clock::now();

    gAlg.computeEdges();
    gAlg.computePath();

    auto end3 = chrono::steady_clock::now();
    auto diff3 = end3 - start3;
    
    double path3 = gAlg.computeLength();
    
    gAlg.outputData();
    gAlg.displayEdgeWeights();
    
 
    // Begin Algorithm 1: Greedy
    greedyTSP GTSP; // Second Algorithm
    GTSP.begin(tsp);
    GTSP.setCity(tsp);
    
    auto start2 = chrono::steady_clock::now();
    
    GTSP.computeEdges();
    GTSP.computePath();
    
    auto end2 = chrono::steady_clock::now();
    auto diff2 = end2 - start2;

    GTSP.outputData(); //test function
    GTSP.displayEdgeWeights();
    
    // output to terminal relevant statistical info and path and path length
    
    cout <<endl;
    cout <<"Algorithm 1: path: (based on file id)" <<endl;
    NI.displayPath();
    cout <<endl <<"Algorithm 2: path: (based on position in file, ie, 0 is first position) " <<endl;
    GTSP.outputPath();
    cout <<endl <<"Algorithm 3: path: (based on position in file, ie, 0 is first position)" <<endl;
    gAlg.outputPath();
    
    double path2 = GTSP.computeLength();

    
    cout <<endl;
    cout <<"Algoritm 1: Greedy Algorithm" <<endl;
    cout <<"Size of Input: " <<tsp.size() + 1 <<endl;
    cout <<"Length of path: " << path2 <<endl;
    cout <<"Time algorithm took: " <<chrono::duration<double, nano> (diff2).count() <<" ns" <<endl <<endl;
    
    cout <<"Algorithm 2: Nearest Insertion" <<endl;
    cout <<"Size of Input: " <<storage.size() + 1 <<endl;
    cout <<"Length of path: " <<length2 <<endl;
    cout <<"Time algorithm took: " <<chrono::duration<double, nano> (diff).count() <<" ns" <<endl <<endl;
    
    cout <<"Algoritm 3:" <<endl;
    cout <<"Size of Input: " <<thirdA.size() + 1 <<endl;
    cout <<"Length of path: " << path3 <<endl;
    cout <<"Time algorithm took: " <<chrono::duration<double, nano> (diff3).count() <<" ns" <<endl <<endl;
    
    
}

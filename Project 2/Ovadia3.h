//
//  Ovadia3.h
//  
//
//  Created by Adam on 12/23/16.
//
//

#ifndef Ovadia3_h
#define Ovadia3_h

#include "Node.h"
#include <vector>

int path[1000];
double weights[1000][1000];

class greedy {
    private:
        struct Edge {
            int id1;
            int id2;
        };
        std::vector<int> path;
        std::vector<Edge> EdgePath;
        std::vector<Node> data;
        std::vector<Edge> additionalPath; // store path in progress
        int cityCount;
        double computeDistance(Node first, Node second);
        //std::vector<int> findSmallestEdge();
        //std::vector<double> findNextSmallestEdge();
        int counter; // track size of path
        bool isInPath(int pos);
        std::vector<int> findSmallestEdge();
        void connectEdgePath();
        bool posInPath(int pos);
    
    
    public:
        void setCity(std::vector<Node>& input);
        void computeEdges();
    
         void computePath();
    
        // initialize private items
        void begin(std::vector<Node> input);
        double computeLength();
    
        // test
        void outputData();
        void displayEdgeWeights();
        void outputPath();
};

#endif /* Ovadia3_h */
#include "Ovadia3.cpp"


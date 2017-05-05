//
//  Ovadia1.h
//  
//
//  Created by Adam on 12/20/16.
//
//

#include "Node.h"
#include <vector>
#ifndef Ovadia1_h
#define Ovadia1_h


class greedyTSP {
    private:
        std::vector<Node> data;
        int path[1000];
        std::vector<Node> additionalPath; // store path in progress
        double weights[1000][1000];
        int cityCount;
        double computeDistance(Node first, Node second);
        std::vector<int> findSmallestEdge();
        std::vector<double> findNextSmallestEdge();
        int counter; // track size of path
        bool isInPath(int x1);

    public:
        void setCity(std::vector<Node>& input);
        void computeEdges();
    
        void computePath();
    
        // initialize private items
        void begin(std::vector<Node> input);
        int findDataPos(double element);
        double computeLength();

    // test
    void outputData();
    void displayEdgeWeights();
    void outputPath();
};



#endif /* Ovadia1_h */
#include "Ovadia1.cpp"

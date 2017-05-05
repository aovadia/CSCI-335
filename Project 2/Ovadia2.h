//
//  Ovadia2.h
//  
//
//  Created by Adam on 12/19/16.
//
//
#include "cityHeader.h"

#ifndef Ovadia2_h
#define Ovadia2_h
static const int MAX = 10000;
  double adjMatrix[MAX][MAX];

class nearestInsertion {
    private:
        int pathCount;
        int numCities;
    
        // [x][y] 1,2
        std::vector<city> data; // stores input data
        std::vector<city> path;  // stores path
        double computeDistance(city city1, city city2); //edges
    
        int findXadjMatrixPos(double xCoord);
        int findYadjMatrixPos(double yCoord);
    
        bool isInPath(double xValue, double yValue);
    public:
        void setNumCities(int num);
        void computeAdjMatrix(std::vector<city> cityArray);
    
        void computePath();
        void computePathFromVertex();
        void setCityVec(std::vector<city> storage);
    
        double computeLength();
    
        // test function
        void displayAdjMatrix();
        void displayPath();
};



#endif /* Ovadia2_h */
#include "Ovadia2.cpp"

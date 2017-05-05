//
//  Node.cpp
//  
//
//  Created by Adam on 12/20/16.
//
//

#include <stdio.h>
using namespace std;

Node::Node() : edge1(nullptr), edge2(nullptr) {
    
}

Node::Node(const double& aX, const double& aY) : x(aX), y(aY), edge1(nullptr), edge2(nullptr) {
    
}

Node::Node(const double& aX, const double& aY, Node* E1, Node* E2) : x(aX), y(aY), edge1(E1), edge2(E2) {
    
}

void Node::insert(double& Xval, double& Yval) {
    
}

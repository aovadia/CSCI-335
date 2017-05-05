//
//  Node.h
//  
//
//  Created by Adam on 12/20/16.
//
//

#ifndef Node_h
#define Node_h
/*
class Node {
    private:
        double x;
        double y;
        Node* edge1;
        Node* edge2;
    
    public:
        Node();
        Node(const double& aX, const double& aY);
        Node(const double& aX, const double&, Node* E1, Node* E2);
        void insert(double& Xval, double& Yval);
    
}; */


struct Node {
    int identifier;
    double x;
    double y;
    bool inPath;
    Node* edge1;  //left
    Node* edge2;   // right
    void setEdge1(Node & anEntry) {
        edge1 = &anEntry;
    }
    void setEdge2(Node & anEntry) {
        edge2 = &anEntry;
    }
    Node* getEdge1() {
        return edge1;
    }
    Node* getEdge2() {
        return edge2;
    }
};

#endif /* Node_h */
//#include "Node.cpp"

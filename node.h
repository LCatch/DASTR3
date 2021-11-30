
// -------------------------------------------------
// Datastructures assignment 2
// Authors: Liya Charlaganova, Wouter Remmerswaal
// -------------------------------------------------
// The Node class tores a single element for the automaton matrix.

#ifndef NODE_H
#define NODE_H

using namespace std;

// Node class
class Node{
    public:
        Node();
        Node(char c, int l, int r);
        void print();
        void shift(int i);

        char letter;    // stores character
        int left;       // left child
        int right;      // right child
};

#endif
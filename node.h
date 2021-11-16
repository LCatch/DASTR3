
// -------------------------------------------------
// Datastructures assignment 2
// Authors: Liya Charlaganova, Wouter Remmerswaal
// -------------------------------------------------
// The Node class tores a single element for the automaton matrix.

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <string>

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

// Create an empty node.
Node::Node(){
    letter = ' ';
    left = -1;
    right = -1;
}

// Create node with a character 'c' which points to two other nodes at
// indexes 'l' and 'r'.
Node::Node(char c, int l, int r){
    letter = c;
    left = l;
    right = r;
}

// Shifts the indexes of both the left and the right node by i
// Does not shift if the node has no left or right.
void Node::shift(int i){
    if (left != -1){
        left += i;
    }
    if (right != -1){
        right += i;
    }
}

// Debug print, prints the letter, left and right of a node.
void Node::print(){
    cout << letter << ' ' << left << ' ' << right << endl;
}

#endif
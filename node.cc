#include <iostream>
#include <vector>
#include <string>
#include "basic.h"
#include "node.h"

using namespace std;

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

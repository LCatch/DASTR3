
#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node{
    public:
        Node();
        Node(char c, int l, int r);
        void print();
        void shift(int i);

        // to private
        char letter;
        int left;
        int right;
    private:
        
};

// Create an empty node that points to the right.
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

void Node::shift(int i){
    if (left != -1){
        left += i;
    }
    if (right != -1){
        right += i;
    }
}

void Node::print(){
    cout << letter << ' ' << left << ' ' << right << endl;
}

#endif
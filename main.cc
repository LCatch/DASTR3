// -------------------------------------------------
// Datastructures assignment 2
// Authors: Liya Charlaganova, Wouter Remmerswaal
// -------------------------------------------------
// Main file that prints the menu and takes the input from the user.
// The whole program has the goal to take in a regex expression and then
// check whether a string input matches the expression using an 
// automaton.
// (String matching has not yet been implemented)

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "node.h"
#include "automaton.h"

using namespace std;

void menu(){
    bool exit = false;
    string in;
    Automaton Aut = Automaton();

    while(!exit){
        cout << endl;
        cout << "Commands: " << endl;
        cout << "'exp' <expression> to read in an expression." << endl;
        cout << "'dot' <file> to write the expression in DOT";
        cout << " notation to 'file'." << endl;
        cout << "'mat' <string> to match string to expression" << endl;
        cout << "'end' to exit the program" << endl;
        cout << endl;
        
        cin >> in;
        
        if (in == "end"){
            exit = true;
        }

        else if (in == "exp"){
            Aut.read_expr();
        }
        else if (in == "dot"){
            Aut.print_dot();
        }
        else if (in == "p"){ // debug print
            Aut.print();
        }
        else if (in == "mat"){ 
            Aut.match();
        }
        else{
            cout << "Command unclear" << endl;
        }

    }
}

int main(){
    menu();
}
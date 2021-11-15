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
        // cout << "'mat' <string> to match string to expression" << endl;
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
            cout << "dot" << endl;
        }
        else if (in == "p"){
            Aut.print();
        }
        else{
            cout << "Command unclear" << endl;
        }

    }
}

int main(){
    // Automaton Aut = Automaton();
    // Aut.read_expr();
    // Aut.print();
    menu();
}
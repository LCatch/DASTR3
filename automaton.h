
#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "node.h"
#include "basic.h"

using namespace std;

int len_expr;

class Automaton{
    public:
        Automaton();
        Automaton(char letter);

        void concat(Automaton Aut2);
        void star();
        void add(Automaton Aut2);
        Automaton Expr(istringstream &is);
        Automaton Term (istringstream &is);
        Automaton Fact (istringstream &is);

        void print();

        void next_token(istringstream &is);
        char token; // TODO move to private

        void overwrite(Automaton Aut);
        void read_expr();
        void print_dot();

    private:
        // char token;
        vector<Node> mat;
        // int len;
        int i;
        int f;
};

Automaton::Automaton(){
    i = -1;
    f = -1;
    token = ' ';
    len_expr = 0;
    mat.push_back(Node()); // add emtpy node at beginning
}

Automaton::Automaton(char letter){
    token = ' ';
    len_expr = 0;
    i = 1;
    f = 2;
    mat.push_back(Node()); // add emtpy node at beginning
    mat.push_back(Node(letter, 2, -1));
    mat.push_back(Node());
}

void Automaton::next_token(istringstream &is){
    cout << "in next" << endl;
    // if (cin.eof()){
    //     cout << "eof" << endl;
    //     token = ' ';
    // }
    // else{
    //     cin >> token;
    // }
    is >> token;
    cout << "NEXT: " << token << endl;
}

// Debug print, prints all nodes from 1 to n
void Automaton::print(){
    for (unsigned int i = 1; i < mat.size(); i++){
        cout << i << " : ";
        mat[i].print();
    }
}

// Concats another automaton to the current automaton
void Automaton::concat(Automaton Aut2) {
    int iAut1 = mat.size();

    mat.at(f) = Node(' ', Aut2.i + iAut1 - 1, -1);;

    for (unsigned int i=1; i < Aut2.mat.size() - 1; i++){
        Node n = Aut2.mat.at(i);
        n.shift(iAut1 - 1);
        mat.push_back(n);
    }
    mat.push_back(Node());
    f = mat.size() - 1;
}

// "stars" the current automaton
void Automaton::star(){
    Node n = Node(' ', i, mat.size() + 1);

    mat.at(f) = n;
    mat.push_back(n);
    mat.push_back(Node());

    i = mat.size() - 2;
    f = mat.size() - 1;
}

// Adds another automaton to the current automaton
void Automaton::add(Automaton Aut2){
    int fAut1 = mat.size() + Aut2.mat.size();
    int iAut2 = mat.size();

    mat.back() = Node(' ', fAut1, -1);

    for (unsigned int j=1; j < Aut2.mat.size(); j++){
        Node n = Aut2.mat.at(j);
        n.shift(iAut2 - 1);
        mat.push_back(n);
    }
    mat.back() = Node(' ', fAut1, -1);
    mat.push_back(Node(' ', i, iAut2) );
    mat.push_back(Node());

    f = mat.size() - 1;
    i = mat.size() - 2;
}


Automaton Automaton::Expr(istringstream &is) {
    cout << "EXPR" << endl; 
    Automaton Aut1 = Term(is);
    // Aut1.print();
    if ( token == '|' ){ 
        next_token(is);
        Automaton Aut2 = Expr(is);
        Aut1.add(Aut2);
    }
    return Aut1;
} // Expr

Automaton Automaton::Term (istringstream &is) {
    cout << "TERMO" << endl;
    Automaton Aut1 = Fact(is);
    if ( is_letter(token) | (token == '(') ){
        Automaton Aut2 = Term(is);
        Aut1.concat(Aut2);
    }
    return Aut1;
} // Term

Automaton Automaton::Fact (istringstream &is) {
    cout << "FACT" << endl;
    // cout << "TOK: " << token << endl;
    Automaton Aut = Automaton();
    cout << "tok: " << token << endl;
    if ( token == '('){ 
        next_token(is);
        Aut = Expr(is);
        if ( token == ')' ) {
            next_token(is);
        }
        else{
            cout << "bad shit" << endl;
        } //TODO exit or smt?
    }
    else if ( is_letter(token) ){
        cout << "token got" << endl;
        Aut = Automaton(token); // TODO actually make a thing
        // Aut.print();
        // cout << "bb" << endl;
        next_token(is);
        // cout << "aaa" << endl;
    }
    else if (token == '$'){
        cout << "EMPTY TOKEN" << endl;
        return Aut;
    }
    else{
        cout << "bad shit 2" << endl; // TODODOD
        return Aut;
    }

    if (token == '*'){ 
        Aut.star();
        next_token(is);
    }
    return Aut;
} // Fact

// Overwrites the current Automaton with another automaton
void Automaton::overwrite(Automaton Aut){
    mat.clear();
    for (unsigned int j=0; j<Aut.mat.size(); j++){
        mat.push_back(Aut.mat.at(j));
    }
    token = ' ';
    i = Aut.i;
    f = Aut.f;
}

// Reads an expressinon given by the user from the input line
// and overwrites the new expression into the current one
void Automaton::read_expr(){
    Automaton Aut = Automaton();
    string line;
    string str;

    getline(cin, line);
    line += "$";
    istringstream is(line);
    // len_expr = line.size();
    

    Aut.next_token(is);

    overwrite(Aut.Expr(is));

}

// Dot-prints the current automaton into a file given by the user
void Automaton::print_dot(){
    string filename;
    string letter;
    cin.ignore(); // Ignore the first part of the cin
    getline(cin, filename);
    ofstream out(filename);
    out << "digraph G {\n\trankdir=\"LR\" \n"; // Standard beginning of the file
    for(unsigned int j=1; j<mat.size()-1; j++){ 
        out << "\t" + to_string(j) + " -> " + to_string(mat[j].left); // Every node has at least an arrow
        if(is_letter(mat[j].letter)){ // If the transition uses a letter, label it this letter
            letter = mat[j].letter; // This can only happen if a node has no right "target"
            out << " [label=\"" + letter + string("\"]");
        }
        out << "\n";
        if(mat[j].right!=-1){ // If a node also has a right "target", also use this one
            out << "\t" + to_string(j) + " -> " + to_string(mat[j].right) + "\n";
        }
    }
    out << "}";
    out.close();
}
#endif
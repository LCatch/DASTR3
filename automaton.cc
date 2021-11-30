
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "node.h"
#include "basic.h"
#include "automaton.h"

using namespace std;

// Constructor for empty automaton
Automaton::Automaton(){
    error = false;
    i = -1;
    f = -1;
    token = ' ';
    mat.push_back(Node()); // add emtpy node at beginning
}

// Constructor for automaton which contains a single transition
// from initial state to final state with a character 'letter'.
Automaton::Automaton(char letter){
    error = false;
    token = ' ';
    i = 1;
    f = 2;
    mat.push_back(Node()); // add emtpy node at beginning
    mat.push_back(Node(letter, 2, -1));
    mat.push_back(Node());
}

// Get next token.
void Automaton::next_token(istringstream &is){
    is >> token;
}

// Debug print, prints all nodes from 1 to n
void Automaton::print(){
    for (unsigned int i = 1; i < mat.size(); i++){
        cout << i << " : ";
        mat[i].print();
    }
}

void Automaton::clear(){
    error = false;
    i = -1;
    f = -1;
    token = ' ';
    mat.clear();
    mat.push_back(Node());
}

bool Automaton::contain_errors(Automaton Aut2){
    return error | Aut2.has_error();
}

bool Automaton::has_error(){
    return error;
}

void Automaton::set_error(bool err){
    error = err;
}

// Concats another automaton to the current automaton.
void Automaton::concat(Automaton Aut2) {
    if (contain_errors(Aut2)){
        clear();
        error = true;
    }
    else{
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
}

// "stars" the current automaton.
void Automaton::star(){
    Node n = Node(' ', i, mat.size() + 1);

    mat.at(f) = n;
    mat.push_back(n);
    mat.push_back(Node());

    i = mat.size() - 2;
    f = mat.size() - 1;
}

// Adds another automaton to the current automaton.
void Automaton::add(Automaton Aut2){
    if (contain_errors(Aut2)){
        clear();
        error = true;
    }

    else{
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
}

// Creates an expression.
Automaton Automaton::Expr(istringstream &is) {
    Automaton Aut1 = Term(is);
    if ( token == '|' ){ 
        next_token(is);
        Automaton Aut2 = Expr(is);
        Aut1.add(Aut2);
    }
    return Aut1;
}

// Creates a term.
Automaton Automaton::Term (istringstream &is) {
    Automaton Aut1 = Fact(is);
    if ( is_letter(token) | (token == '(') ){
        Automaton Aut2 = Term(is);
        Aut1.concat(Aut2);
    }
    return Aut1;
} // Term

// Creates a factor, this is the smallest possible element.
Automaton Automaton::Fact (istringstream &is) {
    Automaton Aut = Automaton();
    if ( token == '('){ 
        next_token(is);
        Aut = Expr(is);
        if ( token == ')' ) {
            next_token(is);
        }
        else{
            cout << "Invalid expression" << endl;
            Aut.set_error(true);
            return Aut;
        } 
    }
    else if ( is_letter(token) ){
        Aut = Automaton(token);
        next_token(is);
    }
    else if (token == '$'){
        return Aut;
    }
    else{
        cout << "Invalid expression" << endl;
        Aut.set_error(true);
        return Aut;
    }

    if (token == '*'){ 
        Aut.star();
        next_token(is);
    }
    return Aut;
}

// Overwrites the current Automaton with another automaton.
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
// and overwrites the new expression into the current one.
void Automaton::read_expr(){
    Automaton Aut = Automaton();
    string line;
    string str;

    getline(cin, line);
    line += "$";        // adding endline character
    istringstream is(line);
    

    Aut.next_token(is);

    overwrite(Aut.Expr(is));

}

// Dot-prints the current automaton into a file given by the user.s
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

// Add items to e_items which you can epsilon-reach via node n
void Automaton::e_space_rec(int n, vector<int> &e_items){
    if(find(e_items.begin(), e_items.end(), n) == e_items.end()){ // If the current item is not yet in the items list
        e_items.push_back(n); // Add the item
        if(!is_letter(mat[n].letter) && mat[n].left!=-1){ // If it has a possible epsilon jump 
            e_space_rec(mat[n].left, e_items); // Go again from the left node
            if(mat[n].right!=-1){
                e_space_rec(mat[n].right, e_items); // Go again from the right node
            }
        }
    }
} 


// Return the whole epsilon space of a set of nodes 
vector<int> Automaton::e_space(vector<int> space){
    vector<int> new_e_space; 
    for(unsigned int i=0; i<space.size();i++){ // For every node in space we check which nodes we can epsilon reach 
        e_space_rec(space[i], new_e_space);
    }
    return new_e_space;
}

// Determine the node which you can reach via space with a forced node jump with "letter"
vector<int> Automaton::e_space_letter(vector<int> space, char letter){
    vector<int> new_e_space_letter; // Start with an empty space
    space = e_space(space); // Determine the epsilon space of the starting space
    for(unsigned int i=0; i<space.size(); i++){ // For every item in this space 
        if(mat[space[i]].letter==letter){ // We check if we can go to another node via the letter
            if(find(new_e_space_letter.begin(), new_e_space_letter.end(), mat[space[i]].left) == new_e_space_letter.end()){
                new_e_space_letter.push_back(mat[space[i]].left); // Add the new letter to the new space
            }
        }
    }
    return new_e_space_letter;
}

void Automaton::match(){
    string input;
    cin.ignore(); // Ignore the first part of the cin
    getline(cin, input);
    if(mat.size()==1){ // No expression or empty expression in the automaton
        cout << "no expression to match" << endl;
        return;
    }
    vector<int> space;
    space.push_back(i); // Initial state
    for(char& character : input) { // For every character in the matchable string
        space = e_space_letter(space, character); // We determine the space when we use this letter
    }
    space = e_space(space); // From the last space we take the epsilon space
    int end_node = mat.size()-1; // End node
    if(find(space.begin(), space.end(), end_node) != space.end()){
        cout << "match"<< endl; // If this epsilon space contains the end node we are happy
    }
    else{
        cout << "geen match" << endl;
    }
}

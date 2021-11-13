#include <iostream>
#include <vector>

using namespace std;

class Node{
    public:
        Node();
        Node(char c, int l, int r);
        void print();
    
    private:
        char letter;
        int left;
        int right;
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

void Node::print(){
    cout << letter << ' ' << left << ' ' << right << endl;
}

class Automaton{
    public:
        Automaton();
        Automaton(char letter);
        Automaton concat(Automaton Aut1, Automaton Aut2);
        Automaton star();
        Automaton add(Automaton Aut1, Automaton Aut2);
        Automaton Expr();
        Automaton Term ();
        Automaton Fact ();

        void print();

        void next_token();
        bool token_is_letter();
        char token; // TODO move to private

    private:
        // char token;
        vector<Node> mat;
        int len;
};

Automaton::Automaton(){
    token = ' ';
    len = 0;
    mat.push_back(Node()); // add emtpy node at beginning
}

Automaton::Automaton(char letter){
    token = ' ';
    len = 2;
    mat.push_back(Node()); // add emtpy node at beginning
    mat.push_back(Node(letter, 1, -1));
    mat.push_back(Node());
}

void Automaton::next_token(){
    cin >> token;
}

bool Automaton::token_is_letter(){
    return (token >= 'a') && (token <= 'z');
}

void Automaton::print(){
    for (Node n: mat){
        n.print();
    }
}

Automaton Automaton::concat(Automaton Aut1, Automaton Aut2) {
    // int f = Aut1.size() + Aut2.size();
    // Aut1.mat.push_back(Node(' ', f, -1) );
    
}

Automaton Automaton::star(){
    //stuff
}

Automaton Automaton::add(Automaton Aut1, Automaton Aut2){
    //stuff
}


Automaton Automaton::Expr() {
    Automaton Aut1 = Term();
    if ( token == '|' ){ 
        next_token();
        Automaton Aut2 = Expr();
        return add(Aut1, Aut2);
    }
    return Aut1;
} // Expr

Automaton Automaton::Term () {
    Automaton Aut1 = Fact();
    if ( token_is_letter() | (token == '(') ){
        Automaton Aut2 = Term();
        return concat(Aut1, Aut2);
    }
    return Aut1;
    // TODO either do not call concat if aut2 is empty, or make concat take in emtpy
    // aut too
} // Term

Automaton Automaton::Fact () {
    cout << "TOK: " << token << endl;
    Automaton Aut = Automaton();
    if ( token == '('){ 
        next_token();
        Automaton Aut = Expr(); // 11,12 shit? 
        if ( token == ')' ) {
            next_token();
        }
        else{
            cout << "bad shit" << endl;
        } //TODO exit or smt?
    }
    else if ( token_is_letter() ){
        cout << "token got" << endl;
        Aut = Automaton(token); // TODO actually make a thing
        Aut.print();
        next_token();
    }
    else{
        cout << "bad shit 2" << endl; // TODODOD
        return Automaton();
    }

    if (token == '*'){ // eventueel while? TODO decide
        // pas ster toe op Aut; // TODO
        cout << "astar" << endl;
        next_token();
    }
    return Aut;
} // Fact

int main(){
    Automaton Aut = Automaton();
    Aut.print();
    Aut.next_token();
    Aut = Aut.Fact();
    cout << "FINIAL PRINT: "<< endl;
    Aut.print();
    // while (Aut.token != '$'){
    //     cout << Aut.token << endl;
    //     Aut.next_token();
    // }
}
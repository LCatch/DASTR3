#include <iostream>
#include <vector>

using namespace std;

class Node{
    public:
        Node();
        Node(char c, int l, int r);
        void print();
        void shift(int i);
    
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

class Automaton{
    public:
        Automaton();
        Automaton(char letter);
        void concat(Automaton Aut2);
        void star();
        void add(Automaton Aut2);
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
        int i;
        int f;
};

Automaton::Automaton(){
    i = -1;
    f = -1;
    token = ' ';
    len = 0;
    mat.push_back(Node()); // add emtpy node at beginning
}

Automaton::Automaton(char letter){
    token = ' ';
    len = 2;
    i = 1;
    f = 2;
    mat.push_back(Node()); // add emtpy node at beginning
    mat.push_back(Node(letter, 2, -1));
    mat.push_back(Node());
}

void Automaton::next_token(){
    cout << "in next" << endl;
    if (cin.eof()){
        cout << "eof" << endl;
        token = ' ';
    }
    else{
        cin >> token;
    }
    cout << "NEXT: " << token << endl;
}

bool Automaton::token_is_letter(){
    return (token >= 'a') && (token <= 'z');
}

void Automaton::print(){
    for (unsigned int i = 1; i < mat.size(); i++){
        cout << i << " : ";
        mat[i].print();
    }
}

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

void Automaton::star(){
    Node n = Node(' ', i, mat.size() + 1);

    mat.at(f) = n;
    mat.push_back(n);
    mat.push_back(Node());

    i = mat.size() - 2;
    f = mat.size() - 1;
}

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


Automaton Automaton::Expr() {
    Automaton Aut1 = Term();
    Aut1.print();
    if ( token == '|' ){ 
        next_token();
        Automaton Aut2 = Expr();
        Aut1.add(Aut2);
    }
    return Aut1;
} // Expr

Automaton Automaton::Term () {
    Automaton Aut1 = Fact();
    if ( token_is_letter() | (token == '(') ){
        Automaton Aut2 = Term();
        Aut1.concat(Aut2);
    }
    return Aut1;
} // Term

Automaton Automaton::Fact () {
    cout << "TOK: " << token << endl;
    Automaton Aut = Automaton();
    if ( token == '('){ 
        next_token();
        Automaton Aut = Expr();
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
        // Aut.print();
        // cout << "bb" << endl;
        next_token();
        // cout << "aaa" << endl;
    }
    else{
        cout << "bad shit 2" << endl; // TODODOD
        return Automaton();
    }

    if (token == '*'){ // eventueel while? TODO decide
        // pas ster toe op Aut; // TODO
        next_token();
    }
    return Aut;
} // Fact

int main(){
    Automaton Aut = Automaton();
    Aut = Aut.Expr();
}
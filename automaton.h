// -------------------------------------------------
// Datastructures assignment 2
// Authors: Liya Charlaganova, Wouter Remmerswaal
// -------------------------------------------------
// Automaton class that creates the automaton using recursive function
// calls and then constructing the automaton bottom up. The automaton
// itself is stored as a matrix.

#ifndef AUTOMATON_H
#define AUTOMATON_H

using namespace std;


// Automaton class
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

        void overwrite(Automaton Aut);
        void clear();
        void read_expr();
        void print_dot();

        bool contain_errors(Automaton Aut2);
        bool has_error();
        void set_error(bool err);

        void e_space_rec(int n, vector<int> &e_items);
        vector<int> e_space(vector<int> space);
        vector<int> e_space_letter(vector<int> space, char letter);
        void match();

    private:
        char token;         // stores the current token
        vector<Node> mat;   // matrix that stores the automaton
        int i;              // initial state of automaton
        int f;              // final state of automaton
        bool error;
};

#endif
#include <iostream>
#include <vector>

using namespace std;


class Automaton{
    Automaton();
    Automaton concat(Automaton Aut1, Automaton Aut2);
    Automaton star();
    Automaton add(Automaton Aut1, Automaton Aut2)
    Automaton Expr();
    Automaton Term ();
    Automaton Fact ();

    next_token();

    private:
        char token;
}

Automaton::Automaton(){
    token = ' ';
}

Automaton::next_token(){
    cin >> token;
}

Automaton::Automaton concat(Automaton Aut1, Automaton Aut2) {
    //stuff
}

Automaton::Automaton star(){
    //stuff
}

Automaton::Automaton add(Automaton Aut1, Automaton Aut2){
    //stuff
}


Automaton::Automaton Expr() {
    Automaton Aut1 = Term();
    if ( huidige letter == ’|’ ){ 
        next_token();
        Automaton Aut2 = Expr();
    }
    return add(Aut1, Aut2);
    // TODO either do not call add if aut2 is empty, or make add take in emtpy
    // aut too
} // Expr

Automaton::Automaton Term () {
    Automaton Aut1 = Fact();
    if ( huidige letter in {’(’,’a’,...,’z’} ) // TODO
        Automaton Aut2 = Term();
    return concat(Aut1, Aut2)
    // TODO either do not call concat if aut2 is empty, or make concat take in emtpy
    // aut too
} // Term

Automaton::Automaton Fact () {
    if ( token == '('){ 
        next_token();
        Automaton Aut1 = Expr();
        if ( token == ')' )
            next_token();
        else{
            cout << "bad shit" << endl;
        } //TODO exit or smt?
    }
    else if ( huidige letter in {’a’,...,’z’} ) // TODO
        { Automaton Aut = tak met huidige letter; // TODO actually make a thing
        next_token();
        }
    else{
        cout << "bad shit 2" << endl; // TODODOD
    }

    if (token == '*'){ // eventueel while? TODO decide
        pas ster toe op Aut; // TODO
        next_token();
    }
    return Aut;
} // Fact
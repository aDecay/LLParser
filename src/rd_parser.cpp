#include <iostream>
#include "../include/rd_parser.h"

using namespace std;

RecursiveDescentParser::RecursiveDescentParser(LexicalAnalyzer* analyzer, bool debug) {
    this->analyzer = analyzer;
    this->debug = false;
}

void RecursiveDescentParser::parse() {
    analyzer->ready();
    program();
}

void RecursiveDescentParser::program() {
    if (debug)
        cout << "Enter <program>" << endl;
    
    statements();
    
    if (debug)
        cout << "Exit <program>" << endl;
}

void RecursiveDescentParser::statements() {
    if (debug)
        cout << "Enter <statements>" << endl;
    
    statement();

    while (analyzer->getNextToken() == LexicalAnalyzer::SEMI) {
        analyzer->lex();
        statement();
    }

    if (debug)
        cout << "Exit <statements>" << endl;
}

void RecursiveDescentParser::statement() {
    if (debug)
        cout << "Enter <statement>" << endl;

    if (analyzer->getNextToken() != LexicalAnalyzer::IDENT) {
        cout << "ERROR - ident expected" << endl;
    }
    analyzer->lex();
    if (analyzer->getNextToken() != LexicalAnalyzer::ASSIGN_OP) {
        cout << "ERROR - assign op expected" << endl;
        // TODO - error
    }
    analyzer->lex();
    expression();

    if (debug)
        cout << "Exit <statement>" << endl;
}

void RecursiveDescentParser::expression() {
    if (debug)
        cout << "Enter <expression>" << endl;

    term();
    while (analyzer->getNextToken() == LexicalAnalyzer::ADD_OP) {
        analyzer->lex();
        term();
    }

    if (debug)
        cout << "Exit <expression>" << endl;
}

void RecursiveDescentParser::term() {
    if (debug)
        cout << "Enter <term>" << endl;

    factor();
    while (analyzer->getNextToken() == LexicalAnalyzer::MULT_OP) {
        analyzer->lex();
        factor();
    }

    if (debug)
        cout << "Exit <term>" << endl;
}

void RecursiveDescentParser::factor() {
    if (debug)
        cout << "Enter <factor>" << endl;

    if (analyzer->getNextToken() == LexicalAnalyzer::IDENT
        || analyzer->getNextToken() == LexicalAnalyzer::CONST) {
            analyzer->lex();
    } else {
        if (analyzer->getNextToken() != LexicalAnalyzer::LEFT_PAREN) {
            cout << "ERROR - lparen expected" << endl;
            // TODO - error
        }
        analyzer->lex();
        expression();
        if (analyzer->getNextToken() != LexicalAnalyzer::RIGHT_PAREN) {
            cout << "ERROR - rparen expected" << endl;
            // TODO - error
        }
        analyzer->lex();
    }

    if (debug)
        cout << "Exit <factor>" << endl;
}
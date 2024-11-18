#include <iostream>
#include "../include/rd_parser.h"

using namespace std;

RecursiveDescentParser::RecursiveDescentParser(LexicalAnalyzer* analyzer) {
    this->analyzer = analyzer;
}

void RecursiveDescentParser::parse() {
    analyzer->ready();
    program();
}

void RecursiveDescentParser::program() {
    cout << "Enter <program>" << endl;
    statements();
    cout << "Exit <program>" << endl;
}

void RecursiveDescentParser::statements() {
    cout << "Enter <statements>" << endl;
    
    statement();

    while (analyzer->getNextToken() == LexicalAnalyzer::SEMI) {
        analyzer->lex();
        statement();
    }

    cout << "Exit <statements>" << endl;
}

void RecursiveDescentParser::statement() {
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

    cout << "Exit <statement>" << endl;
}

void RecursiveDescentParser::expression() {
    cout << "Enter <expression>" << endl;

    term();
    while (analyzer->getNextToken() == LexicalAnalyzer::ADD_OP) {
        analyzer->lex();
        term();
    }

    cout << "Exit <expression>" << endl;
}

void RecursiveDescentParser::term() {
    cout << "Enter <term>" << endl;

    factor();
    while (analyzer->getNextToken() == LexicalAnalyzer::MULT_OP) {
        analyzer->lex();
        factor();
    }

    cout << "Exit <term>" << endl;
}

void RecursiveDescentParser::factor() {
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

    cout << "Exit <factor>" << endl;
}
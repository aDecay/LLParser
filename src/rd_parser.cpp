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
    printResult();
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
    initStmt();

    if (debug)
        cout << "Enter <statement>" << endl;

    if (analyzer->getNextToken() != LexicalAnalyzer::IDENT) {
        cout << "ERROR - ident expected" << endl;
    }
    string id(analyzer->getLexeme());

    idCount++;
    analyzer->lex();
    if (analyzer->getNextToken() != LexicalAnalyzer::ASSIGN_OP) {
        cout << "ERROR - assign op expected" << endl;
        // TODO - error
    }
    analyzer->lex();
    SymbolEntry result = expression();
    symbolTable[id] = result;

    if (debug)
        cout << "Exit <statement>" << endl;

    printStmt();
}

SymbolEntry RecursiveDescentParser::expression() {
    SymbolEntry result;
    
    if (debug)
        cout << "Enter <expression>" << endl;

    result = term();
    while (analyzer->getNextToken() == LexicalAnalyzer::ADD_OP) {
        char op = analyzer->getLexeme()[0];
        opCount++;
        analyzer->lex();
        SymbolEntry nextTerm = term();
        if (op == '+') {
            result = result + nextTerm;
        } else {
            result = result - nextTerm;
        }
    }

    if (debug)
        cout << "Exit <expression>" << endl;

    return result;
}

SymbolEntry RecursiveDescentParser::term() {
    SymbolEntry result;

    if (debug)
        cout << "Enter <term>" << endl;

    result = factor();
    while (analyzer->getNextToken() == LexicalAnalyzer::MULT_OP) {
        char op = analyzer->getLexeme()[0];
        opCount++;
        analyzer->lex();
        SymbolEntry nextFactor = factor();
        if (op == '*') {
            result = result * nextFactor;
        } else {
            result = result / nextFactor;
        }
    }

    if (debug)
        cout << "Exit <term>" << endl;

    return result;
}

SymbolEntry RecursiveDescentParser::factor() {
    SymbolEntry result;

    if (debug)
        cout << "Enter <factor>" << endl;

    if (analyzer->getNextToken() == LexicalAnalyzer::IDENT) {
        string lexeme = string(analyzer->getLexeme());
        if (symbolTable.find(lexeme) == symbolTable.end()) {
            symbolTable[lexeme] = SymbolEntry(0, true);
        }
        result = symbolTable[lexeme];
        idCount++;
        analyzer->lex();
    } else if (analyzer->getNextToken() == LexicalAnalyzer::CONST) {
        result = SymbolEntry(atoi(analyzer->getLexeme()), false);
        constCount++;
        analyzer->lex();
    } else {
        if (analyzer->getNextToken() != LexicalAnalyzer::LEFT_PAREN) {
            cout << "ERROR - lparen expected" << endl;
            // TODO - error
        }
        analyzer->lex();
        result = expression();
        if (analyzer->getNextToken() != LexicalAnalyzer::RIGHT_PAREN) {
            cout << "ERROR - rparen expected" << endl;
            // TODO - error
        }
        analyzer->lex();
    }

    if (debug) {
        cout << "Exit <factor>" << endl;
        cout << result.value << ", " << result.isUnknown << endl;
    }
    
    return result;
}

void RecursiveDescentParser::initStmt() {
    analyzer->initAccumulatedLexeme();

    idCount = 0;
    constCount = 0;
    opCount = 0;
}

void RecursiveDescentParser::printStmt() {
    cout << analyzer->getAccumulatedLexeme() << endl;
    cout << "ID: " << idCount << "; Const: " << constCount << "; OP: " << opCount << ";" << endl;
}

void RecursiveDescentParser::printResult() {
    cout << "Result ==> ";
    for (auto symbol : symbolTable) {
        cout << symbol.first << ": ";
        if (symbol.second.isUnknown) {
            cout << "Unknown";
        } else {
            cout << symbol.second.value;
        }
        cout << "; ";
    }
    cout << endl;
}
#include <iostream>
#include "../include/lex_analyzer.h"

using namespace std;

LexicalAnalyzer::LexicalAnalyzer(char* fname, bool debug) {
    if ((in_fp = fopen(fname, "r")) == NULL) {
        cout << "ERROR - cannot open " << fname << endl;
        exit(1);
    }

    this->debug = debug;
}

void LexicalAnalyzer::ready() {
    getChar();
    lex();
}

void LexicalAnalyzer::parse() {
    getChar();
    do {
        lex();
    } while (nextToken != EOF_TOKEN);
}

void LexicalAnalyzer::addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        cout << "ERROR - lexeme is too long" << endl;
    }
}

void LexicalAnalyzer::getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    } else {
        charClass = EOF_CHAR;
    }
}

void LexicalAnalyzer::getNonBlank() {
    while (nextChar >= 0 && nextChar <= 32)
        getChar();
}

LexicalAnalyzer::Token LexicalAnalyzer::lex() {
    accumulatedLexeme.append(string(lexeme));
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = CONST;
            break;
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
        case EOF_CHAR:
            nextToken = EOF_TOKEN;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    }
    
    if (debug)
        cout << "Next token is " << nextToken << ", Next lexeme is " << lexeme << endl;

    return nextToken;
}

LexicalAnalyzer::Token LexicalAnalyzer::lookup(char ch) {
    switch (ch) {
        case ':':
            addChar();
            getChar();
            if (nextChar == '=') {
                addChar();
                nextToken = ASSIGN_OP;
            } else {
                nextToken = EOF_TOKEN;
            }
            break;
        case ';':
            addChar();
            nextToken = SEMI;
            break;
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
        case '-':
            addChar();
            nextToken = ADD_OP;
            break;
        case '*':
        case '/':
            addChar();
            nextToken = MULT_OP;
            break;
        default:
            addChar();
            nextToken = EOF_TOKEN;
            break;
    }
    return nextToken;
}

LexicalAnalyzer::Token LexicalAnalyzer::getNextToken() {
    return nextToken;
}

char* LexicalAnalyzer::getLexeme() {
    return lexeme;
}

string LexicalAnalyzer::getAccumulatedLexeme() {
    if (charClass != EOF_CHAR) {
        accumulatedLexeme.append(string(lexeme));
    }

    return accumulatedLexeme;
}

void LexicalAnalyzer::initAccumulatedLexeme() {
    accumulatedLexeme = "";
}
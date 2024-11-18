#pragma once

#include <cstdio>

using namespace std;

class LexicalAnalyzer {
    public:
        enum Character {
            LETTER,
            DIGIT,
            UNKNOWN,
            EOF_CHAR
        };
        enum Token {
            CONST,
            IDENT,
            ASSIGN_OP,
            SEMI,
            ADD_OP,
            MULT_OP,
            LEFT_PAREN,
            RIGHT_PAREN,
            EOF_TOKEN
        };
    private:
        bool debug;
        FILE* in_fp;
        Character charClass;
        char lexeme[100];
        char nextChar;
        int lexLen;
        int token;
        Token nextToken;
        string accumulatedLexeme;

        void addChar();
        void getChar();
        void getNonBlank();
        Token lookup(char ch);

    public:
        LexicalAnalyzer(char* fname, bool debug=false);
        void ready();
        Token lex();
        void parse();
        Token getNextToken();
        string getAccumulatedLexeme();
        void initAccumulatedLexeme();
};
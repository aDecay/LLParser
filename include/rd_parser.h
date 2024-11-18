#pragma once

#include "../include/lex_analyzer.h"

class RecursiveDescentParser {
    private:
        bool debug;
        LexicalAnalyzer* analyzer;
        int idCount;
        int constCount;
        int opCount;

        void program();
        void statements();
        void statement();
        void expression();
        void term();
        void factor();
        void initStmt();
        void printStmt();

    public:
        RecursiveDescentParser(LexicalAnalyzer* analyzer, bool debug=false);
        void parse();
};
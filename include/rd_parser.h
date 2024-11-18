#pragma once

#include "../include/lex_analyzer.h"

class RecursiveDescentParser {
    private:
        LexicalAnalyzer* analyzer;
        void program();
        void statements();
        void statement();
        void expression();
        void term();
        void factor();

    public:
        RecursiveDescentParser(LexicalAnalyzer* analyzer);
        void parse();
};
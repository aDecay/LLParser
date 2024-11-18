#pragma once

#include <map>
#include "../include/lex_analyzer.h"
#include "../include/symbol_entry.h"

class RecursiveDescentParser {
    private:
        bool debug;
        LexicalAnalyzer* analyzer;
        int idCount;
        int constCount;
        int opCount;
        map<string, SymbolEntry> symbolTable;
        SymbolEntry symbolEntry;

        void program();
        void statements();
        void statement();
        SymbolEntry expression();
        SymbolEntry term();
        SymbolEntry factor();
        void initStmt();
        void printStmt();
        void printResult();

    public:
        RecursiveDescentParser(LexicalAnalyzer* analyzer, bool debug=false);
        void parse();
};
#include <iostream>
#include "../include/lex_analyzer.h"

using namespace std;

int main(int argc, char** argv) {
    FILE* in_fp;
    
    if (argc < 2) {
        cout << "ERROR - no input file" << endl;
        exit(1);
    }

    LexicalAnalyzer* analyzer = new LexicalAnalyzer(argv[1]);
    analyzer->parse();

    return 0;
}
#pragma once

struct SymbolEntry {
    int value;
    bool isUnknown;
    
    SymbolEntry();
    SymbolEntry(int value, bool inUnknown);
    SymbolEntry operator+(const SymbolEntry &s) const;
    SymbolEntry operator-(const SymbolEntry &s) const;
    SymbolEntry operator*(const SymbolEntry &s) const;
    SymbolEntry operator/(const SymbolEntry &s) const;
};
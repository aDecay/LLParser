#include "../include/symbol_entry.h"

SymbolEntry::SymbolEntry() : value(0), isUnknown(false) {}
SymbolEntry::SymbolEntry(int value, bool isUnknown) : value(value), isUnknown(isUnknown) {}

SymbolEntry SymbolEntry::operator+(const SymbolEntry &s) const {
    if (isUnknown || s.isUnknown) {
        return SymbolEntry(0, true);
    } else {
        return SymbolEntry(value + s.value, false);
    }
}

SymbolEntry SymbolEntry::operator-(const SymbolEntry &s) const {
    if (isUnknown || s.isUnknown) {
        return SymbolEntry(0, true);
    } else {
        return SymbolEntry(value - s.value, false);
    }
}

SymbolEntry SymbolEntry::operator*(const SymbolEntry &s) const {
    if (isUnknown || s.isUnknown) {
        return SymbolEntry(0, true);
    } else {
        return SymbolEntry(value * s.value, false);
    }
}

SymbolEntry SymbolEntry::operator/(const SymbolEntry &s) const {
    if (isUnknown || s.isUnknown || s.value == 0) {
        return SymbolEntry(0, true);
    } else {
        return SymbolEntry(value / s.value, false);
    }
}
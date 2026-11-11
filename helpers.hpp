#pragma once


constexpr bool isDigit(char& c) { return c >= '0' && c <= '9'; };
constexpr bool isHex(char c)   { return isDigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); };
constexpr bool isAlpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'; };
constexpr bool isAlnum(char c) { return isAlpha(c) || isDigit(c); };

constexpr bool validEscape(char c) {
    switch (c) {
    case 'n': case 't': case 'r': case '0':
    case '\\': case '"': case '\'':
        return true;
    default:
        return false;
    }
}
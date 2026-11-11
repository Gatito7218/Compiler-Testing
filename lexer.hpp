#pragma once
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <deque>
#include <variant>
#include <optional>
#include "helpers.hpp"

// TO-DO for later: string interner

namespace LEXER {
using POS = int*;


// Will use this for more complex tokenizing later
enum class Base {
    Binary = 2,
    Octal = 8,
    Decimal = 10,
    Hexidecimal = 16
};

struct LiteralType {
    enum class Tag {
        Int,
        Float,
        Char,
        Byte,
        Str,
        ByteStr,
        CStr,
        RawStr,
        RawByteStr,
        RawCStr
    };


    union Payload {
        struct {
            Base base;
            bool empty;
        } _int;

        struct {
            Base base;
            bool empty_exp;
        } _float;

        struct {
            bool terminate;
        } _char;

        struct {
            bool terminate;
        } byte;

        struct {
            bool terminate;
        } str;


        Payload() {}
        ~Payload() {}
    } payload;
};



enum class tokenType {
    BLOCKCOMMENT,
    LINECOMMENT,
    WHITESPACE,

    UNKNOWN,
    


    EndOfFile,
    IDENTIFIER,
    KEYWORD,
    LITERAL,

    Eq, At, Tilde, Colon, Semi, Comma,
    Dot, DotDot, DotDotDot, DotDotEq,
    Pound, Dollar, Questions,
    ModSep,

    OPERATOR,
    OPERATOREQ,

    OPEN_DELIMITER,
    CLOSED_DELIMITER
};


static const std::unordered_map<std::string_view, tokenType> keywords {
    {}, {}, {}, {}, {}, {}, 
};


struct Token {
    tokenType type; // type of token
    int len;
};

// TO-DO


struct Cursor {
    char* chars;
    char prev;
};

class Lexer {
    private:


        Cursor cursor;

        Token advance_token();
        std::vector<Token> tokenize();

    public:
        std::string filename;
        std::size_t pos;

        char advance();
        char peek();

};


}
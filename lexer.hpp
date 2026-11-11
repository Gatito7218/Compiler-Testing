#pragma once
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <deque>
#include <variant>
#include <optional>
#include <stdint.h>
#include "helpers.hpp"

// TO-DO for later: string interner

namespace LEXER {
using POS = int*;


// Will use this for more complex tokenizing later
/*
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
*/


enum class tokenType {
    BlockComment, LineComment, Whitespace,
    
    Identifier,
    Keywork,
    Literal,

    Semi, Comma, Dot, OpenParen, CloseParen, OpenBrace, CloseBrace,
    OpenBracket, CloseBracket, At, Pound, Tilde, Question, Colon, Dollar,
    Eq, Bang, Lt, Gt, Minus, And, Or, Plus, Star, Slash, Caret, Percent,
    Unknown, Eof
};

enum class literalKind {
    Int, Float, Char,
};

struct Token {
    tokenType kind; // type of token
    uint32_t len;
};

// TO-DO


struct Cursor {
    char* chars;
    char prev;
};

class Cursor {
    public:
        explicit Cursor(std::string_view src) : 
            begin(src.data()), curr(src.data()), end(src.data() + src.size()),
            start(src.data()) {}
        void beginToken() { start = curr; }
        uint32_t tokenLen() const {return static_cast<uint32_t>(curr - start); }

        char prev(); // Optional To-Do

        char first() const { return peek(0); }
        char second() const { return peek(1); }
        char third() const { return peek(2); }
        char bump() { 
            if (curr == end) return '\0';
            return *curr++;
        }
        bool eof() const { return curr == end; }

        template <class Pred>
        void eat(Pred&& p) { while(!eof() && p(*curr)) ++curr; }
    private:
        //Remove these
        std::string_view src_;
        char peek(std::size_t n) const {
            return static_cast<std::size_t>(end - curr) > n ? curr[n] : '\0';
        }


        const char* begin;
        const char* curr;
        const char* end;
        const char* start;
};





class Lexer {

    public:
        explicit Lexer(std::string_view src) : cursor(src) {}
        std::vector<Token> tokenize();
        Token advance_token();

        char advance();
        char peek();
    
    private:
        Cursor cursor;


        Token make(tokenType k) { return Token{k, cursor.tokenLen()}; }


        Token lineComment();
        Token blockComment();
        Token whitespace();
        Token number(char c);
        Token string();
        Token ident();
};


}
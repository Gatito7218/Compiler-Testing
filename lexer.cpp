#include "lexer.hpp"


using namespace LEXER;




// basic lexer, will need to add int size etc. later
Token Lexer::advance_token() {
    cursor.beginToken();
    if (cursor.eof()) return make(tokenType::Eof);

    char c = cursor.bump();

    switch(c) {
        case '/':
            if (cursor.first() == '/') return lineComment();
            if (cursor.first() == '*') return blockComment();
            return make(tokenType::Slash);
        case ' ': case '\t': case '\n': case '\r':
            return whitespace();
        case '"': return string();
        case '0': case '1': case '2': case '3': case '4': case '5': case '6':
        case '7': case '8': case '9':
            return number(c);

        case ';': return make(tokenType::Semi);
        case ',': return make(tokenType::Comma);
        case '.': return make(tokenType::Dot);
        case '(': return make(tokenType::OpenParen);
        case ')': return make(tokenType::CloseParen);
        case '{': return make(tokenType::OpenBrace);
        case '}': return make(tokenType::CloseBrace);
        case '[': return make(tokenType::OpenBracket);
        case ']': return make(tokenType::CloseBracket);
        case '@': return make(tokenType::At);
        case '#': return make(tokenType::Pound);
        case '~': return make(tokenType::Tilde);
        case '?': return make(tokenType::Question);
        case ':': return make(tokenType::Colon);
        case '$': return make(tokenType::Dollar);
        case '=': return make(tokenType::Eq);
        case '!': return make(tokenType::Bang);
        case '<': return make(tokenType::Lt);
        case '>': return make(tokenType::Gt);
        case '-': return make(tokenType::Minus);
        case '&': return make(tokenType::And);
        case '|': return make(tokenType::Or);
        case '+': return make(tokenType::Plus);
        case '*': return make(tokenType::Star);
        case '^': return make(tokenType::Caret);
        case '%': return make(tokenType::Percent);
        default:
            if (isAlpha(c)) return ident();
            return make(tokenType::Unknown);
    }
       
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (true) {
        tokens.push_back(advance_token());
        if (tokens.back().kind == tokenType::Eof) break;
    }
    return tokens;
}


Token Lexer::lineComment() {
    cursor.bump();
    cursor.eat([](char c) { return c != '\n'; });
    return make(tokenType::LineComment);
}

Token Lexer::whitespace() {
    cursor.eat([](char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; });
    return make(tokenType::Whitespace);
}

Token Lexer::ident() {
    cursor.eat(isAlnum);
    return make(tokenType::Identifier);
}


// Gonna take a bit to implement
Token Lexer::blockComment() {

}


Token Lexer::whitespace() {

}
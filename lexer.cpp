#include "lexer.hpp"


using namespace LEXER;





Token Lexer::advance_token() {
    Token newToken;

       
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (true) {
        tokens.push_back(advance_token());
        if (tokens.back().type == tokenType::EndOfFile) break;
    }
    return tokens;
}
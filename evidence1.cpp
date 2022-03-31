#include "functions.h"
using namespace std;

int main(){
    Lexer lex(Code::execute());
    for(auto token = lex.next();
        not token.is1of(Token::Type::End, Token::Type::Unexpected);
        token = lex.next()){
            HTML_Builder::buildHTML(string token.type(), string token.lexeme())
    }
}
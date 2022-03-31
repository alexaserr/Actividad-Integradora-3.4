#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Token{
    public:
        enum class Type{
            Number, Identifier, OPENpar, CLOSEpar, OPENcurly, CLOSEcurly, OPENsquare,
            CLOSEsquare, LessThan, MoreThan, Equal, Addition, Substraction, Multiplication,
            Division, Comment, Power, Comma, Colon, Semicolon, Space, Keyword, End, 
            Unexpected, Pipe, Dot, Quote, LoopKeyword, IfKeyword, FuncKeyword, DefKeyword,
        };

        Token(Type type) : m_type{type} {}

        Token(Type type, const char *prin, const char *end) 
            : m_type{type}, m_lexeme(prin, distance(prin, end)) {};

        Token(Type type, const char *prin, size_t length)
            : m_type{type}, m_lexeme(prin, length){};

        Type type(){
            return m_type;
        }

        void type(Type type){
            m_type = type;
        }

        bool is(Type type) const{
            return m_type == type;
        }

        bool aint(Type type) const{
            return m_type != type;
        }

        bool is1of(Type t1, Type t2) const{
            return is(t1) || is(t2);
        }

        template <typename... Ts>
        bool is1of(Type t1, Type t2, Ts...ts) const{
            return is(t1) || is1of(t2, ts...);
        }

        string lexeme() const{
            return m_lexeme;
        }

        void lexeme(string lexeme){
            m_lexeme = move(lexeme);
        }


    private:
        Type m_type{};
        string m_lexeme{};
};

class Lexer{
    public:
        Lexer(const char *prin) : m_prin{prin} {}
        Token next();

    private:
        Token identifier_or_keyword();
        Token number();
        Token isCom_or_isDiv();
        Token atom(Token::Type);

        char peek() const{return *m_prin;}
        char get(){return *m_prin++;}

        const char *m_prin = nullptr;
};

class HTML_Builder{
    public:
        void buildHTML(__cxx11::string, __cxx11::string){};
};

class Code{
    public:
        __cxx11::string execute(){};
};

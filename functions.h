#include "classes.h"

bool isNum(const char &str){
    switch (str){
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
        default:
            return false;
    }
}

bool isSpace(const char &str){
    switch(str){
        case ' ':
        case '\t':
        case '\r':
        case '\n':
            return true;
        default:
            return false;
    }
}

bool isVar_Char(const char &str){
    int asciiVal = (int)str;
    if ( (asciiVal <= 90 && asciiVal >= 65) || (asciiVal <= 122 && asciiVal >= 97) ){
        return true;
    }
    return false;
}

bool isKeyword(const char &str){
    string keyword;
    map<string, string>::iterator it;

    map<string, string> keywords = {{"for", "keyword"},
                                    {"while", "keyword"},
                                    {"if", "keyword"},
                                    {"else", "keyword"},
                                    {"elif", "keyword"},
                                    {"return", "keyword"},
                                    {"function", "keyword"},
                                    {"def", "keyword"},
                                    {"class", "keyword"},
                                    {"bool", "keyword"},
                                    {"int", "keyword"},
                                    {"vector", "keyword"},
                                    {"float", "keyword"},
                                    {"string", "keyword"},
                                    {"end", "keyword"},
                                    {"break", "keyword"},
                                    {"continue", "keyword"},
                                    {"false", "keyword"},
                                    {"true", "keyword"} };
    if(str != '\n'||'\t'||'\0'||' '){
        keyword += &str;
    }
    it = keywords.find(keyword);
    if(it != keywords.end()){
        return true;
    } else return false;

}

Token Lexer:: atom(Token::Type type){
    return Token(type, m_prin++, 1);
}

Token Lexer::next(){
    while(isSpace(peek())) get();
    switch(peek()){
        case '\0':
            return Token(Token::Type::End, m_prin, 1);
    default:
        return atom(Token::Type::Unexpected);
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
        return identifier_or_keyword();
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return number();
    case '(': 
        return atom(Token::Type::OPENpar);
    case ')': 
        return atom(Token::Type::CLOSEpar);
    case '[': 
        return atom(Token::Type::OPENsquare);
    case ']': 
        return atom(Token::Type::CLOSEsquare);
    case '{': 
        return atom(Token::Type::OPENcurly);
    case '}': 
        return atom(Token::Type::CLOSEcurly);
    case '<': 
        return atom(Token::Type::LessThan);
    case '>':
        return atom(Token::Type::MoreThan);
    case '=':  
        return atom(Token::Type::Equal);
    case '+': 
        return atom(Token::Type::Addition);
    case '-': 
        return atom(Token::Type::Substraction);
    case '*': 
        return atom(Token::Type::Multiplication);
    case '/': 
        return isCom_or_isDiv();
    case '#': 
        return atom(Token::Type::Comment);
    case '.': 
        return atom(Token::Type::Dot);
    case ',': 
        return atom(Token::Type::Comma);
    case ':': 
        return atom(Token::Type::Colon);
    case ';': 
        return atom(Token::Type::Semicolon);
    case '^': 
        return atom(Token::Type::Power);
    case '"': 
        return atom(Token::Type::Quote);
    case '|': 
        return atom(Token::Type::Pipe);
    }
}

Token Lexer::identifier_or_keyword(){
    const char *beginning = m_prin;
    get();
    while(isVar_Char(peek())){
        get();
        if(isKeyword(peek())){
                get();
                return Token(Token::Type::Keyword, beginning, m_prin);
        } else{
            get();
            return Token(Token::Type::Identifier, beginning, 1);
        }
    } return Token(Token::Type::Unexpected, m_prin, 1);
}

Token Lexer::isCom_or_isDiv(){
    const char *beginning = m_prin;
    get();
    if(peek()=='/'){
        get();
        beginning = m_prin;
        while(peek() != '\0'){
            if(get() == '\n'){
                return Token(Token::Type::Comment, beginning, distance(beginning, m_prin) -1);
            }
        } return Token(Token::Type::Unexpected, m_prin, 1);
    } else return Token(Token::Type::Division, beginning, 1);
}

Token Lexer::number(){
    const char *beginning = m_prin;
    get();
    while(isNum(peek())) get();
    return Token(Token::Type::Number, beginning, m_prin);
}

ostream &operator << (ostream &os, const Token::Type &type){
    static const char *const names[]{
        "Number",                "Identifier",           "Open Parenthesis",     "Closed Parenthesis", 
        "Open Curly Bracket",    "Close Curly Bracket",  "Open Square Bracket",  "Close Square Bracket",
        "Less Than",             "GreaterThan",          "Equal",                "Addition",
        "Substraction",          "Multiplication",       "Division",             "Comment",
        "Power",                 "Comma",                "Colon",                "Semicolon",
        "Space",                 "Keyword",              "End",                  "Unexpected",
        "Pipe",                  "Dot",                  "Quote"                 
    }; 
    return os << names[static_cast<int>(type)];
}

void HTML_Builder::buildHTML(string a, string b){
    ostream out("file.html");
    out << "<html>" << '\n' << "<head>" << '\n' <<"<title>" << "EVIDENCIA 1" << "</title>" << '\n' <<
           "</head>" << "<body>" << '\n';
    string cuerpo = cuerpo + "<div class=" + a + ">" + b + "</div" + "\n" + "<br><br>";
    out << cuerpo;
}

string Code::execute(){
    ostream newfile;
    newfile.open("test.txt");
    string tp;
    while(getline(newfile, tp)){
        return tp+"\n";
    }
}
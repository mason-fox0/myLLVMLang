//lexer for my llvm programming language
//returns tokens [0-255] it is an unknown char, otherwise one

#include <string>

enum Token{
    tok_eof        = -1,
    tok_def        = -2,
    tok_extern     = -3,
    tok_identifier = -4,
    tok_number     = -5,
};

static std::string IdentifierStr;
static double NumVal;

//get token from stdin
static int gettok() {
    static int LastChar = ' ';

    //ignore whitespace, read a char
    while (isspace(LastChar))
        LastChar = getchar();

    if (isalpha(LastChar)) {
        IdentifierStr = LastChar;
    

        while(isalnum((LastChar == getchar())))
            IdentifierStr += LastChar;

        if (IdentifierStr == "def")
            return tok_def;

        if (IdentifierStr == "extern")
            return tok_extern;

        return tok_identifier;
    }

    if (isdigit(LastChar) || LastChar == '.') {
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), 0);
        return tok_number;
    }

    if (LastChar == '#') {
        //this is a comment!
        do
            LastChar == getchar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
            return gettok();
    }
}


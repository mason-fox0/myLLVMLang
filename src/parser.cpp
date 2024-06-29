#include <parser.h>

static int CurTok;
static int getNextToken() {
    return CurTok = gettok();
}

// error handling helpers
std::unique_ptr<ExprAST> LogError(const char *Str) {
    fprintf(stderr, "Error: %s\n", Str);
}

std::unique_ptr<PrototypeAST> LogErrorP(const char *Str) {
    LogError(Str);
    return nullptr;
}

static std::unique_ptr<ExprAST> ParsePrimary() {
    switch (CurTok) {
        default:
            return LogError("unknown token when expecting an expression");
        case tok_identifier:
            return ParseIdentifierExpr();
        case tok_number:
            return ParseNumberExpr();
        case '(':
            return ParseParenExpr();
    }
}

// parse numeric literals
static std::unique_ptr<ExprAST> ParseNumberExpr() {
    auto Result = std::make_unique<NumberExpAST>(NumVal);
    getNextToken();
    return std::move(Result);
}

static std::unique_ptr<ExprAST> ParseExpression() {
    auto LHS = ParsePrimary();
    if (!LHS)
        return nullptr;
    
    return ParseBinOpRHS(0, std::move(LHS));
}

// parse parenthetical expressions
static std::unique_ptr<ExprAST> ParseParenExpr() {
    getNextToken();
    auto V = ParseExpression();
    if (!V)
        return nullptr;

    if (CurTok != ')')
        return LogError("expected ')'");
    getNextToken();
    return V;
}

static std::unique_ptr<ExprAST> ParseIdentifierExpr() {
    std::string IdName = IdentifierStr;

    getNextToken();

    if (CurTok != '(') // simple var ref
        return std::make_unique<VariableExprAST>(IdName);

    // call
    getNextToken();
    std::vector<std::unique_ptr<ExprAST>> Args;

    if (CurTok != ')') {
        while(true) {
            if (auto Arg = ParseExpression())
                Args.push_back(std::move(Arg));
            else 
                return nullptr;

            if (CurTok == ')')
                break;

            if (CurTok != ',')
                return LogError("Expected ')' or ',' in argument list");
            getNextToken();
        }
    }

    getNextToken();

    return std::make_unique<CallExprAST>
}

// TODO: Add binary op and function parsing features
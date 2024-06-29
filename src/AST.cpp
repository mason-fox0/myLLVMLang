#include <AST.h>

// Base class for expression nodes
class ExprAST {
public:
    virtual ~ExprAST() = default;
};

// Expression class for numeric literals
class NumberExpAST : public ExprAST {
    double Val;

public:
    NumberExpAST(double Val) : Val(Val) {}
};

// Expression class for variables
class VariableExprAST : public ExprAST {
    std::string Name;

public:
    VariableExprAST(const std::string &Name) : Name(Name) {}
};

// Expression class for binary operators
class BinaryExprAST : public ExprAST {
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS,
                  std::unique_ptr<ExprAST> RHS)
        : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

// Expression class for function call
class callExprAST : public ExprAST {
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;

public:
    callExprAST(const std::string &Callee,
                std::vector<std::unique_ptr<ExprAST>> Args)
            :Callee(Callee), Args(std::move(Args)) {}
};

// Represents function prototype (function and args)
class PrototypeAST {
    std::unique_ptr<PrototypeAST> Proto;
    std::unique_ptr<ExprAST> Body;

public:
    PrototypeAST(std::unique_ptr<PrototypeAST> Proto,
                 std::unique_ptr<ExprAST> Body)
        : Proto(std::move(Proto)), Body(std::move(Body)) {}
};

// Represents function definition
class FunctionAST {
    std::unique_ptr<PrototypeAST> Proto;
    std::unique_ptr<ExprAST> Body;

public:
    FunctionAST(std::unique_ptr<PrototypeAST> Proto,
                std::unique_ptr<ExprAST> Body)
        : Proto(std::move(Proto)), Body(std::move(Body)) {}
};
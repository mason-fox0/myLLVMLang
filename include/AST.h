#pragma once

#include <string>
#include <memory>
#include <vector>

// Base class for expression nodes
class ExprAST {
public:
    virtual ~ExprAST();
};

// Expression class for numeric literals
class NumberExpAST : public ExprAST {
private:
    double Val;

public:
    NumberExpAST(double Val);
};

// Expression class for variables
class VariableExprAST : public ExprAST {
private:
    std::string Name;

public:
    VariableExprAST(const std::string &Name);
};

// Expression class for binary operators
class BinaryExprAST : public ExprAST {
private:
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS,
                  std::unique_ptr<ExprAST> RHS);
};

// Expression class for function call
class CallExprAST : public ExprAST {
private:
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;

public:
    callExprAST(const std::string &Callee,
                std::vector<std::unique_ptr<ExprAST>> Args);
};

// Represents function prototype (function and args)
class PrototypeAST {
private:
    std::unique_ptr<PrototypeAST> Proto;
    std::unique_ptr<ExprAST> Body;

public:
    PrototypeAST(std::unique_ptr<PrototypeAST> Proto,
                 std::unique_ptr<ExprAST> Body);
};

// Represents function definition
class FunctionAST {
private:
    std::unique_ptr<PrototypeAST> Proto;
    std::unique_ptr<ExprAST> Body;

public:
    FunctionAST(std::unique_ptr<PrototypeAST> Proto,
                std::unique_ptr<ExprAST> Body);
};
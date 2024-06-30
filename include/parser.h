#pragma once
#include <lexer.h>
#include <AST.h>
#include <map>

static int getNextToken();
static int GetTokPrecedence();
static std::map<char, int> BinopPrecedence;

std::unique_ptr<ExprAST> LogError(const char *Str);
std::unique_ptr<PrototypeAST> LogErrorP(const char *Str);

static std::unique_ptr<ExprAST> ParseExpression();
static std::unique_ptr<ExprAST> ParsePrimary();

static std::unique_ptr<ExprAST> ParseNumberExpr();
static std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec,
                                              std::unique_ptr<ExprAST> LHS);
static std::unique_ptr<ExprAST> ParseParenExpr();
static std::unique_ptr<ExprAST> ParseIdentifierExpr();

static std::unique_ptr<PrototypeAST> ParsePrototype();
static std::unique_ptr<FunctionAST> ParseDefinition();
static std::unique_ptr<PrototypeAST> ParseExtern();

static std::unique_ptr<FunctionAST> ParseTopLevelExpr();

static void HandleDefinition();
static void HandleExtern();
static void HandleTopLevelExpression();

static void MainLoop();
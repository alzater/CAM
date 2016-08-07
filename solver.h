#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <map>
#include <tuple>
#include <memory>
#include "token.h"
#include <iostream>


typedef TStr* Term;
typedef TStr* Code;
typedef std::vector<TStr*> Stack;

class Line
{
public:
    Line( Term term, Code code );
    ~Line();

public:
    Term   term (){ return _term;  }
    Code   code (){ return _code;  }
    Stack& stack(){ return _stack; }

public:
    void setTerm ( Term   term  ) { _term  = term;             }
    void setCode ( Code   code  ) { _code  = code;             }
    void setStack( Stack& stack ) { _stack = std::move(stack); }

public:
    void print() const;

private:
    Term  _term;
    Code  _code;
    Stack _stack;
};

//typedef std::tuple< Term, Code, Stack > TLine;

class Solver
{
public:
    Solver(TStr* str);
    ~Solver();

    void makeSteps( int steps );
    bool makeStep();

private:
    void doApp();
    void doCar();
    void doCdr();
    void doCons();
    void doCur();
    void doPush();
    void doQuote();
    void doSwap();
    void doOperation();
    void doBranch();
    void doRec();
    void doNothing();
private:
    int _qMem;
    Line _line;
    std::vector<TStr> _mem;
};

#endif // SOLVER_H

#include "solver.h"
#include "tstr.h"

#include <functional>
#include <iostream>

Solver::Solver( TStr* code )
    : _qMem(0)
    , _line( new TStr("()"), code )
{
    _line.print();
}

Solver::~Solver()
{}

void Solver::makeSteps( int steps )
{
    while(steps--)
    {
        if (makeStep())
            break;
    }
}


bool Solver::makeStep()
{

    if( _line.code()->size() == 0 )
        return true;

    switch(_line.code()->back()->getType())
    {
    case TokenType::APP:       doApp();       break;
    case TokenType::CAR:       doCar();       break;
    case TokenType::CDR:       doCdr();       break;
    case TokenType::CONS:      doCons(); 	  break;
    case TokenType::CUR:       doCur();       break;
    case TokenType::PUSH:      doPush(); 	  break;
    case TokenType::QUOTE:     doQuote();  	  break;
    case TokenType::SWAP:      doSwap();      break;
    case TokenType::OPERATION: doOperation(); break;
    case TokenType::BRANCH:    doBranch();    break;
    case TokenType::REC:       doRec();       break;
    default:
        doNothing();
        break;
    }

    _line.print();

    return false;
}

void Solver::doNothing()
{
    _line.code()->delAndPop();
}

void Solver::doCar()
{
    _line.code()->delAndPop();

    TStr* tmp = _line.term();
    _line.setTerm( tmp->back()->first() );

    tmp->back()->setFirst(nullptr);
    delete tmp;
}

void Solver::doCdr()
{
    _line.code()->delAndPop();

    TStr* tmp = _line.term();
    _line.setTerm( tmp->back()->second() );

    tmp->back()->setSecond(nullptr);
    delete tmp;
}

void Solver::doCons()
{
    _line.code()->delAndPop();

    Token* pair = new Token(TokenType::PAIR);

    pair->setFirst(_line.stack().back() );
    _line.stack().pop_back();

    pair->setSecond(_line.term());

    Term term(new TStr());
    term->push(pair);
    _line.setTerm(term);
}

void Solver::doPush()
{
    _line.code()->delAndPop();

    TStr* term = _line.term()->copy();
    _line.stack().push_back(term);
}

void Solver::doQuote()
{
    delete _line.term();

    Term term = new TStr;
    term->push(_line.code()->back());
    _line.setTerm(term);
    _line.code()->pop();
}

void Solver::doSwap()
{
    _line.code()->delAndPop();

    Term term = _line.term();
    _line.setTerm(_line.stack().back());
    _line.stack().back() = term;
}

void Solver::doCur()
{
    Token* colon = new Token(TokenType::COLON);
    colon->setData(_line.code()->back()->data());
    colon->setTerm(_line.term());

    TStr* term = new TStr;
    term->push(colon);
    _line.setTerm(term);

    _line.code()->back()->setData( nullptr );
    _line.code()->delAndPop();
}

void Solver::doApp()
{
    _line.code()->delAndPop();

    Token* colon;
    if ( _line.term()->back()->getType() == TokenType::PAIR )
    {
        Token* pair = _line.term()->back();

        if ( pair->first()->back()->getType() == TokenType::REF ) {
            Token* newPair = new Token(TokenType::PAIR);
            TStr* forPush = new TStr;
            forPush->push(pair->first()->back());
            newPair->setSecond(forPush);
            pair->first()->pop();

            Term t = new TStr("()");
            newPair->setFirst(t);

            colon = new Token(TokenType::COLON);

            Term data = _mem[forPush->back()->getRef()].copy();
            colon->setData(data);

            Term term = new TStr();
            term->push( newPair );
            colon->setTerm(term);
        }
        else
        {
            colon = pair->first()->back();
            pair->first()->pop();
        }

        delete pair->first();
        pair->setFirst(colon->term());
        colon->setTerm( nullptr );
    }
    else
    {
        colon = _line.term()->back();
        _line.term()->pop();
        delete _line.term();
        _line.setTerm(colon->term());
    }

    _line.code()->push(colon->data());
    colon->setData( nullptr );
    delete colon;
}

void Solver::doOperation()
{
    Token* pair      = _line.term()->back();
    Token* first     = pair->first()->back();
    Token* second    = pair->second()->back();
    Token* operation = _line.code()->back();

    int res;
    switch (operation->operation()) {
        case '+': res = first->getNumber() +  second->getNumber(); break;
        case '*': res = first->getNumber() *  second->getNumber(); break;
        case '-': res = first->getNumber() -  second->getNumber(); break;
        case '=': res = first->getNumber() == second->getNumber(); break;
        default:
            break;
    }

    Token* resToken = new Token(TokenType::QUOTE);
    resToken->setNumber(res);
    _line.term()->delAndPop();
    _line.term()->push(resToken);

    _line.code()->delAndPop();
}

void Solver::doBranch()
{
    bool val = _line.term()->back()->getBool();

    Token* branch = _line.code()->back();
    _line.code()->pop();

    if ( val )
    {
        _line.code()->push(branch->first());
        branch->setFirst( nullptr );
    }
    else
    {
        _line.code()->push(branch->second());
        branch->setSecond( nullptr );
    }
    delete branch;

    delete _line.term();
    _line.setTerm(_line.stack().back());
    _line.stack().pop_back();
}

void Solver::doRec()
{
    Token* rec = _line.code()->back();
    _mem.push_back(*rec->data());
    rec->setData(nullptr);
    _line.code()->delAndPop();

    _line.term()->clear();

    Token* ref = new Token(TokenType::REF);
    ref->setRef(_qMem);
    ++_qMem;

    _line.term()->push(ref);
}

Line::Line( Term term, Code code )
{
    _term = term;
    _code = code;
}

Line::~Line()
{
    delete _term;
    delete _code;
    for ( size_t i = 0; i < _stack.size(); ++i )
        delete _stack[i];
}

void Line::print() const
{
    std::cout << "T: ";
    _term->print();
    std::cout << "    C: ";
    _code->print();
    std::cout << "    S: ";
    for ( const auto & item : _stack )
    {
        item->print();
        std::cout << ';';
    }
    std::cout << '\n';
}

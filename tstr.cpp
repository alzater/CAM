#include "tstr.h"

#include <iostream>
#include <algorithm>

TStr::TStr()
{}

TStr::~TStr()
{
    for ( size_t i = 0; i < _data.size(); ++i )
        delete _data[i];
}

TStr::TStr(std::string str)
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] == '\'') {
            getConstant(str, i);
            continue;
        }
        if (str[i] == '\\') {
            getCur(str, i);
            continue;
        }
        if (str[i] == 'E') {
            Token* token = new Token(TokenType::APP);
            _data.push_back(token);
            continue;
        }
        if (str[i] == '<') {
            Token* token = new Token(TokenType::PUSH);
            _data.push_back(token);
            continue;
        }
        if (str[i] == '>') {
            Token* token = new Token(TokenType::CONS);
            _data.push_back(token);
            continue;
        }
        if (str[i] == ',') {
            Token* token = new Token(TokenType::SWAP);
            _data.push_back(token);
            continue;
        }
        if (str[i] == ')') {
            Token* token = new Token(TokenType::RBR);
            _data.push_back(token);
            continue;
        }
        if (str[i] == '(') {
            Token* token = new Token(TokenType::LBR);
            _data.push_back(token);
            continue;
        }
        if (str[i] == 'F') {
            Token* token = new Token(TokenType::CAR);
            _data.push_back(token);
            continue;
        }
        if (str[i] == 'S') {
            Token* token = new Token(TokenType::CDR);
            _data.push_back(token);
            continue;
        }
        if (str[i] == 'I') {
            Token* token = new Token(TokenType::IF);
            _data.push_back(token);
            continue;
        }
        if (str[i] == 'Y') {
            getY(str, i);
            continue;
        }
        if (str[i] == 'B') {
            getBranch(str, i);
            continue;
        }
        if (str[i] == '+' ||
            str[i] == '-' ||
            str[i] == '*' ||
            str[i] == '='
           ) {
            Token* token = new Token(TokenType::OPERATION);
            token->setOperation(str[i]);
            _data.push_back(token);

            continue;
        }
    }
    std::reverse(_data.begin(), _data.end());
}

TStr* TStr::copy() const
{
    TStr* cp = new TStr;
    for ( size_t i = 0; i < _data.size(); ++i )
        cp->push(_data[i]->copy());
    return cp;
}

void TStr::print()
{
    for(int i = _data.size() - 1; i >= 0; --i)
        std::cout << _data[i]->to_string();
}

std::string TStr::to_string()
{
    std::string res;
    for(int i = _data.size() - 1; i >= 0; --i)
        res += _data[i]->to_string();
    return res;
}

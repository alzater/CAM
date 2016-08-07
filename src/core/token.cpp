#include "token.h"
#include "tstr.h"

// ------------------------------------------------------------

Token::Token( TokenType type)
    : _type( type )
    , _first( nullptr )
    , _second( nullptr )
{}

// ------------------------------------------------------------

Token::~Token()
{
    if ( _first != nullptr )
        delete _first;
    if ( _second != nullptr )
        delete _second;
}

// ------------------------------------------------------------

Token* Token::copy() const
{
    Token* cp = new Token( _type );

    if ( _first )
        cp->setFirst( _first->copy() );
    if ( _second )
        cp->setSecond( _second->copy() );

    cp->setBool( _boolValue );
    cp->setNumber( _number );
    cp->setRef(_ref);

    return cp;
}

// ------------------------------------------------------------

TokenType Token::getType() const
{
    return _type;
}

// ------------------------------------------------------------

void Token::setType(TokenType type)
{
    _type = type;
}

// ------------------------------------------------------------

std::string Token::to_string()
{
    std::string res;
    switch (_type) {
    case TokenType::NUMBER:
        res = "'" + std::to_string(_number);
        break;
    case TokenType::CAR:
        res = "F";
        break;
    case TokenType::CDR:
        res = "S";
        break;
    case TokenType::PUSH:
        res = "<";
        break;
    case TokenType::SWAP:
        res = ",";
        break;
    case TokenType::CONS:
        res = ">";
        break;
    case TokenType::APP:
        res = "E";
        break;
    case TokenType::CUR:
        res = "CUR";
        break;
    case TokenType::QUOTE:
        res = "'" + std::to_string(_number);
        break;
    case TokenType::LBR:
        res = "(";
        break;
    case TokenType::RBR:
        res = ")";
        break;
    case TokenType::COLON:
        res = "(" + _first->to_string() + "):(" + _second->to_string() + ")";
        break;
    case TokenType::PAIR:
        res = "(" + _first->to_string() + "," + _second->to_string() + ")";
        break;
    case TokenType::OPERATION:
        res = "O";
        break;
    case TokenType::IF:
        res = "I";
        break;
    case TokenType::BRANCH:
        res = "B(" + _first->to_string() + ")(" + _second->to_string() + ")";
        break;
    case TokenType::REC:
        res = "REC";
        break;
    case TokenType::REF:
        res = "REF";
        break;
    default:
        break;
    }

    return res;
}

// ------------------------------------------------------------

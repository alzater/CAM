#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <memory>

enum class TokenType {
    CAR,
    CDR,
    PUSH,
    SWAP,
    CONS,
    APP,
    CUR,
    QUOTE,
    LBR,
    RBR,
    COLON,
    PAIR,
    NUMBER,
    OPERATION,
    IF,
    BRANCH,
    REC,
    REF
};

class TStr;
typedef int Num;

class Token;

class Token
{
public:
    Token( TokenType type);
    ~Token();

    Token* copy() const;

    TokenType getType() const;
    void setType(TokenType type);

    std::string to_string();
    void print() const;

public:
    inline TStr* first ()   { return _first; }
    inline TStr* second()   { return _second; }
    inline TStr* data()     { return _first; }
    inline TStr* term()     { return _second; }
    inline Num&  getNumber(){ return _number; }
    inline char operation() { return (char)_number; }
    inline bool getBool()   { return (bool)_number; }
    inline int getRef()     { return _ref; }

public:
    inline void setFirst( TStr* str) { _first = str; }
    inline void setSecond(TStr* str) { _second = str; }
    inline void setData(TStr* str) { _first = str; }
    inline void setTerm(TStr* str) { _second = str; }
    inline void setNumber(const Num & num ) { _number = num; }
    inline void setBool(bool b) { _boolValue = b; }
    inline void setOperation(char c) { _number = (int)c; }
    inline void setRef(int ref) { _ref = ref; }

private:
    TokenType _type;

private:
    TStr *_first;
    TStr *_second;
    bool _boolValue;
    Num _number;
    int _ref;
};

#endif // TOKEN_H

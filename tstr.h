#ifndef TSTR_H
#define TSTR_H

#include "token.h"

#include <vector>
#include <memory>

class TStr;

class TStr
{
private:
    std::vector<Token*> _data;

public:
    TStr();
    TStr( std::string str );
    ~TStr();
    TStr* copy() const;

public:
    std::vector<Token*> & getData()
    {
        return _data;
    }

    void push(Token* token)
    {
        _data.push_back( token );
    }

    void push(TStr* str)
    {
        auto tmp = str->getData();
        for ( size_t i = 0; i < tmp.size(); ++i )
            _data.push_back( tmp[i] );
    }

    void delAndPop()
    {
        delete _data.back();
        _data.pop_back();
    }

    void pop()
    {
        _data.pop_back();
    }

    inline Token* back()
    {
        return _data[_data.size() - 1];
    }

public:
    void clear()
    {
        for ( size_t i = 0; i < _data.size(); ++i )
            delete _data[i];
        _data.clear();
    }

    inline size_t size()
    {
        return _data.size();
    }

public:
    void print();
    std::string to_string();

private:
    inline bool isNum(char ch) {
        if(ch <= '9' && ch >= '0')
            return true;
        return false;
    }

    inline void getConstant( const std::string& str, size_t& index )
    {
        int res=0;
        while(isNum(str[++index]))
        {
            res *= 10;
            res += str[index] - '0';
        }
        --index;

        _data.emplace_back(new Token(TokenType::QUOTE));
        _data.back()->setNumber(res);
    }

    inline void getCur( const std::string& str, size_t& index )
    {
        index += 2;
        int qBr = 1;

        std::string res;
        while (str[index] != ')' || qBr != 1  )
        {
            if(str[index] == '(')
                ++qBr;
            if(str[index] == ')')
                --qBr;
            res.push_back(str[index]);
            ++index;
        }

        TStr* t = new TStr(res);
        Token* token = new Token(TokenType::CUR);
        token->setData(t);

        _data.push_back(token);
    }

    inline void getY( const std::string& str, size_t& index )
    {
        index += 2;
        int qBr = 1;

        std::string res;
        while (str[index] != ')' || qBr != 1  )
        {
            if(str[index] == '(')
                ++qBr;
            if(str[index] == ')')
                --qBr;
            res.push_back(str[index]);
            ++index;
        }

        TStr* t = new TStr(res);
        Token* token = new Token(TokenType::REC);
        token->setData(t);

        _data.push_back(token);
    }

    inline void getBranch( const std::string& str, size_t& index )
    {
        index += 3;
        int qBr = 1;

        std::string res;
        while (str[index] != ')' || qBr != 1  )
        {
            if(str[index] == '(')
                ++qBr;
            if(str[index] == ')')
                --qBr;
            res.push_back(str[index]);
            ++index;
        }

        Token* token = new Token(TokenType::BRANCH);

        TStr* first = new TStr(res);
        token->setFirst(first);
        res.clear();

        index += 3;
        qBr = 1;

        while (str[index] != ')' || qBr != 1  )
        {
            if(str[index] == '(')
                ++qBr;
            if(str[index] == ')')
                --qBr;
            res.push_back(str[index]);
            ++index;
        }
        ++index;

        TStr* second = new TStr(res);
        token->setSecond(second);

        _data.push_back(token);
    }
};

#endif // TSTR_H

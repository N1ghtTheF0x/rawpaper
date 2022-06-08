#include <ptoken.hpp>

namespace PScript
{
    PToken::PToken(PTokenType t,std::string l,const void* d,int line)
    {
        this->type = t,this->lexeme = l,this->literal = d,this->line = line;
    }
    PTokenType PToken::getTokenType() const
    {
        return type;
    }
    std::string PToken::getString() const
    {
        return lexeme;
    }
    const void* PToken::getData() const
    {
        return literal;
    }
    int PToken::getLine() const
    {
        return line;
    }
}
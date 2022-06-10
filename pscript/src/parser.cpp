#include <cstdarg>
#include <pparser.hpp>


namespace PScript
{
    PParser::PParser(PTokens t): tokens(t)
    {

    }

    PExpr PParser::expression()
    {
        return equality();
    }

    PExpr PParser::equality()
    {

    }

    bool PParser::match(PTokenType types,...)
    {
        va_list args;
        va_start(args,types);
        for(const PTokenType &type : args)
        {
            
        }
        va_end(args);
        return false;
    }
}
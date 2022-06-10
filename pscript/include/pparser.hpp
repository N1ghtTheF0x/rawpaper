#if !defined(PSCRIPT_PARSER)
#define PSCRIPT_PARSER

#include "../src/helper.hpp"

#include "pexpr.hpp"

namespace PScript
{
    class PParser
    {
    private:
        PTokens tokens;
        int current = 0;

        PExpr expression();
        PExpr equality();
        bool match(PTokenType,...);
    public:
        PParser(PTokens);
    };
}

#endif
#if !defined(PSCRIPT_EXPR)
#define PSCRIPT_EXPR

#include "../src/helper.hpp"

#include "ptoken.hpp"

namespace PScript
{
    class PExpr;
}

namespace PScript
{
    class PExpr
    {
    private:

    public:
        PExpr();
    };
    class PExprBinary : public PExpr
    {
    private:
        PExpr left;
        PToken opcode = PToken(PTokenType::Null,"",nullptr,-1);
        PExpr right;
    public:
        PExprBinary(PExpr,PToken,PExpr);
    };
}

#endif
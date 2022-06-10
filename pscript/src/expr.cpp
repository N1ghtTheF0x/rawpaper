#include <pexpr.hpp>

namespace PScript
{
    PExpr::PExpr()
    {

    }
    PExprBinary::PExprBinary(PExpr l,PToken t,PExpr r): PExpr()
    {
        left = l;
        opcode = t;
        right = r;
    }
}
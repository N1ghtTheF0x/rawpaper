#if !defined(PSCRIPT_SCANNER)
#define PSCRIPT_SCANNER

#include "../src/helper.hpp"
#include "ptoken.hpp"

namespace PScript
{
    class PScanner
    {
    private:
        std::string source;
        PTokens tokens = PTokens();
        int start = 0;
        int current = 0;
        int line = 1;
        bool isAtEnd();
        void scanToken();
        char advance();
        void addToken(PTokenType);
        void addToken(PTokenType,const void*);
    public:
        PScanner(std::string);
        PTokens scanTokens();
    };
}

#endif
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
        char peek();
        char peekNext();
        void scanToken();
        char advance();
        bool match(char);
        bool isDigit(char);
        bool isAlpha(char);
        bool isAlphaNumberic(char);
        void addToken(PTokenType);
        void addToken(PTokenType,const void*);

        void string();
        void number();
        void identifier();
    public:
        PScanner(std::string);
        PTokens scanTokens();
    };
}

#endif
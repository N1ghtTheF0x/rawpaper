#if !defined(PSCRIPT_TOKEN)
#define PSCRIPT_TOKEN

#include "../src/helper.hpp"

namespace PScript
{
    enum class PTokenType
    {
        LeftParan,RightParan,LeftBrace,RightBrace,
        Comma,Dot,Minus,Plus,Semicolon,Slash,Star,

        Bang,BangEqual,
        Equal,EqualEqual,
        Greater,GreaterEqual,
        Less,LessEqueal,

        Identifier,String,Number,

        And,Class,Else,False,Function,For,If,Null,Or,
        Print,Return,Super,This,True,Var,WHile,EndOfFile
    };

    class PToken
    {
    private:
        PTokenType type;
        std::string lexeme;
        const void* literal;
        int line;
    public:
        PToken(PTokenType,std::string,const void*,int);
        PTokenType getTokenType() const;
        std::string getString() const;
        const void* getData() const;
        int getLine() const;
    };

    typedef std::list<PToken> PTokens;
}

#endif
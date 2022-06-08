#include <pscanner.hpp>
#include <putils.hpp>

namespace PScript
{
    PScanner::PScanner(std::string s)
    {
        source = s;
    }
    bool PScanner::isAtEnd()
    {
        return current >= source.length();
    }
    char PScanner::advance()
    {
        return source.at(current++);
    }
    void PScanner::scanToken()
    {
        char c = advance();
        switch(c)
        {
            case '(': addToken(PTokenType::LeftParan);break;
            case ')': addToken(PTokenType::RightParan);break;
            case '{': addToken(PTokenType::LeftBrace);break;
            case '}': addToken(PTokenType::RightBrace);break;
            case ',': addToken(PTokenType::Comma);break;
            case '.': addToken(PTokenType::Dot);break;
            case '-': addToken(PTokenType::Minus);break;
            case '+': addToken(PTokenType::Plus);break;
            case ';': addToken(PTokenType::Semicolon);break;
            case '*': addToken(PTokenType::Star);break;
            default:
            {
                THROW_PE("pscript","Unexpected character at line "+line);
            }
        }
    }
    void PScanner::addToken(PTokenType type)
    {
        addToken(type,nullptr);
    }
    void PScanner::addToken(PTokenType type,const void* data)
    {
        std::string text = source.substr(start,current);
        tokens.push_back(PToken(type,text,data,line));
    }

    PTokens PScanner::scanTokens()
    {
        while(!isAtEnd())
        {
            start = current;
            scanToken();
        }

        tokens.push_back(PToken(PTokenType::EndOfFile,"",nullptr,line));
        return tokens;
    }
}
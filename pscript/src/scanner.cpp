#include <pscanner.hpp>
#include <putils.hpp>

namespace PScript
{
    const PKeywords keywords = {
        {"and",PTokenType::And},
        {"class",PTokenType::Class},
        {"else",PTokenType::Else},
        {"false",PTokenType::False},
        {"for",PTokenType::For},
        {"function",PTokenType::Function},
        {"if",PTokenType::If},
        {"null",PTokenType::Null},
        {"or",PTokenType::Or},
        {"print",PTokenType::Print},
        {"return",PTokenType::Return},
        {"super",PTokenType::Super},
        {"this",PTokenType::This},
        {"true",PTokenType::True},
        {"var",PTokenType::Var},
        {"while",PTokenType::While},
    };

    PScanner::PScanner(std::string s)
    {
        source = s;
    }
    bool PScanner::isAtEnd()
    {
        return current >= source.length();
    }
    bool PScanner::match(char exspected)
    {
        if(isAtEnd()) return false;
        if(source.at(current) != exspected) return false;
        current++;
        return true;
    }
    bool PScanner::isDigit(char c)
    {
        return c >= '0' && c <= '9';
    }
    bool PScanner::isAlpha(char c)
    {
        return (c >= 'a' && c >= 'z') ||
               (c >= 'A' && c >= 'Z') ||
               (c == '_');
    }
    bool PScanner::isAlphaNumberic(char c)
    {
        return isAlpha(c) || isDigit(c);
    }
    char PScanner::peek()
    {
        if(isAtEnd()) return '\0';
        return source.at(current);
    }
    char PScanner::peekNext()
    {
        if(current + 1 >= source.length()) return '\0';
        return source.at(current+1);
    }
    void PScanner::number()
    {
        while(isDigit(peek())) advance();

        if(peek() == '.' && isDigit(peekNext()))
        {
            advance();
            while(isDigit(peek())) advance();
        }
        std::string stringNumber = source.substr(start,current-start);
        double number = std::stod(stringNumber);
        addToken(PTokenType::Number,new double(number));
    }
    void PScanner::string()
    {
        while(peek() != '"' && !isAtEnd())
        {
            if(peek() == '\n') line++;
            advance();
        }
        if(isAtEnd()) THROW_PE("pscript","String with no end detected!");
        advance();

        std::string value = source.substr(start+1,current-1-start);
        addToken(PTokenType::String,value.c_str());
    }
    void PScanner::identifier()
    {
        while(isAlphaNumberic(peek())) advance();

        std::string text = source.substr(start,current-start);
        PTokenType type = keywords.find(text) != keywords.end() ? keywords.at(text) : PTokenType::Identifier;

        addToken(type);
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
            case '!': addToken(match('=') ? PTokenType::InvertEqual : PTokenType::Invert);break;
            case '=': addToken(match('=') ? PTokenType::EqualEqual : PTokenType::Equal);break;
            case '<': addToken(match('=') ? PTokenType::LessEqual : PTokenType::Less);break;
            case '>': addToken(match('=') ? PTokenType::GreaterEqual : PTokenType::Greater);break;
            case '/':
            {
                if(match('/'))
                {
                    // Comment
                    while(peek() != '\n' && !isAtEnd()) advance();
                }
                else addToken(PTokenType::Slash);
                break;
            }
            case ' ':
            case '\r':
            case '\t':
                break;
            case '\n': line++;break;
            default:
            {
                if(isDigit(c))
                {
                    number();
                    break;
                }
                else if(isAlpha(c))
                {
                    identifier();
                    break;
                }
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
        std::string text = source.substr(start,current-start);
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
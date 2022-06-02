#include "putils.hpp"

#include <sstream>
#include <string>

namespace PUtils
{
    PException::PException(const char* type,const char* msg,const char* file,int line): std::runtime_error(msg)
    {
        std::ostringstream o;
        o << file << ":" << line << " - [" << type << "] " << msg;
        std::string s = o.str();
        this->msg = s.c_str();
    }
    PException::~PException(){}
    const char* PException::what() const throw() 
    {
        return msg;
    }
}
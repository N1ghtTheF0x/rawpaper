#include "putils.hpp"

#include <sstream>
#include <string>

namespace PUtils
{
    PException::PException(std::string type,std::string msg,std::string file,int line): std::runtime_error(msg)
    {
        std::ostringstream o;
        o << file << ":" << line << " - [" << type << "] " << msg;
        msg = o.str();
    }
    PException::~PException(){}
    const char* PException::what() const throw() 
    {
        return msg.c_str();
    }
}
#if !defined(PUTILS_HEADER)
#define PUTILS_HEADER

#include <stdexcept>
#include <string>

namespace PUtils
{
    class PException : public std::runtime_error
    {
    private:
        std::string msg;
    public:
        PException(std::string type,std::string msg,std::string file,int line);
        ~PException() throw();
        const char* what() const throw();
    };
    
}

#define THROW_PE(type,arg) throw PUtils::PException(type,arg,__FILE__,__LINE__);

#endif
#if !defined(PUTILS_HEADER)
#define PUTILS_HEADER

#include <stdexcept>

namespace PUtils
{
    class PException : public std::runtime_error
    {
    private:
        const char* msg;
    public:
        PException(const char* type,const char* msg,const char* file,int line);
        ~PException() throw();
        const char* what() const throw();
    };
    
}

#define THROW_PE(type,arg) throw PUtils::PException(type,arg,__FILE__,__LINE__);

#endif
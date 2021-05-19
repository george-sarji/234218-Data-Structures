#include <exception>

namespace structures
{

    enum ERRORS
    {
        MEMORY_ERROR,
        INVALID_INPUT,
        FAILURE
    };
    class Exception : public std::exception
    {
    public:
        Exception() = default;
        ~Exception() = default;
        virtual const ERRORS errorType() const noexcept;
    };

    class MemoryError : public Exception
    {
    public:
        const ERRORS errorType() const noexcept;
    };
    class InvalidInput : public Exception
    {
    public:
        const ERRORS errorType() const noexcept;
    };
    class FailureError : public Exception
    {
    public:
        const ERRORS errorType() const noexcept;
    };
}
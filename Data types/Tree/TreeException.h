#ifndef TREE_EXCEPTION_H_
#define TREE_EXCEPTION_H_

#include <exception>

namespace structures
{
    enum ERRORS
    {
        ALREADY_EXISTS,
        DOESNT_EXIST,
        NON_SPECIFIC
    };

    class TreeException : public std::exception
    {
    public:
        TreeException() = default;
        ~TreeException() = default;
        virtual const ERRORS errorType() const noexcept;
    };

    class AlreadyExists : public TreeException
    {
    public:
        const ERRORS errorType() const noexcept;
    };

    class DoesntExist : public TreeException
    {
    public:
        const ERRORS errorType() const noexcept;
    };
}

#endif
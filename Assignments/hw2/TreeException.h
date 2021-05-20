#ifndef TREE_EXCEPTION_H_
#define TREE_EXCEPTION_H_

#include <exception>

namespace structures
{
    enum TREE_ERROR
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
        virtual const TREE_ERROR errorType() const noexcept;
    };

    class AlreadyExists : public TreeException
    {
    public:
        const TREE_ERROR errorType() const noexcept;
    };

    class DoesntExist : public TreeException
    {
    public:
        const TREE_ERROR errorType() const noexcept;
    };
}

#endif
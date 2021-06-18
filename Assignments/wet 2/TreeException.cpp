#include "TreeException.h"

namespace structures
{
    const TREE_ERROR structures::TreeException::errorType() const noexcept
    {
        return NON_SPECIFIC;
    }

    const TREE_ERROR structures::AlreadyExists::errorType() const noexcept
    {
        return ALREADY_EXISTS;
    }

    const TREE_ERROR structures::DoesntExist::errorType() const noexcept
    {
        return DOESNT_EXIST;
    }
}
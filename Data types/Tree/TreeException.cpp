#include "TreeException.h"

namespace structures
{
    const ERRORS structures::TreeException::errorType() const noexcept
    {
        return NON_SPECIFIC;
    }

    const ERRORS structures::AlreadyExists::errorType() const noexcept
    {
        return ALREADY_EXISTS;
    }

    const ERRORS structures::DoesntExist::errorType() const noexcept
    {
        return DOESNT_EXIST;
    }
}
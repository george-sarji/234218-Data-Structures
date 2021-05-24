#include "Exception.h"

namespace structures
{
    const structures::ERRORS structures::MemoryError::errorType() const noexcept
    {
        return MEMORY_ERROR;
    }

    const structures::ERRORS structures::FailureError::errorType() const noexcept
    {
        return FAILURE;
    }

    const structures::ERRORS structures::InvalidInput::errorType() const noexcept
    {
        return INVALID_INPUT;
    }

    const structures::ERRORS structures::Exception::errorType() const noexcept
    {
        return NO_MSG;
    }
}
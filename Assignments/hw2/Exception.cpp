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
}
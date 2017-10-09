#pragma once
#include "string_util.h"

// std includes
 #include <stdio.h>

namespace gea {

// ------------------------------------------------------------------------- //
// string_util                                                               //
// ------------------------------------------------------------------------- //

inline const int vsnprintf(char *buffer, const size_t size, const char *format, va_list args) {
    return std::vsnprintf(buffer, size, format, args);
}

} // namespace gea //

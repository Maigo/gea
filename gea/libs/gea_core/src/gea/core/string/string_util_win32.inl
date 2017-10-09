#pragma once
#include "string_util.h"

namespace gea {

// ------------------------------------------------------------------------- //
// string_util                                                               //
// ------------------------------------------------------------------------- //

inline const int vsnprintf(char *buffer, const size_t size, const char *format, va_list args) {
    return vsnprintf_s(buffer, size, _TRUNCATE, format, args);
}

} // namespace gea //

#pragma once

// std includes
#include <stdarg.h>
#include <string.h>

namespace gea {

// ------------------------------------------------------------------------- //
// string_util                                                               //
// ------------------------------------------------------------------------- //

inline const int vsnprintf(char *buffer, const size_t size, const char *format, va_list args);

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "string_util.inl"

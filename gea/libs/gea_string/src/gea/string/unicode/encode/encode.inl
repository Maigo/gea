#pragma once

// header include
#include "encode.h"

namespace gea {
namespace uni {

// error codes
inline const char* to_string(const error_code err) {
    switch (err) {
    case UNI_OK:                   return "UNI_OK";
    case UNI_EOF:                  return "UNI_EOF";
    case UNI_INVALID_CODEPOINT:    return "UNI_INVALID_CODEPOINT";
    case UNI_RESTRICTED_CODEPOINT: return "UNI_RESTRICTED_CODEPOINT";
    }
    return "";
}

} // namespace uni //
} // namespace gea //

#pragma once

// header include
#include "ucs4.h"

namespace gea {
namespace uni {
namespace ucs4 {

// error codes
inline const char* to_string(const error_code err) {
    switch (err) {
    case UCS4_OK:                   return "UCS4_OK";
    case UCS4_EOF:                  return "UCS4_EOF";
    case UCS4_INVALID_CODEPOINT:    return "UCS4_INVALID_CODEPOINT";
    case UCS4_RESTRICTED_CODEPOINT: return "UCS4_RESTRICTED_CODEPOINT";
    case UCS4_INCOMPLETE_SEQUENCE:  return "UCS4_INCOMPLETE_SEQUENCE";
    case UCS4_NO_ENCODING:          return "UCS4_NO_ENCODING";
    }
    return "";
}

// encode
inline error_code_t can_encode(codepoint_t cp) {
    error_code_t err = UCS4_OK;
    return err;
}

} // namespace ucs4 //
} // namespace uni //
} // namespace gea //

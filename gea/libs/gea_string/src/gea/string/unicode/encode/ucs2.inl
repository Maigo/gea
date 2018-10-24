#pragma once

// header include
#include "ucs2.h"

namespace gea {
namespace uni {
namespace ucs2 {

// error codes
inline const char* to_string(const error_code err) {
    switch (err) {
    case UCS2_OK:                   return "UCS2_OK";
    case UCS2_EOF:                  return "UCS2_EOF";
    case UCS2_INVALID_CODEPOINT:    return "UCS2_INVALID_CODEPOINT";
    case UCS2_RESTRICTED_CODEPOINT: return "UCS2_RESTRICTED_CODEPOINT";
    case UCS2_INCOMPLETE_SEQUENCE:  return "UCS2_INCOMPLETE_SEQUENCE";
    case UCS2_NO_ENCODING:          return "UCS2_NO_ENCODING";
    }
    return "";
}

// encode
inline error_code_t can_encode(codepoint_t cp) {
    error_code_t err = UCS2_OK;

    uint32_t cp_lt_ucs2max = (uint32_t) ((int32_t) (cp - (UCS2_MAX_ENCODE + 1)) >> 31);
    err = (cp_lt_ucs2max & UCS2_OK) | (~cp_lt_ucs2max & UCS2_NO_ENCODING);

    return err;
}

} // namespace ucs2 //
} // namespace uni //
} // namespace gea //

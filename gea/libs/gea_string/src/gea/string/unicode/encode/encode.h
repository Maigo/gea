#pragma once

namespace gea {
namespace uni {

// ------------------------------------------------------------------------- //
// Common interface                                                          //
// ------------------------------------------------------------------------- //

#define UNI_ERROR_CODE(x) (0x8000000 | x)
#define UNI_OK_CODE(x)    (0x0000000 | x)

// common types
typedef int32_t error_code_t;
//typedef int32_t size_t;

// lib error types
enum error_code : error_code_t {
    UNI_OK                   = UNI_OK_CODE(0),
    UNI_EOF                  = UNI_ERROR_CODE(1),
    UNI_INVALID_CODEPOINT    = UNI_ERROR_CODE(2),
    UNI_RESTRICTED_CODEPOINT = UNI_ERROR_CODE(3),
};
inline const char* to_string(const error_code err);

} // namespace uni //
} // namespace gea //

#include "encode.inl"

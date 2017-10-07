#pragma once

// gea includes
#include <gea/core/string/string_builder.h>
#include <gea/random/random.h>

namespace gea {
namespace data {

// ------------------------------------------------------------------------- //
// guid                                                                      //
// ------------------------------------------------------------------------- //

struct guid {
    uint32_t data0;
    uint16_t data1;
    uint16_t data2;
    uint8_t  data3[8];

    inline guid();
    inline guid(const uint32_t data0, const uint16_t data1, const uint16_t data2, const uint8_t data3[8]);
    inline guid(const uint8_t *data);
};

inline const bool operator ==(const guid &lhs, const guid &rhs);
inline const bool operator !=(const guid &lhs, const guid &rhs);
inline const bool operator <=(const guid &lhs, const guid &rhs);
inline const bool operator >=(const guid &lhs, const guid &rhs);
inline const bool operator < (const guid &lhs, const guid &rhs);
inline const bool operator > (const guid &lhs, const guid &rhs);
inline const size_t compare(const guid &lhs, const guid &rhs);

const char *to_string(const guid &guid, string_builder &builder);
const guid from_string(const char *s);

// ------------------------------------------------------------------------- //
// random                                                                    //
// ------------------------------------------------------------------------- //

const guid random_guid();

// ------------------------------------------------------------------------- //

} // namespace data //
} // namespace gea //

#include "guid.inl"

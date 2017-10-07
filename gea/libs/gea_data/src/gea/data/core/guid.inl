#pragma once
#include "guid.h"

// gea includes
#include <gea/core/string/string_builder.h>

namespace gea {
namespace data {

// ------------------------------------------------------------------------- //
// guid                                                                      //
// ------------------------------------------------------------------------- //

inline guid::guid() {
    c_assert(sizeof(guid) == 16);
    memset(this, 0xFF, sizeof(guid));
}

inline guid::guid(const uint32_t _data0, const uint16_t _data1, const uint16_t _data2, const uint8_t _data3[8])
    : data0(_data0), data1(_data1), data2(_data2) {
    memcpy(data3, _data3, 8 * sizeof(uint8_t));
}


inline guid::guid(const uint8_t *data) {
    c_assert(sizeof(guid) == 16);
    memcpy(this, data, sizeof(guid));
}

inline const bool operator ==(const guid &lhs, const guid &rhs) { return compare(lhs, rhs) == 0; }
inline const bool operator !=(const guid &lhs, const guid &rhs) { return compare(lhs, rhs) != 0; }
inline const bool operator <=(const guid &lhs, const guid &rhs) { return compare(lhs, rhs) <= 0; }
inline const bool operator >=(const guid &lhs, const guid &rhs) { return compare(lhs, rhs) >= 0; }
inline const bool operator < (const guid &lhs, const guid &rhs) { return compare(lhs, rhs) <  0; }
inline const bool operator > (const guid &lhs, const guid &rhs) { return compare(lhs, rhs) >  0; }

inline const size_t compare(const guid &lhs, const guid &rhs) {
    c_assert(sizeof(guid) == 16);
    return memcmp(&lhs, &rhs, sizeof(guid));
}

const char *to_string(const guid &guid, string_builder &builder) {
    l_assert_msg(builder.empty() && (builder.capacity() >= 37), "Invalid string builder!");
//    char buffer[16];
//    if (gea_likely(dec_to_hex(guid.data0, buffer, sizeof(buffer))))
//        builder.append(buffer, 8).append('-');
//    if (gea_likely(dec_to_hex(guid.data1, buffer, sizeof(buffer))))
//        builder.append(buffer, 4).append('-');
//    if (gea_likely(dec_to_hex(guid.data2, buffer, sizeof(buffer))))
//        builder.append(buffer, 4).append('-');
//    if (gea_likely(dec_to_hex(guid.data3 + 0, 2, buffer, sizeof(buffer))))
//        builder.append(buffer, 4).append('-');
//    if (gea_likely(dec_to_hex(guid.data3 + 2, 6, buffer, sizeof(buffer))))
//        builder.append(buffer, 12);

    builder.append_format("%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
        guid.data0, guid.data1, guid.data2, guid.data3[0], guid.data3[1],
        guid.data3[2], guid.data3[3], guid.data3[4], guid.data3[5], guid.data3[6], guid.data3[7]);
    return builder.data();
}

const guid from_string(const char *s) {
    l_assert_msg(strlen(s) == 36, "Invalid string!");

    uint32_t byte[11] = { 0 };
    const uint32_t cnt = gea::sscanf(s, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
        &byte[0], &byte[1], &byte[2], &byte[3], &byte[4],
        &byte[5], &byte[6], &byte[7], &byte[8], &byte[9],
        &byte[10]);
    l_assert_msg(cnt == 11, "Malformed GUID!");

    const uint32_t data0 = byte[0];
    const uint16_t data1 = byte[1], data2 = byte[2];
    const uint8_t data3[8] = { byte[3], byte[4], byte[5], byte[6], byte[7], byte[8], byte[9], byte[10] };
    return guid(data0, data1, data2, data3);
}

// ------------------------------------------------------------------------- //
// random                                                                    //
// ------------------------------------------------------------------------- //

const guid random_guid() {
    uint32_t data[4];
    data[0] = random_uint32_t();
    data[1] = random_uint32_t();
    data[2] = random_uint32_t();
    data[3] = random_uint32_t();

    return guid(reinterpret_cast<const uint8_t*>(data));
}

// ------------------------------------------------------------------------- //

} // namespace data //
} // namespace gea //

#pragma once

namespace gea {

// ------------------------------------------------------------------------- //
// string_util                                                               //
// ------------------------------------------------------------------------- //
class string_util
{
public:
    // variadic arguments
    inline static const int vsnprintf(char* buffer, const size_t size, const char* format, va_list args);
    inline static const int snprintf(char* buffer, const size_t size, const char* format, ...);

    inline static const int vsscanf(const char* s, const char* format, va_list args);
    inline static const int sscanf(const char* s, const char* format, ...);

    // compare
    inline static const bool equals(const char* s0, const char* e0, const char* s1, const char* e1);
    inline static const bool equals(const char* s0, const char* e0, const char* s1);
    inline static const bool equals(const char* s0, const char* s1);

    // search
    inline static const char* first_index_of(const char* s, const char c);
    inline static const char* first_index_of(const char* s, const char* end, const char c);
    inline static const char* last_index_of(const char* s, const char c);
    inline static const char* last_index_of(const char* s, const char* end, const char c);

    // conversion - hexadecimal to decimal
    inline static const uint8_t hex_to_dec(const char hex);

    inline static const size_t hex_to_dec(const char* hex, const size_t hex_size, uint8_t& out_dec);
    inline static const size_t hex_to_dec(const char* hex, const size_t hex_size, uint16_t& out_dec);
    inline static const size_t hex_to_dec(const char* hex, const size_t hex_size, uint32_t& out_dec);
    inline static const size_t hex_to_dec(const char* hex, const size_t hex_size, uint64_t& out_dec);
    inline static const size_t hex_to_dec(const char* hex, const size_t hex_size, uint8_t* out_dec, const size_t dec_size);

    // conversion - decimal to hexadecimal
    inline static const char dec_to_hex(const uint8_t dec);

    inline static const bool dec_to_hex(const uint8_t  dec, char* buffer, const size_t size);
    inline static const bool dec_to_hex(const uint16_t dec, char* buffer, const size_t size);
    inline static const bool dec_to_hex(const uint32_t dec, char* buffer, const size_t size);
    inline static const bool dec_to_hex(const uint64_t dec, char* buffer, const size_t size);
    inline static const bool dec_to_hex(const uint8_t* dec, const size_t n, char* buffer, const size_t size);

    // conversion - binary to decimal
    inline static const uint8_t bin_to_dec(const char bin);

    // conversion - decimal to binary
    inline static const char dec_to_bin(const uint8_t dec);

    inline static const bool dec_to_bin(const uint8_t  dec, char* buffer, const size_t size);
    inline static const bool dec_to_bin(const uint16_t dec, char* buffer, const size_t size);
    inline static const bool dec_to_bin(const uint32_t dec, char* buffer, const size_t size);
    inline static const bool dec_to_bin(const uint64_t dec, char* buffer, const size_t size);
    inline static const bool dec_to_bin(const uint8_t* dec, const size_t n, char* buffer, const size_t size);
};

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //

inline const char* const to_string(const bool value);

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "string_util.inl"

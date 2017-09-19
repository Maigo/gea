#pragma once

namespace gea {

// ------------------------------------------------------------------------- //
// string_util                                                               //
// ------------------------------------------------------------------------- //

inline const int vsnprintf(char *buffer, const size_t size, const char *format, va_list args);

// ------------------------------------------------------------------------- //
// conversion functions                                                      //
// ------------------------------------------------------------------------- //

// hexadecimal to decimal
inline const uint8_t hex_to_dec(const char hex);

inline const size_t hex_to_dec(const char *hex, const size_t hex_size, const uint8_t  &out_dec);
inline const size_t hex_to_dec(const char *hex, const size_t hex_size, const uint16_t &out_dec);
inline const size_t hex_to_dec(const char *hex, const size_t hex_size, const uint32_t &out_dec);
inline const size_t hex_to_dec(const char *hex, const size_t hex_size, const uint64_t &out_dec);
inline const size_t hex_to_dec(const char *hex, const size_t hex_size, uint8_t *out_dec, const size_t dec_size);

// decimal to hexadecimal
inline const char dec_to_hex(const uint8_t dec);

inline const bool dec_to_hex(const uint8_t  dec, char *buffer, const size_t size);
inline const bool dec_to_hex(const uint16_t dec, char *buffer, const size_t size);
inline const bool dec_to_hex(const uint32_t dec, char *buffer, const size_t size);
inline const bool dec_to_hex(const uint64_t dec, char *buffer, const size_t size);
inline const bool dec_to_hex(const uint8_t *dec, const size_t n, char *buffer, const size_t size);

// binary to decimal
inline const uint8_t bin_to_dec(const char bin);

// decimal to binary
inline const char dec_to_bin(const uint8_t dec);

inline const bool dec_to_bin(const uint8_t  dec, char *buffer, const size_t size);
inline const bool dec_to_bin(const uint16_t dec, char *buffer, const size_t size);
inline const bool dec_to_bin(const uint32_t dec, char *buffer, const size_t size);
inline const bool dec_to_bin(const uint64_t dec, char *buffer, const size_t size);
inline const bool dec_to_bin(const uint8_t *dec, const size_t n, char *buffer, const size_t size);

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "string_util.inl"

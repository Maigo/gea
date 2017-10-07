#pragma once

// gea includes
#include <gea/core/limits.h>
#include <gea/data/stream/io_stream.h>

namespace gea {

// ------------------------------------------------------------------------- //
// bit_ostream                                                               //
// ------------------------------------------------------------------------- //
class bit_ostream : public io_ostream {
public:
    inline bit_ostream(io_ostream &stream);

    virtual void flush() override;

    // floating point numbers
    void write_float (const float f);
    void write_double(const double d);
    // signed integers
    void write_int8 (const int8_t  u, const int8_t  min = gea::numeric_limits<int8_t>::min(),  const int8_t  max = gea::numeric_limits<int8_t>::max());
    void write_int16(const int16_t u, const int16_t min = gea::numeric_limits<int16_t>::min(), const int16_t max = gea::numeric_limits<int16_t>::max());
    void write_int32(const int32_t u, const int32_t min = gea::numeric_limits<int32_t>::min(), const int32_t max = gea::numeric_limits<int32_t>::max());
    void write_int64(const int64_t u, const int64_t min = gea::numeric_limits<int64_t>::min(), const int64_t max = gea::numeric_limits<int64_t>::max());
    // unsigned integers
    void write_uint8 (const uint8_t  u, const uint8_t  min = gea::numeric_limits<uint8_t>::min(),  const uint8_t  max = gea::numeric_limits<uint8_t>::max());
    void write_uint16(const uint16_t u, const uint16_t min = gea::numeric_limits<uint16_t>::min(), const uint16_t max = gea::numeric_limits<uint16_t>::max());
    void write_uint32(const uint32_t u, const uint32_t min = gea::numeric_limits<uint32_t>::min(), const uint32_t max = gea::numeric_limits<uint32_t>::max());
    void write_uint64(const uint64_t u, const uint64_t min = gea::numeric_limits<uint64_t>::min(), const uint64_t max = gea::numeric_limits<uint64_t>::max());
    // boolean
    void write_bool(const bool b);

private:
    void write_internal(const uint32_t bits, const uint32_t mask, const uint8_t size);

    io_ostream &m_stream;
};

// ------------------------------------------------------------------------- //
// bit_istream                                                               //
// ------------------------------------------------------------------------- //
class bit_istream {
public:
    // floating point numbers
    const float read_float();
    const double read_double();
    // signed integers
    const int8_t  read_int8 (const int8_t  min = gea::numeric_limits<int8_t>::min(),  const int8_t  max = gea::numeric_limits<int8_t>::max());
    const int16_t read_int16(const int16_t min = gea::numeric_limits<int16_t>::min(), const int16_t max = gea::numeric_limits<int16_t>::max());
    const int32_t read_int32(const int32_t min = gea::numeric_limits<int32_t>::min(), const int32_t max = gea::numeric_limits<int32_t>::max());
    const int64_t read_int64(const int64_t min = gea::numeric_limits<int64_t>::min(), const int64_t max = gea::numeric_limits<int64_t>::max());
    // unsigned integers
    const uint8_t  read_uint8 (const uint8_t  min = gea::numeric_limits<uint8_t>::min(),  const uint8_t  max = gea::numeric_limits<uint8_t>::max());
    const uint16_t read_uint16(const uint16_t min = gea::numeric_limits<uint16_t>::min(), const uint16_t max = gea::numeric_limits<uint16_t>::max());
    const uint32_t read_uint32(const uint32_t min = gea::numeric_limits<uint32_t>::min(), const uint32_t max = gea::numeric_limits<uint32_t>::max());
    const uint64_t read_uint64(const uint64_t min = gea::numeric_limits<uint64_t>::min(), const uint64_t max = gea::numeric_limits<uint64_t>::max());
    // boolean
    const bool read_bool();
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "bit_stream.inl"

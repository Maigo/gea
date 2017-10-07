#pragma once

// gea includes
#include <gea/core/limits.h>
#include <gea/data/stream/io_stream.h>

namespace gea {

// ------------------------------------------------------------------------- //
// fixed_ostream                                                             //
// ------------------------------------------------------------------------- //
class fixed_ostream : public io_ostream {
public:
    inline fixed_ostream(uint8_t *buffer, const size_t size);

    virtual void flush() override;

private:
    uint8_t *m_buffer;
    const size_t m_size;
};

// ------------------------------------------------------------------------- //
// fixed_istream                                                             //
// ------------------------------------------------------------------------- //
class fixed_istream : public io_istream {
public:
    inline fixed_istream(uint8_t *buffer, const size_t size);

private:
    uint8_t *m_buffer;
    const size_t m_size;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "fixed_stream.inl"

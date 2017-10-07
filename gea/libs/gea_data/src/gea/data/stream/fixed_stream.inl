#pragma once
#include "fixed_stream.h"

namespace gea {

// ------------------------------------------------------------------------- //
// fixed_ostream                                                             //
// ------------------------------------------------------------------------- //

inline fixed_ostream::fixed_ostream(uint8_t *buffer, const size_t size)
    : m_buffer(buffer), m_size(size) {
}

// ------------------------------------------------------------------------- //
// fixed_istream                                                             //
// ------------------------------------------------------------------------- //

inline fixed_istream::fixed_istream(uint8_t *buffer, const size_t size)
    : m_buffer(buffer), m_size(size) {
}

// ------------------------------------------------------------------------- //

}

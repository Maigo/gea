#pragma once

namespace gea {

// ------------------------------------------------------------------------- //
// memory util                                                               //
// ------------------------------------------------------------------------- //

class memory_util {
public:
	template <typename T>
	static inline T* align(T* const p, const size_t align);
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "memory_util.inl"

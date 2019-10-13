#pragma once

// header include
#include "delegate_base.h"

namespace gea {

// ------------------------------------------------------------------------- //
// delegate_base                                                             //
// ------------------------------------------------------------------------- //

template <typename RET, typename... ARGS>
inline delegate_base<RET(ARGS...)>::function_data::function_data() : self(0), function(nullptr) {}

template <typename RET, typename... ARGS>
inline delegate_base<RET(ARGS...)>::function_data::function_data(const function_data& other) : self(other.self), function(other.function) {}

template <typename RET, typename... ARGS>
inline delegate_base<RET(ARGS...)>::function_data::function_data(const uintptr_t other_self, function_t other_function) : self(other_self), function(other_function) {}

template <typename RET, typename... ARGS>
inline void delegate_base<RET(ARGS...)>::function_data::assign(const function_data& other) {
    self = other.self;
    function = other.function;
}

template <typename RET, typename... ARGS>
inline void delegate_base<RET(ARGS...)>::function_data::assign(const uintptr_t other_self, function_t other_function) {
    self = other_self;
    function = other_function;
}

template <typename RET, typename... ARGS>
inline const bool delegate_base<RET(ARGS...)>::function_data::is_empty() const { return (function == nullptr); }

template <typename RET, typename... ARGS>
inline const bool delegate_base<RET(ARGS...)>::function_data::operator== (function_data& other) const {
    return (self == other.self) && (function == other.function);
}

template <typename RET, typename... ARGS>
inline const bool delegate_base<RET(ARGS...)>::function_data::operator!= (function_data& other) const {
    return (self != other.self) || (function != other.function);
}

// ------------------------------------------------------------------------- //

} // namespace gea //

#pragma once
#include "variable.h"

// gea includes
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// variable                                                                  //
// ------------------------------------------------------------------------- //

inline const char *to_string(const variable_type variable_type) {
    switch (variable_type) {
    case variable_type__int8:
        return "variable_type__int8";
    case variable_type__int16:
        return "variable_type__int16";
    case variable_type__int32:
        return "variable_type__int32";
    case variable_type__int64:
        return "variable_type__int64";
    case variable_type__uint8:
        return "variable_type__uint8";
    case variable_type__uint16:
        return "variable_type__uint16";
    case variable_type__uint32:
        return "variable_type__uint32";
    case variable_type__uint64:
        return "variable_type__uint64";
    case variable_type__float32:
        return "variable_type__float32";
    case variable_type__double64:
        return "variable_type__double64";
    case variable_type__count: // fall-through
    case variable_type__invalid: // fall-through
    default:
        l_error_msg("invalid type!");
    }
    return "";
}

template <typename T> inline const variable_type get_variable_type() { return variable_type__invalid; }
template <> inline const variable_type get_variable_type<int8_t>()   { return variable_type__int8; }
template <> inline const variable_type get_variable_type<int16_t>()  { return variable_type__int16; }
template <> inline const variable_type get_variable_type<int32_t>()  { return variable_type__int32; }
template <> inline const variable_type get_variable_type<int64_t>()  { return variable_type__int64; }
template <> inline const variable_type get_variable_type<uint8_t>()  { return variable_type__uint8; }
template <> inline const variable_type get_variable_type<uint16_t>() { return variable_type__uint16; }
template <> inline const variable_type get_variable_type<uint32_t>() { return variable_type__uint32; }
template <> inline const variable_type get_variable_type<uint64_t>() { return variable_type__uint64; }
template <> inline const variable_type get_variable_type<float>()    { return variable_type__float32; }
template <> inline const variable_type get_variable_type<double>()   { return variable_type__double64; }

// ------------------------------------------------------------------------- //

inline variable::variable() : type(variable_type__invalid) {
    memset(raw_value, 0, sizeof(raw_value));
}

template <typename T>
inline variable::variable(const T value) : type(get_variable_type<T>()) {
    c_assert(sizeof(T) <= 8);
    *reinterpret_cast<T*>(&raw_value) = value;
}

template <typename T>
inline const T variable::get_value() const {
    c_assert(sizeof(T) <= 8);
    l_assert(type == get_variable_type<T>());
    return *reinterpret_cast<const T*>(&raw_value);
}

// ------------------------------------------------------------------------- //

} // namespace gea //

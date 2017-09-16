#pragma once

namespace gea {

// ------------------------------------------------------------------------- //
// variable                                                                  //
// ------------------------------------------------------------------------- //

enum variable_type {
    variable_type__int8,
    variable_type__int16,
    variable_type__int32,
    variable_type__int64,
    variable_type__uint8,
    variable_type__uint16,
    variable_type__uint32,
    variable_type__uint64,
    variable_type__float32,
    variable_type__double64,

    variable_type__count,
    variable_type__invalid,
};

struct variable {
    variable_type type;
    uint8_t raw_value[8];

    inline variable();
    template <typename T> inline variable(const T value);
    template <typename T> inline const T get_value() const;
};

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //

inline const char *to_string(const variable_type variable_type);

// TODO: strip cv type qualifiers
template <typename T>
inline const variable_type get_variable_type();

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "variable.inl"

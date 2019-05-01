#pragma once

// std includes
#include <type_traits>

namespace gea {

// ------------------------------------------------------------------------- //
// type_traits                                                               //
// ------------------------------------------------------------------------- //

// alias templates
template <typename T>
using remove_const = std::remove_const<T>;

template <typename T>
using remove_volatile = std::remove_volatile<T>;

template <typename T>
using remove_cv = std::remove_cv<T>;

template <typename T>
using add_const = typename std::add_const<T>::type;

template <typename T>
using add_volatile = typename std::add_volatile<T>::type;

template <typename T>
using add_cv = typename std::add_cv<T>::type;

template <typename T>
using remove_reference = typename std::remove_reference<T>::type;

template <typename T>
using add_lvalue_reference = typename std::add_lvalue_reference<T>::type;

template <typename T>
using add_rvalue_reference = typename std::add_rvalue_reference<T>::type;

template <typename T>
using make_signed = typename std::make_signed<T>::type;

template <typename T>
using make_unsigned = typename std::make_unsigned<T>::type;

template <typename T>
using remove_pointer = typename std::remove_pointer<T>::type;

template <typename T>
using add_pointer = typename std::add_pointer<T>::type;

// ------------------------------------------------------------------------- //

template <bool Test, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T>
{
    using type = T;
};

template <bool Test, typename T = void>
using enable_if_t = typename enable_if<Test, T>::type;

} // namespace gea //

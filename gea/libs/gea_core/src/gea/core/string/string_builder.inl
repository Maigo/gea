#pragma once
#include "string_builder.h"

// gea includes
#include <gea/core/string/string_util.h>
#include <gea/utility/assert.h>

// TODO: added here to avoid dependency, remove?
template <typename T>
static const T min(const T lhs, const T rhs) { return lhs <= rhs ? lhs : rhs; }
template <typename T>
static const T max(const T lhs, const T rhs) { return lhs >= rhs ? lhs : rhs; }

namespace gea {

// ------------------------------------------------------------------------- //
// string_builder                                                            //
// ------------------------------------------------------------------------- //

template <typename T>
inline string_builder_impl<T> &string_builder_impl<T>::append(const T *s) {
    const size_t len = strlen(s);
    return append(s, len);
}

template <typename T>
inline string_builder_impl<T> &string_builder_impl<T>::append(const T *s, const T *e) {
    const size_t len = (e - s);
    return append(s, len);
}

template <typename T>
inline string_builder_impl<T> &string_builder_impl<T>::append(const T *s, const size_t size) {
    const char_t *end = min(m_pos + size, m_end - 1);

    for (const char_t *it = s; m_pos < end; ++m_pos, ++it) {
        (*m_pos) = (*it);
    }
    null_terminate();
    return (*this);
}

template <typename T>
inline string_builder_impl<T> &string_builder_impl<T>::append(const T c) {
    const char_t *end = min(m_pos + 1, m_end - 1);
    if (m_pos < end) {
        (*m_pos++) = c;
    }
    null_terminate();
    return (*this);
}

template <typename T>
inline string_builder_impl<T> &string_builder_impl<T>::append_format(const T *format, ...) {
    const size_t remaining = max(m_end - m_pos, ptrdiff_t(0));

    va_list args;
    va_start(args, format);
    string_util::vsnprintf(m_pos, remaining, format, args);
    va_end(args);
    return (*this);
}

template <typename T>
inline const T *const string_builder_impl<T>::data() const { return m_buffer; }

template <typename T>
inline T *const string_builder_impl<T>::data() { return m_buffer; }

template <typename T>
inline const bool string_builder_impl<T>::reserve(const size_t size) {
    return size_t(m_end - m_buffer) >= size;
}

template <typename T>
inline const bool string_builder_impl<T>::resize(const size_t size, const T t) {
    const char_t *end = min(m_buffer + size, m_end - 1);
    for (; m_pos < end; ++m_pos) {
        (*m_pos) = t;
    }
    null_terminate();
    return (m_buffer + size) <= (m_end - 1);
}

template <typename T>
inline void string_builder_impl<T>::reset() {
    m_pos = m_buffer;
    null_terminate();
}

template <typename T>
inline const bool string_builder_impl<T>::empty() const { return (m_pos == m_buffer); }

template <typename T>
inline const size_t string_builder_impl<T>::size() const { return size_t(m_pos - m_buffer); }

template <typename T>
inline const size_t string_builder_impl<T>::capacity() const { return size_t(m_end - m_buffer); }

template <typename T>
inline string_builder_impl<T>::string_builder_impl(T *buffer, const size_t size) : m_pos(buffer), m_end(buffer + size), m_buffer(buffer) {
    l_assert_msg(buffer != nullptr && (size > 0), "Invalid buffer or buffer size!");
    null_terminate();
}

template <typename T>
inline void string_builder_impl<T>::null_terminate() {
    if (gea_likely(m_pos < m_end)) {
        (*m_pos) = '\0';
    }
}

// ------------------------------------------------------------------------- //

inline string_builder::string_builder(char_t *buffer, const size_t size)
    : super_t(buffer, size) { }

// ------------------------------------------------------------------------- //

template <int N>
inline static_string_builder<N>::static_string_builder()
    : super_t(m_buffer, sizeof(m_buffer)) {}

// ------------------------------------------------------------------------- //

inline wstring_builder::wstring_builder(char_t *buffer, const size_t size)
    : super_t(buffer, size) { }

// ------------------------------------------------------------------------- //

} // namespace gea //

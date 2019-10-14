#pragma once

// header include
#include "string_builder.h"

// gea includes
#include <gea/core/bits/bits.h>
#include <gea/core/string/string_util.h>
#include <gea/core/math.h>
#include <gea/system/memory/allocator/allocator.h>
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// string_builder                                                            //
// ------------------------------------------------------------------------- //

template <typename T>
inline string_builder_impl<T>& string_builder_impl<T>::append(const T* s) {
    const size_t len = strlen(s);
    return append(s, len);
}

template <typename T>
inline string_builder_impl<T>& string_builder_impl<T>::append(const T* s, const T* e) {
    const size_t len = (e - s);
    return append(s, len);
}

template <typename T>
inline string_builder_impl<T>& string_builder_impl<T>::append(const T* s, const size_t length) {
    if (reserve(size() + length)) {
        const char_t* end = mth::min(m_pos + length, m_end - 1);

        for (const char_t* it = s; m_pos < end; ++m_pos, ++it) {
            (*m_pos) = (*it);
        }
        null_terminate();
    } else {
        l_assert_msg(false, "Unable to allocate memory!");
    }
    return (*this);
}

template <typename T>
inline string_builder_impl<T>& string_builder_impl<T>::append(const T c) {
    if (reserve(size() + 1)) {
        const char_t* end = mth::min(m_pos + 1, m_end - 1);
        if (m_pos < end) {
            (*m_pos++) = c;
        }
        null_terminate();
    } else {
        l_assert_msg(false, "Unable to allocate memory!");
    }
    return (*this);
}

template <typename T>
inline string_builder_impl<T>& string_builder_impl<T>::append(const sub_string_impl<T>& s) {
    const size_t len = (s.end - s.begin);
    return append(s.begin, len);
}

template <typename T>
inline string_builder_impl<T>& string_builder_impl<T>::append_format(const T* format, ...) {
    va_list args;
    va_start(args, format);

    const size_t length = string_util::vscprintf(format, args);
    if (reserve(size() + length)) {
        const size_t remaining = mth::max(m_end - m_pos, ptrdiff_t(0));
        string_util::vsnprintf(m_pos, remaining, format, args);
    } else {
        l_assert_msg(false, "Unable to allocate memory!");
    }

    va_end(args);
    return (*this);
}

template <typename T>
inline const T* const string_builder_impl<T>::data() const { return m_buffer; }

template <typename T>
inline T* const string_builder_impl<T>::data() { return m_buffer; }

template <typename T>
inline const T* const string_builder_impl<T>::end() const { return m_pos; }

template <typename T>
inline T* const string_builder_impl<T>::end() { return m_pos; }

template <typename T>
inline const bool string_builder_impl<T>::reserve(const size_t size) {
    return (size <= capacity()) || (!m_call_reserve.is_empty() && m_call_reserve(this, size));
}

template <typename T>
inline const bool string_builder_impl<T>::resize(const size_t size, const T t) {
    if (reserve(size)) {
        const char_t* end = mth::min(m_buffer + size, m_end - 1);
        for (; m_pos < end; ++m_pos) {
            (*m_pos) = t;
        }
        null_terminate();
    } else {
        l_assert_msg(false, "Unable to allocate memory!");
    }
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
inline const size_t string_builder_impl<T>::capacity() const { return static_cast<size_t>(mth::max((m_end - m_buffer) - 1, ptrdiff_t(0))); }

template <typename T>
inline string_builder_impl<T>::string_builder_impl() : m_pos(nullptr), m_end(nullptr), m_buffer(nullptr) {}

template <typename T>
inline string_builder_impl<T>::string_builder_impl(T* buffer, const size_t size) : m_pos(buffer), m_end(buffer + size), m_buffer(buffer) {
    l_assert_msg((buffer != nullptr) && (size > 0), "Invalid buffer or buffer size!");
    null_terminate();
}

template <typename T>
inline void string_builder_impl<T>::assign(T* buffer, const size_t pos, const size_t size) {
    l_assert_msg((buffer != nullptr) && (pos < size) && (size > 0), "Invalid buffer, buffer position or size!");
    m_pos = buffer + pos;
    m_end = buffer + size;
    m_buffer = buffer;

    null_terminate();
}

template <typename T>
inline void string_builder_impl<T>::set_call_reserve(const call_reserve_t& call_reserve) { m_call_reserve = call_reserve; }

template <typename T>
inline void string_builder_impl<T>::null_terminate() {
    if (gea_likely(m_pos < m_end)) {
        (*m_pos) = '\0';
    }
}

// ------------------------------------------------------------------------- //

inline string_builder::string_builder()
    : super_t() { }

inline string_builder::string_builder(char_t* buffer, const size_t size)
    : super_t(buffer, size) { }

// ------------------------------------------------------------------------- //

template <int N>
inline static_string_builder<N>::static_string_builder()
    : super_t(m_buffer, sizeof(m_buffer)) {}

// ------------------------------------------------------------------------- //

inline extendable_string_builder::extendable_string_builder(allocator& allocator)
    : super_t(), m_allocator(allocator)
{
    const call_reserve_t call_reserve = call_reserve_t::create<extendable_string_builder, &extendable_string_builder::reserve>();
    set_call_reserve(call_reserve);
}

inline extendable_string_builder::extendable_string_builder(allocator& allocator, const size_t capacity)
    : super_t(), m_allocator(allocator)
{
    const call_reserve_t call_reserve = call_reserve_t::create<extendable_string_builder, &extendable_string_builder::reserve>();
    set_call_reserve(call_reserve);

    reserve(capacity);
}

inline extendable_string_builder::~extendable_string_builder() {
    if (char* old_buffer = data()) {
        m_allocator.deallocate(old_buffer);
    }
}

inline const bool extendable_string_builder::reserve(const size_t capacity) {
    const size_t old_capacity = extendable_string_builder::capacity();
    const size_t new_capacity = bit::rpow2(mth::max(2 * old_capacity, capacity) + 1);
    if (char* new_buffer = static_cast<char*>(m_allocator.allocate(new_capacity))) {
        char* old_buffer = data();

        memcpy(new_buffer, data(), size());
        assign(new_buffer, size(), new_capacity);
        m_allocator.deallocate(old_buffer);
        return true;
    }
    return false;
}

// ------------------------------------------------------------------------- //

inline wstring_builder::wstring_builder(char_t* buffer, const size_t size)
    : super_t(buffer, size) { }

// ------------------------------------------------------------------------- //

} // namespace gea //

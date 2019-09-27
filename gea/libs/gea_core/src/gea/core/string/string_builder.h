#pragma once

namespace gea {

// ------------------------------------------------------------------------- //
// subb_string                                                               //
// ------------------------------------------------------------------------- //
template <typename T>
struct sub_string_impl
{
    const T* begin;
    const T* end;
};

typedef sub_string_impl<char> sub_string;
typedef sub_string_impl<wchar_t> sub_wstring;

// ------------------------------------------------------------------------- //
// string_builder                                                            //
// ------------------------------------------------------------------------- //

template <class T>
class string_builder_impl {
public:
    typedef T char_t;
    typedef sub_string_impl<T> sub_string_t;

    inline string_builder_impl &append(const T *s);
    inline string_builder_impl &append(const T *s, const T *e);
    inline string_builder_impl &append(const T *s, const size_t size);
    inline string_builder_impl &append(const T c);
    inline string_builder_impl &append_format(const T *format, ...);

    inline const T *const data() const;
    inline       T *const data();

    inline const bool reserve(const size_t size); // check
    inline const bool resize(const size_t size, const T t);
    inline void reset();

    inline const bool empty() const;
    inline const size_t size() const;
    inline const size_t capacity() const;

protected:
    inline string_builder_impl(T *buffer, const size_t size);

private:
    inline void null_terminate();

    T *m_pos;
    T *m_end;
    T *m_buffer;
};

// ------------------------------------------------------------------------- //

class string_builder : public string_builder_impl<char> {
public:
    typedef string_builder_impl<char> super_t;
    typedef super_t::char_t char_t;

protected:
    inline string_builder(char_t *buffer, const size_t size);
};

// ------------------------------------------------------------------------- //

template <int N = 128>
class static_string_builder : public string_builder {
public:
    typedef string_builder super_t;
    typedef super_t::char_t char_t;

    inline static_string_builder();

private:
    char_t m_buffer[N];
};

// ------------------------------------------------------------------------- //

class wstring_builder : public string_builder_impl<wchar_t> {
public:
    typedef string_builder_impl<wchar_t> super_t;
    typedef super_t::char_t char_t;

protected:
    inline wstring_builder(char_t *buffer, const size_t size);
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "string_builder.inl"

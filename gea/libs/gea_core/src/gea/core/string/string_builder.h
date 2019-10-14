#pragma once

// gea includes
#include <gea/core/string/string.h>
#include <gea/core/pattern/member_delegate.h>

namespace gea {

// forward declarations
class allocator;

// ------------------------------------------------------------------------- //
// string_builder                                                            //
// ------------------------------------------------------------------------- //

template <class T>
class string_builder_impl {
public:
    typedef T char_t;

    inline string_builder_impl& append(const T* s);
    inline string_builder_impl& append(const T* s, const T* e);
    inline string_builder_impl& append(const T* s, const size_t size);
    inline string_builder_impl& append(const T c);
    inline string_builder_impl& append(const sub_string_impl<T>& s);
    inline string_builder_impl& append_format(const T* format, ...);

    inline const T* const data() const;
    inline       T* const data();
    inline const T* const end() const;
    inline       T* const end();

    inline const bool reserve(const size_t size);
    inline const bool resize(const size_t size, const T t);
    inline void reset();

    inline const bool empty() const;
    inline const size_t size() const;
    inline const size_t capacity() const;

protected:
    inline string_builder_impl();
    inline string_builder_impl(T* buffer, const size_t size);
    inline void assign(T* buffer, const size_t pos, const size_t size);

    typedef member_delegate<const bool(const size_t)> call_reserve_t;
    inline void set_call_reserve(const call_reserve_t& call_reserve);

private:
    inline void null_terminate();

    call_reserve_t m_call_reserve;
    T* m_pos;
    T* m_end;
    T* m_buffer;
};

// ------------------------------------------------------------------------- //

class string_builder : public string_builder_impl<char> {
public:
    typedef string_builder_impl<char> super_t;
    typedef super_t::char_t char_t;

protected:
    inline string_builder();
    inline string_builder(char_t* buffer, const size_t size);
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

class extendable_string_builder : public string_builder {
public:
    typedef string_builder super_t;
    typedef super_t::char_t char_t;

    inline extendable_string_builder(allocator& allocator);
    inline extendable_string_builder(allocator& allocator, const size_t capacity);
    inline ~extendable_string_builder();

    inline const bool reserve(const size_t size);

private:
    allocator& m_allocator;
};

// ------------------------------------------------------------------------- //

class wstring_builder : public string_builder_impl<wchar_t> {
public:
    typedef string_builder_impl<wchar_t> super_t;
    typedef super_t::char_t char_t;

protected:
    inline wstring_builder(char_t* buffer, const size_t size);
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "string_builder.inl"

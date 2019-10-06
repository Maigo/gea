#pragma once

namespace gea {

// ------------------------------------------------------------------------- //
// sub_string                                                                //
// ------------------------------------------------------------------------- //
template <typename T>
struct sub_string_impl {
    const T* begin;
    const T* end;
};

typedef sub_string_impl<char> sub_string;
typedef sub_string_impl<wchar_t> sub_wstring;

// ------------------------------------------------------------------------- //

} // namespace gea //

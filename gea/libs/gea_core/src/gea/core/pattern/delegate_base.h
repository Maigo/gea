#pragma once

namespace gea {

// ------------------------------------------------------------------------- //
// delegate_base                                                             //
// ------------------------------------------------------------------------- //

template <typename T>
class delegate_base;

template <typename RET, typename... ARGS>
class delegate_base<RET(ARGS...)> {
protected:
    typedef RET(*function_t)(const uintptr_t self, ARGS...);

    struct function_data {
        inline function_data();
        inline function_data(const function_data& other);
        inline function_data(const uintptr_t other_self, function_t other_function);

        inline void assign(const function_data& other);
        inline void assign(const uintptr_t other_self, function_t other_function);

        inline const bool is_empty() const;

        inline const bool operator== (function_data& other) const;
        inline const bool operator!= (function_data& other) const;

        uintptr_t self;
        function_t function;
    };
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "delegate_base.inl"

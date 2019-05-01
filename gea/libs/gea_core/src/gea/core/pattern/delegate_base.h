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
        inline function_data() : self(0), function(nullptr) {}
        inline function_data(const function_data& other) : self(other.self), function(other.function) {}
        inline function_data(const uintptr_t other_self, function_t other_function) : self(other_self), function(other_function) {}

        inline void assign(const function_data& other) {
            self = other.self;
            function = other.function;
        }
        inline void assign(const uintptr_t other_self, function_t other_function) {
            self = other_self;
            function = other_function;
        }

        inline const bool is_empty() const { return (function == nullptr); }

        inline const bool operator== (function_data& other) const {
            return (self == other.self) && (function == other.function);
        }
        inline const bool operator!= (function_data& other) const {
            return (self != other.self) || (function != other.function);
        }

        uintptr_t self;
        function_t function;
    };
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "delegate_base.inl"

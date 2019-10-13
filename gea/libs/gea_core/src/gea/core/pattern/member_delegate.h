#pragma once

namespace gea {

// ------------------------------------------------------------------------- //
// member_delegate_base                                                      //
// ------------------------------------------------------------------------- //

template <typename T>
class member_delegate_base;

template <typename RET, typename... ARGS>
class member_delegate_base<RET(ARGS...)> {
protected:
    typedef RET(*function_t)(void* self, ARGS...);

    struct function_data {
        inline function_data();
        inline function_data(const function_data& other);
        inline function_data(function_t other_function);

        inline void assign(const function_data& other);
        inline void assign(function_t other_function);

        inline const bool is_empty() const;

        inline const bool operator== (function_data& other) const;
        inline const bool operator!= (function_data& other) const;

        function_t function;
    };
};

// ------------------------------------------------------------------------- //
// member_delegate                                                           //
// ------------------------------------------------------------------------- //

template <typename T>
class member_delegate;

template <typename RET, typename... ARGS>
class member_delegate<RET(ARGS...)> : private member_delegate_base<RET(ARGS...)> {
public:
    inline member_delegate();
    inline member_delegate(const member_delegate& other);

    // assign delegate - member function
    inline member_delegate& operator= (const member_delegate& other);

    inline const bool is_empty() const;

    inline const bool operator== (const member_delegate& other) const;
    inline const bool operator!= (const member_delegate& other) const;

    RET operator() (void* self, ARGS... args) const;

    // create delegate - member function
    template <class T, RET(T::*TFunction)(ARGS...)>
    static inline member_delegate create();

    // create delegate - const member function
    template <class T, RET(T::*TFunction)(ARGS...) const>
    static inline member_delegate create();

private:
    typedef typename member_delegate_base<RET(ARGS...)>::function_t function_t;
    typedef typename member_delegate_base<RET(ARGS...)>::function_data function_data;

    inline explicit member_delegate(function_t function);

    // call wrapper - member function
    template <class T, RET(T::*TFunction)(ARGS...)>
    static RET member_function_call(void* self, ARGS... args);

    // call wrapper - const member function
    template <class T, RET(T::*TFunction)(ARGS...) const>
    static RET const_member_function_call(void* self, ARGS... args);

    function_data m_function_data;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "member_delegate.inl"

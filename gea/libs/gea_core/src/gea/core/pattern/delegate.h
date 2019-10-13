#pragma once

// gea includes
#include <gea/core/pattern/delegate_base.h>

namespace gea {

// ------------------------------------------------------------------------- //
// delegate                                                                  //
// ------------------------------------------------------------------------- //

template <typename T>
class delegate;

template <typename RET, typename... ARGS>
class delegate<RET(ARGS...)> : private delegate_base<RET(ARGS...)> {
public:
    inline delegate();
    inline delegate(const delegate& other);
    template <typename LAMBDA>
    inline delegate(const LAMBDA& lambda);

    // assign delegate - member function
    inline delegate& operator= (const delegate& other);

    // assign delegate - lambda
    template <typename LAMBDA>
    inline delegate& operator= (const LAMBDA& lambda);

    inline const bool is_empty() const;

    inline const bool operator== (const delegate& other) const;
    inline const bool operator!= (const delegate& other) const;

    RET operator() (ARGS... args) const;

    // create delegate - member function
    template <class T, RET(T::*TFunction)(ARGS...)>
    static inline delegate create(T* instance);

    // create delegate - const member function
    template <class T, RET(T::*TFunction)(ARGS...) const>
    static inline delegate create(const T* instance);

    // create delegate - function
    template <RET(*Function)(ARGS...)>
    static inline delegate create();

    // create delegate - lambda
    template <typename LAMBDA>
    static inline delegate create(const LAMBDA& lambda);

private:
    typedef typename delegate_base<RET(ARGS...)>::function_t function_t;
    typedef typename delegate_base<RET(ARGS...)>::function_data function_data;

    inline delegate(const uintptr_t self, function_t function);

    // call wrapper - member function
    template <class T, RET(T::*TFunction)(ARGS...)>
    static RET member_function_call(uintptr_t self, ARGS... args);

    // call wrapper - const member function
    template <class T, RET(T::*TFunction)(ARGS...) const>
    static RET const_member_function_call(uintptr_t self, ARGS... args);

    // call wrapper - function
    template <RET(*Function)(ARGS...)>
    static RET function_call(uintptr_t self, ARGS... args);

    // call wrapper - lambda
    template <typename LAMBDA>
    static RET lambda_call(uintptr_t self, ARGS... args);

    function_data m_function_data;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "delegate.inl"

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
    inline delegate() : m_function_data() {}
    inline delegate(const delegate& other) : m_function_data(other.m_function_data) { }
    template <typename LAMBDA>
    delegate(const LAMBDA& lambda) : m_function_data(reinterpret_cast<uintptr_t>(&lambda), lambda_call<LAMBDA>) {}

    // assign delegate - member function
    inline delegate& operator= (const delegate& other) {
        m_function_data.assign(other.m_function_data);
        return (*this);
    }

    // assign delegate - lambda
    template <typename LAMBDA>
    inline delegate& operator= (const LAMBDA& lambda) {
        m_function_data.assign(reinterpret_cast<uintptr_t>(&lambda), lambda_call<LAMBDA>);
        return *this;
    }

    inline const bool is_empty() const { return m_function_data.is_empty(); }

    inline const bool operator== (const delegate& other) const { return m_function_data == other.m_function_data; }
    inline const bool operator!= (const delegate& other) const { return m_function_data != other.m_function_data; }

    RET operator() (ARGS... args) const {
        return (*m_function_data.function)(m_function_data.self, args...);
    }

    // create delegate - member function
    template <class T, RET(T::*TFunction)(ARGS...)>
    static inline delegate create(T* instance) {
        return delegate(reinterpret_cast<uintptr_t>(instance), member_function_call<T, TFunction>);
    }

    // create delegate - const member function
    template <class T, RET(T::*TFunction)(ARGS...) const>
    static inline delegate create(const T* instance) {
        return delegate(reinterpret_cast<uintptr_t>(instance), const_member_function_call<T, TFunction>);
    }

    // create delegate - function
    template <RET(*Function)(ARGS...)>
    static inline delegate create() {
        return delegate(reinterpret_cast<uintptr_t>(nullptr), function_call<Function>);
    }

    // create delegate - lambda
    template <typename LAMBDA>
    static inline delegate create(const LAMBDA& lambda) {
        return delegate(reinterpret_cast<uintptr_t>(&lambda), lambda_call<LAMBDA>);
    }

private:
    typedef typename delegate_base<RET(ARGS...)>::function_t function_t;
    typedef typename delegate_base<RET(ARGS...)>::function_data function_data;

    inline delegate(const uintptr_t self, function_t function) : m_function_data(self, function) {}

    // call wrapper - member function
    template <class T, RET(T::*TFunction)(ARGS...)>
    static RET member_function_call(uintptr_t self, ARGS... args) {
        T* t = reinterpret_cast<T*>(self);
        return (t->*TFunction)(args...);
    }

    // call wrapper - const member function
    template <class T, RET(T::*TFunction)(ARGS...) const>
    static RET const_member_function_call(uintptr_t self, ARGS... args) {
        const T* t = reinterpret_cast<T*>(self);
        return (t->*TFunction)(args...);
    }

    // call wrapper - function
    template <RET(*Function)(ARGS...)>
    static RET function_call(uintptr_t self, ARGS... args) {
        return (*Function)(args...);
    }

    // call wrapper - lambda
    template <typename LAMBDA>
    static RET lambda_call(uintptr_t self, ARGS... args) {
        LAMBDA* l = reinterpret_cast<LAMBDA*>(self);
        return (l->operator())(args...);
    }

    function_data m_function_data;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "delegate.inl"

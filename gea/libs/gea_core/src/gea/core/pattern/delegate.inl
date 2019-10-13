#pragma once

// header include
#include "delegate.h"

namespace gea {

// ------------------------------------------------------------------------- //
// delegate                                                                  //
// ------------------------------------------------------------------------- //

template <typename RET, typename... ARGS>
inline delegate<RET(ARGS...)>::delegate() : m_function_data() {}

template <typename RET, typename... ARGS>
inline delegate<RET(ARGS...)>::delegate(const delegate& other) : m_function_data(other.m_function_data) {}

template <typename RET, typename... ARGS>
template <typename LAMBDA>
inline delegate<RET(ARGS...)>::delegate(const LAMBDA& lambda) : m_function_data(reinterpret_cast<uintptr_t>(&lambda), lambda_call<LAMBDA>) {}

template <typename RET, typename... ARGS>
inline delegate<RET(ARGS...)>& delegate<RET(ARGS...)>::operator= (const delegate& other) {
    m_function_data.assign(other.m_function_data);
    return (*this);
}

template <typename RET, typename... ARGS>
template <typename LAMBDA>
inline delegate<RET(ARGS...)>& delegate<RET(ARGS...)>::operator= (const LAMBDA& lambda) {
    m_function_data.assign(reinterpret_cast<uintptr_t>(&lambda), lambda_call<LAMBDA>);
    return *this;
}

template <typename RET, typename... ARGS>
inline const bool delegate<RET(ARGS...)>::is_empty() const { return m_function_data.is_empty(); }

template <typename RET, typename... ARGS>
inline const bool delegate<RET(ARGS...)>::operator== (const delegate& other) const { return m_function_data == other.m_function_data; }

template <typename RET, typename... ARGS>
inline const bool delegate<RET(ARGS...)>::operator!= (const delegate& other) const { return m_function_data != other.m_function_data; }

template <typename RET, typename... ARGS>
RET delegate<RET(ARGS...)>::operator() (ARGS... args) const {
    return (*m_function_data.function)(m_function_data.self, args...);
}

// create delegate - member function
template <typename RET, typename... ARGS>
template <class T, RET(T::* TFunction)(ARGS...)>
inline delegate<RET(ARGS...)> delegate<RET(ARGS...)>::create(T* instance) {
    return delegate(reinterpret_cast<uintptr_t>(instance), member_function_call<T, TFunction>);
}

// create delegate - const member function
template <typename RET, typename... ARGS>
template <class T, RET(T::* TFunction)(ARGS...) const>
inline delegate<RET(ARGS...)> delegate<RET(ARGS...)>::create(const T* instance) {
    return delegate(reinterpret_cast<uintptr_t>(instance), const_member_function_call<T, TFunction>);
}

// create delegate - function
template <typename RET, typename... ARGS>
template <RET(*Function)(ARGS...)>
inline delegate<RET(ARGS...)> delegate<RET(ARGS...)>::create() {
    return delegate(reinterpret_cast<uintptr_t>(nullptr), function_call<Function>);
}

// create delegate - lambda
template <typename RET, typename... ARGS>
template <typename LAMBDA>
inline delegate<RET(ARGS...)> delegate<RET(ARGS...)>::create(const LAMBDA& lambda) {
    return delegate(reinterpret_cast<uintptr_t>(&lambda), lambda_call<LAMBDA>);
}

template <typename RET, typename... ARGS>
inline delegate<RET(ARGS...)>::delegate(const uintptr_t self, function_t function) : m_function_data(self, function) {}

// call wrapper - member function
template <typename RET, typename... ARGS>
template <class T, RET(T::* TFunction)(ARGS...)>
RET delegate<RET(ARGS...)>::member_function_call(uintptr_t self, ARGS... args) {
    T* t = reinterpret_cast<T*>(self);
    return (t->*TFunction)(args...);
}

// call wrapper - const member function
template <typename RET, typename... ARGS>
template <class T, RET(T::* TFunction)(ARGS...) const>
RET delegate<RET(ARGS...)>::const_member_function_call(uintptr_t self, ARGS... args) {
    const T* t = reinterpret_cast<T*>(self);
    return (t->*TFunction)(args...);
}

// call wrapper - function
template <typename RET, typename... ARGS>
template <RET(*Function)(ARGS...)>
RET delegate<RET(ARGS...)>::function_call(uintptr_t self, ARGS... args) {
    return (*Function)(args...);
}

// call wrapper - lambda
template <typename RET, typename... ARGS>
template <typename LAMBDA>
RET delegate<RET(ARGS...)>::lambda_call(uintptr_t self, ARGS... args) {
    LAMBDA* l = reinterpret_cast<LAMBDA*>(self);
    return (l->operator())(args...);
}

// ------------------------------------------------------------------------- //

}// namespace gea //
